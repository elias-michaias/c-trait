# How c-trait works

This document explains the preprocessor machinery that powers c-trait's static and dynamic dispatch, and why the design is the way it is.

> **Credit:** The core technique — an [extendible `_Generic`](https://github.com/JacksonAllan/CC/blob/main/articles/Better_C_Generics_Part_1_The_Extendible_Generic.md) powered by a preprocessor counter and self-including headers — was inspired by Jackson Allan's article on the subject and his [Convenient Containers](https://github.com/JacksonAllan/CC) library. `c-trait` adapts and extends that pattern from single-dispatch generic functions to full trait-based polymorphism.

## Table of contents

- [The core problem](#the-core-problem)
- [Self-include loop](#self-include-loop)
- [Trait definition: what `#include "trait.h"` emits](#trait-definition-what-include-traith-emits)
- [Selector objects and selector types](#selector-objects-and-selector-types)
- [Impl registration](#impl-registration)
- [Static dispatch (SD)](#static-dispatch-sd)
- [The `call()` dispatch chain](#the-call-dispatch-chain)
- [Dynamic dispatch (DynSD)](#dynamic-dispatch-dynsd)
- [Default methods and override detection](#default-methods-and-override-detection)
- [Why a single `call()` macro](#why-a-single-call-macro)
- [The octal counter trick](#the-octal-counter-trick)
- [Limitations](#limitations)

---

## The core problem

C has no function overloading, no traits, and no open-world interfaces. The C preprocessor also cannot loop. So how do you:

1. Register an unlimited number of type+trait+method combinations at compile time?
2. Route a single function call (`call(Animal.get_snacks, &obj)`) to the correct implementation based on both the selector and the object's concrete type?
3. Do all of this with zero runtime overhead for static dispatch?

The answer is: **self-inclusion** + **type tags** + **a global octal counter**.

---

## Self-include loop

The central trick is that `trait.h` includes itself. The file is structured as a big `#ifdef` tree:

```c
#ifdef For        // ← impl path (or SD/DynSD loop body)
  #ifdef ___TRAIT_SD_ACTIVE
    ...           // SD loop iteration
  #elif defined ___TRAIT_DYNSD_ACTIVE
    ...           // DynSD loop iteration
  #elif defined Forward
    ...           // forward-declare pass
  #else
    ...           // normal impl registration
  #endif
#elif defined Trait   // ← trait definition path
  ...
#else
  // stable utility macros (glue, dispatch chains, counters)
#endif
```

**Why self-inclusion?** The preprocessor can't loop, so you can't iterate over methods in a trait signature. But you *can* re-enter the same file with different state macros defined, routing through different branches each time. Each re-entry processes one "step" of the registration, then kicks off the next step via another self-include — forming a chain of passes that the preprocessor executes sequentially.

When you write:
```c
#define For Dog
#define Impl Animal
#include "trait.h"
```

The preprocessor re-opens `trait.h` from the top. Because `For` is defined, it enters the `#ifdef For` branch and processes the impl code. The second `#include "trait.h"` at the bottom of that branch re-enters the file again — but this time, additional state macros (like `___TRAIT_SD_ACTIVE`) may be defined, routing it through a different branch.

**State macros** that control which path is taken:

| Macro | Meaning |
|-------|---------|
| `For` | Concrete type being implemented (or `Default`) |
| `Impl` | Trait being implemented |
| `Trait` | Trait being *defined* (not implemented) |
| `___TRAIT_SD_ACTIVE` | Inside the SD self-include loop |
| `___TRAIT_DYNSD_ACTIVE` | Inside the DynSD self-include loop |
| `Forward` | Forward-declare pass (emits extern decls + SD entries before `def()` bodies) |
| `___TRAIT_IS_STATIC_CURRENT` | Current trait is static (no vtable) |

All of these are `#undef`-ed after use, making each `#include` block single-use.

---

## Trait definition: what `#include "trait.h"` emits

When you write:
```c
#define Trait Animal
#define Dynamic
#define AnimalSignature(Self)    \
  require(Self, int, get_snacks) \
  default(Self, void, feed, int)
#include "trait.h"
```

The file enters the `#elif defined Trait` branch. This is the "definition pass" — it generates all the scaffolding that implementations will later plug into. Here's what it emits, in order:

### 1. Vtable struct (FN)

```c
typedef struct {
  int (*get_snacks)(void *);
  void (*feed)(void *, int);
} Animal_vtable;
```

Each method becomes a function pointer field. The `FN` action makes `require` and `default` emit `RetType (*Name)(void *Self, Args...)`. This is the layout that dynamic dispatch will index into at runtime.

### 2. DynTrait typedef

```c
typedef struct {
  void *self;
  const Animal_vtable *vt;
} DynAnimal;
```

This is the "fat pointer" — a type-erased pointer plus a vtable pointer. Only emitted for dynamic traits. It's the object you pass to `call()` when you want runtime dispatch.

### 3. Forward inline wrappers (FWD)

```c
static inline int DynAnimal_get_snacks(DynAnimal self) {
  return self.vt->get_snacks(self.self);
}
static inline void DynAnimal_feed(DynAnimal self, int a1) {
  self.vt->feed(self.self, a1);
}
```

Convenience wrappers for calling through DynAnimal by value — a sugar layer on top of manual vtable access.

### 4. Per-method tag types (STAG)

```c
typedef struct { char _; } ___sel_Animal_get_snacks_t;
typedef struct { char _; } ___sel_Animal_feed_t;
```

Each method gets a **unique, empty struct type**. These are the selector types that `call()` matches against at compile time. They exist solely to give each method a distinct type that `_Generic` can dispatch on — they carry no data and cost nothing at runtime.

### 5. Selector struct + selector object (SSEL)

```c
typedef struct {
  ___sel_Animal_get_snacks_t get_snacks;
  ___sel_Animal_feed_t feed;
} Animal___sel_t;

static const Animal___sel_t Animal = {0};
```

The `Animal` variable is a zero-initialized struct. Its *type* carries the method tags. When you write `Animal.get_snacks`, C's `.` operator evaluates this to an expression of type `___sel_Animal_get_snacks_t` — and that's what `call()` inspects. The variable itself is never used at runtime; it exists to make the `Animal.method` syntax work through normal C struct access.

### 6. DynSD loop — register DynAnimal for vtable dispatch (dynamic traits only)

For dynamic traits, a self-include loop registers `DynAnimal` itself in the SD dispatch chain. This runs at **trait declaration time**, not impl registration time:

```c
typedef DynAnimal ___trait_sd_000000_ty;
typedef ___sel_Animal_get_snacks_t ___trait_sd_000000_sty;
typedef void (*___trait_sd_pair_000000_p)(___sel_Animal_get_snacks_t, DynAnimal);
static inline int ___trait_sd_fn_000000(DynAnimal *self) {   // vtable dispatch!
  return self->vt->get_snacks(self->self);
}
```

This is what makes `call(Animal.get_snacks, &dyn_animal)` work — the SD dispatch chain matches `DynAnimal` as the concrete type, and the wrapper does vtable dispatch. Without this, you'd need a separate dispatch path for trait objects.

---

## Selector objects and selector types

This is the key abstraction. Consider:

```c
call(Animal.get_snacks, &dog);
```

- `Animal` is the selector object (type: `Animal___sel_t`)
- `Animal.get_snacks` uses C's `.` operator on a struct → result has type `___sel_Animal_get_snacks_t`
- `call()` receives this type via `typeof(sel)` and matches it against registered SD entries

The selector object itself is **never used at runtime**. It exists purely to carry type information through the preprocessor and compiler. The `.` operator is just normal C syntax — no special macro magic is needed for the dotted notation.

---

## Impl registration

When you write:
```c
#define For Dog
#define Impl Animal
  def(int, get_snacks) { return self->snacks; }
  def(void, feed, int n) { self->snacks += n; }
#include "trait.h"
```

The second `#include` processes the impl. Here's what happens:

### Step 1: `defaults()` + `impl()` (dynamic traits only)

- `defaults()` — emits DFL wrapper functions for default methods
- `impl()` — emits the vtable object, `Dog_as_Animal()`, and `Dog_from_Animal()`

### Step 2: SDREG — register the concrete type

```c
typedef Dog ___trait_reg_000001_ty;        // tag this slot as Dog
AnimalSignature((Animal, SDREG))           // emit per-method SDREG wrappers
```

The SDREG wrappers are thin forwarding functions:
```c
static inline int ___trait_sd_fn_000001_Animal_get_snacks(Dog *self) {
  return Dog_Animal_get_snacks(self);
}
```

### Step 3: SD loop — emit per-method dispatch entries

The file self-includes with `___TRAIT_SD_ACTIVE` defined. This runs up to 8 times (one per method). Each iteration:

1. `___TRAIT_SD_SELECT(K, Animal)` — extracts the Kth method tuple from `AnimalSignature((Animal, MLIST))`
2. `___TRAIT_SD_EMIT(tuple)` — emits:

```c
typedef Dog ___trait_sd_004_ty;                            // concrete type tag
typedef ___sel_Animal_get_snacks_t ___trait_sd_004_sty;    // selector type tag
static inline int ___trait_sd_fn_004(Dog *self) {          // dispatch wrapper
  return Dog_Animal_get_snacks(self);
}
```

The 7-digit SD counter (`SD_C7`..`SD_C1`) gives each entry a unique number. The `_ty` typedef tags the concrete type, the `_sty` typedef tags the selector type, the `_asty` typedef tags the alias selector type, and the `_p`/`_apair` typedefs define function pointer pair types used by `_Generic` for dispatch matching.

### Step 4: ENFORCE (extends enforcement)

For traits with `extends()`, a static reference to the base trait's vtable is emitted:
```c
static void *const ___trait_enforce_Dog_Animal = (void *)&Dog_Animal_vtable;
```
If `Dog` hasn't implemented `Animal`, this symbol is undefined → **linker error**.

---

## Static dispatch (SD)

For concrete types passed directly to `call()`, the dispatch is **fully static** — resolved at compile time with zero runtime overhead.

```c
Dog dog = { .snacks = 5 };
call(Animal.get_snacks, &dog);
// Compiles to: Dog_Animal_get_snacks(&dog)  (direct call, no vtable)
```

The mechanism is standard C11 `_Generic` with the "extendible `_Generic`" pattern (see [Jackson Allan's article](https://github.com/JacksonAllan/CC/blob/main/articles/Better_C_Generics_Part_1_The_Extendible_Generic.md) for the foundational technique): recursive macros generate `_Generic` associations from slot 0 to the current counter value. The **fptr trick** dispatches on both selector type and concrete type simultaneously.

---

## The `call()` dispatch chain

```c
call(sel, obj, ...)
// expands to (C11):
_Generic(
  (void (*)(___TRAIT_TYPEOF(sel), ___TRAIT_TYPEOF(*(obj))))0,
  ___TRAIT_SD_SLOTS
  default: ERROR_trait_not_implemented_for_this_type
)(obj, ##__VA_ARGS__)
```

The controlling expression is a null function-pointer whose type encodes both the selector and object types: `void (*)(SelectorType, ConcreteType)`. Each registered SD entry provides a matching **pair type**:

```c
typedef void (*___trait_sd_pair_NNN)(SelectorType, ConcreteType);
typedef void (*___trait_sd_apair_NNN)(AliasSelectorType, ConcreteType);
```

The `_Generic` matches the controlling expression against these pair types. Recursive macros (R1–R6) generate all slots from 0 to the current counter value:

```c
_Generic(
  (void (*)(___TRAIT_TYPEOF(sel), ___TRAIT_TYPEOF(*(obj))))0,
  ___trait_sd_pair_001: ___trait_sd_fn_001,    // primary selector
  ___trait_sd_apair_001: ___trait_sd_fn_001,   // alias selector
  ___trait_sd_pair_002: ___trait_sd_fn_002,
  ___trait_sd_apair_002: ___trait_sd_fn_002,
  ...
  default: ERROR_trait_not_implemented_for_this_type
)
```

Each `___trait_sd_fn_NNN` wrapper is the one generated during SD registration (for concrete types) or DynSD registration (for DynTrait objects).

The compiler sees the entire `_Generic` at compile time, picks the matching branch, and discards all others. The result is a **direct function call** — no branches, no lookup, no overhead.

---

## Dynamic dispatch (DynSD)

For DynTrait objects, the same `call()` macro works:

```c
DynAnimal da = to_trait(Dog, Animal, &dog);
call(Animal.get_snacks, &da);
// Compiles to: da.vt->get_snacks(da.self)  (vtable indirection)
```

This works because the DynSD loop registered `DynAnimal` in the same SD dispatch chain. When the chain encounters `typeof(da) == DynAnimal`, it matches the DynSD wrapper, which does vtable dispatch internally.

The user doesn't need to know or care whether they're calling through a concrete type or a DynTrait — `call()` handles both uniformly.

---

## Default methods and override detection

### Overriding a default

When you write:
```c
#define For Dog
#define Impl Animal
#define Override_Dog_Animal_feed 1
  def(void, feed, int n) { self->snacks += n; }
#include "trait.h"
```

`def()` (or `constdef()` for `immutable` methods) generates a **strong function** with the same name `def()` would have produced — no `_ovr` suffix, no weak attribute:
```c
void Dog_Animal_feed(Dog *self, int n) {
  self->snacks += n;
}
```

The companion `#define Override_Dog_Animal_feed 1` (placed *before* the `#include "trait.h"` that processes the impl block) tells `defaults()` to skip generating the DFL wrapper for `feed`. Without it, `defaults()` would emit a `Dog_Animal_feed` wrapper of its own and you'd get a duplicate-definition error.

### The DFL wrapper

For methods declared with `default()`, the `defaults()` pass generates a wrapper function with the *same name* as what `def()` would generate — but only if the user has **not** opted out via `Override_<Type>_<Trait>_<Method>`:

```c
static inline void Dog_Animal_feed(void *self, int n) {
  // Fall back to default implementation
  DynAnimal _obj = {.self = self, .vt = &Default_Animal_vtable};
  Default_Animal_feed(&_obj, n);
}
```

If the user wrote `def()`/`constdef()` and set `Override_<Type>_<Trait>_<Method>` to `1`, the DFL wrapper is suppressed and the strong `def()` function (same name) is used directly. If the user wrote `def()`/`constdef()` without the Override flag, the strong implementation completely replaces this wrapper. If neither, the default body runs.

### Override detection — the PROBE trick

Whether `Override_<Type>_<Trait>_<Method>` is defined cannot be checked with `#ifdef Override_##Type##_##Method` — token-pasting inside `#ifdef` is not standard C (and not portable). Instead, `defaults()` uses a standard-C **PROBE** trick: a macro is defined to expand to a sentinel, the user's `Override_...` macro (if present) is pasted after it, and a third macro pattern-matches the result to detect whether the paste formed a known token sequence. This is pure preprocessor logic, fully standard C11, and requires no `__attribute__((weak))`.

### Static traits

For static traits (no `#define Dynamic`), the same override mechanism applies, but the default wrapper constructs a minimal `DynTrait{.self = ptr}` without a vtable pointer.

---

## Why a single `call()` macro

### The alternative that doesn't work

You might think: "why not let users write `Animal.get_snacks(&dog)` as a standalone expression?" The answer is that **C's preprocessor cannot intercept the `.` operator**.

`Animal` is a variable. `Animal.get_snacks` is a normal C struct member access. It evaluates to a value of type `___sel_Animal_get_snacks_t`. There is no macro expansion happening — it's just C syntax. You'd need a function call around it to intercept the result.

You might also think: "why not generate overloaded function names like `call_Animal_get_snacks(&dog)`?" This would require the preprocessor to generate a different macro for each method, but **the preprocessor cannot create user-callable macros** — `#define` is textual substitution, not code generation. The user would have to write the exact macro name that was defined.

### The `call()` design

`call(sel, obj)` solves both problems:

1. **`sel` is a C expression** (`Animal.get_snacks`) that uses normal struct access — no macro trickery needed
2. **`call()` is the single macro** that intercepts the result type via `typeof(sel)` and dispatches to the correct wrapper
3. **The wrapper** is generated by the library during impl registration, named by the global octal counter, and selected at compile time via `_Generic`

The user only needs to remember one macro: `call()`. The dotted notation (`Animal.get_snacks`) is just a convention enabled by the selector object's struct layout.

---

## The octal counter trick

The global counter is a 7-digit octal counter (`SD_C7`..`SD_C1`), giving `call()` up to 8⁷ = 2,097,152 SD dispatch slots. Each *method* of each impl consumes one slot, shared between the SD loop (concrete types) and DynSD loop (DynTrait types).

This technique is adapted from Jackson Allan's [extendible `_Generic`](https://github.com/JacksonAllan/CC/blob/main/articles/Better_C_Generics_Part_1_The_Extendible_Generic.md), which in turn credits the [Boost preprocessor counter](https://www.boost.org/doc/libs/1_66_0/boost/preprocessor/slot/detail/counter.hpp). The core idea: since the preprocessor can't loop, you encode a counter as a chain of `#define` digits and enumerate every possible increment as an `#if`/`#elif` branch — a preprocessor odometer.

### How the counter works

The counter is implemented as a chain of `#define`s:

```c
#define ___TRAIT_SD_C1 0    // least significant digit
#define ___TRAIT_SD_C2 0
#define ___TRAIT_SD_C3 0
#define ___TRAIT_SD_C4 0
#define ___TRAIT_SD_C5 0
#define ___TRAIT_SD_C6 0
#define ___TRAIT_SD_C7 0    // most significant digit (overflow guard)
```

Incrementing is done by a giant `#if`/`#elif` chain that pattern-matches the current value and redefines the digits. For example, when C1 is 0:

```c
#undef ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 1
```

When C1 overflows from 7 to 0, C2 is incremented:

```c
#undef ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 0
#undef ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 1
```

The result is a monotonically increasing counter that gives each registration a unique numeric ID — automatically, with no user interaction.

### The user-extensible aspect

The counter is **global and automatic** — the user never sees it or interacts with it. Every `#include "trait.h"` for an impl block silently claims the next counter value. This is what makes the system **open-world**: new impls in new translation units just work, because they register new SD slots that are automatically included in the dispatch chain.

The trade-off is that the counter is **monotonically increasing and never reset** — once a slot is claimed, it's used forever (within a translation unit).

---

## Limitations

| Limitation | Reason |
|------------|--------|
| **Max 8 methods per trait** | SD loop iterates 0–7 via `___TRAIT_SD_PASS`. `_Generic` nesting becomes impractical beyond 8. |
| **Max 2,097,152 SD dispatch slots** | 7-digit octal counter (SD_C7–SD_C1). Each method of each impl consumes one slot. |
| **GNU extensions** | `##__VA_ARGS__` and `__typeof__` (both C11, both with standard C23 equivalents).  In C23 mode, `##__VA_ARGS__` → `__VA_OPT__`, `__typeof__` → `typeof`, `__attribute__((unused))` → `[[maybe_unused]]` automatically. |
| **Compile-time linear scan** | `call()` checks all SD slots sequentially. Many registrations slow compilation (but runtime is a direct call). In the future, this will be optimized. |
| **Single translation unit** | SD/DynSD slots are file-scoped. Cross-TU dispatch requires the vtable (dynamic) path. |
