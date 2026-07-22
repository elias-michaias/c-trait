# API Reference

- [Defining traits](#defining-traits)
- [Implementing traits](#implementing-traits)
- [Calling methods](#calling-methods)
- [Default method bodies](#default-method-bodies)
- [Trait extension (inheritance)](#trait-extension-inheritance)
- [Parametric traits](#parametric-traits)
- [Associated types](#associated-types)
- [Forward declarations](#forward-declarations)

---

## Defining traits

A trait is defined by a **signature macro** and a declaration block:

```c
#define AnimalSignature(Self)                \
  require(Self, int,  get_snacks)            \
  default(Self, void, feed, int)             \
  default(immutable(Self), void, check)

#define Trait Animal
#include "trait.h"
```

The signature macro name must be `<TraitName>Signature`. It receives `Self` as its first parameter (plus any additional type parameters for parametric traits).

### Signature actions

| Macro | Purpose |
|-------|---------|
| `require(Self, Ret, Name, Args...)` | Method the implementor must provide |
| `default(Self, Ret, Name, Args...)` | Method with a default implementation |
| `immutable(Self)` | Marks the method as const (implement with `constdef()`) |
| `extends(Base, Self)` | Declares a supertrait constraint |

### Const traits

```c
#define ReaderSignature(Self)                \
  require(immutable(Self), int,  read)       \
  default(immutable(Self), void, describe)
#define Trait Reader
#include "trait.h"
```

## Implementing traits

```c
#define For TypeName
#define Impl TraitName
  def(RetType, method_name, Args...) { /* body */ }
  constdef(RetType, method_name, Args...) { /* body (const self) */ }
#include "trait.h"
```

- `def()` / `constdef()` — generates the function with correct naming (`Type_Trait_method`). Use `def()` for mutable methods, `constdef()` for `immutable(Self)` methods.
- To **override a default method**, use `def()`/`constdef()` as usual and define `#define Override_<Type>_<Trait>_<Method> 1` before the `#include "trait.h"` that processes this impl block, so that `defaults()` skips generating the DFL wrapper for that method (otherwise you get a duplicate definition).
- `#include "trait.h"` — finalizes the block: emits registration, auto-calls `impl()` for dynamic traits, undefines `For`/`Impl`.

## Calling methods

```c
// Static dispatch (concrete type pointer)
call(Animal.get_snacks, &dog);         // -> Dog_Animal_get_snacks(&dog)

// Dynamic dispatch (trait object pointer)
DynAnimal da = to_trait(Dog, Animal, &dog);
call(Animal.get_snacks, &da);          // -> da.vt->get_snacks(da.self)

// Call generated static functions directly (bypass dispatch)
Dog_Animal_get_snacks(&dog);
```

### Dispatch helpers

| Macro | Purpose |
|-------|---------|
| `to_trait(Type, Trait, &obj)` | Create a trait object (fat pointer) for dynamic dispatch |
| `from_trait(Type, Trait, obj)` | Recover the original concrete pointer |
| `new_trait(Type, Trait, { .field = val })` | Construct a trait object from a compound literal |

## Default method bodies

Default implementations use `Default` as the sentinel type:

```c
#define For Default
#define Impl Animal
  def(void, check) {
    (void)self;
    printf("(default) generic animal.\n");
  }
  def(void, feed, int amount) {
    (void)self;
    printf("(default) fed %d.\n", amount);
  }
#include "trait.h"
```

In default bodies, `self` is a `Dyn<Trait> *` (the trait object), so you can call other trait methods via `call(Trait.method, self, ...)` or the generated `Dyn<Trait>_method(*self, ...)` wrappers.

### Overriding a default

To override a default method for a specific type, use `def()`/`constdef()` in the impl block and define `Override_<Type>_<Trait>_<Method>` to `1` *before* the `#include "trait.h"` that processes the block:

```c
#define For Dog
#define Impl Animal
  def(int, get_snacks) { return self->snacks; }
  def(void, feed, int n) { self->snacks += n; }
#define Override_Dog_Animal_feed 1
#include "trait.h"
```

The `Override_Dog_Animal_feed` macro tells `defaults()` to skip generating the DFL wrapper for `feed`, so the `def()` function (which has the same name `Dog_Animal_feed`) is used instead. The detection uses a standard-C PROBE trick — no `#ifdef` with token pasting (which isn't possible in standard C). Forgetting the `Override_` define results in a duplicate-definition error.

**Static traits** also support default methods — the override mechanism works the same way (same `Override_<Type>_<Trait>_<Method>` requirement), but there is no `DynTrait` to call through in the default body.

## Trait extension (inheritance)

```c
#define PetSignature(Self) \
  extends(Animal, Self) \
  require(Self, void, play)
#define Dynamic
#define Trait Pet
#include "trait.h"
```

`extends()` is **purely declarative** — no methods are copied. Each trait is implemented independently. The linker enforces that the base trait is implemented: if `Dog` implements `Pet` but not `Animal`, you get an undefined symbol error at link time.

Multiple supertraits are supported:

```c
#define IntroducibleSignature(Self) \
  extends(Greetable, Self) \
  extends(Describable, Self) \
  require(immutable(Self), void, introduce, const char *)
```

## Parametric traits

Traits can take additional type parameters. Each instantiation is a separate trait:

```c
#define ContainerSignature(Self, T) \
  require(Self, T, get)         \
  require(Self, void, set, T)

// Create concrete traits via <Name>Signature aliases
#define Container_intSignature(Self) ContainerSignature(Self, int)
#define Dynamic
#define Trait Container_int
#include "trait.h"

#define Container_strSignature(Self) ContainerSignature(Self, const char *)
#define Dynamic
#define Trait Container_str
#include "trait.h"
```

## Associated types

Use preprocessor defines to specialize a trait per implementation:

```c
#define ContainerSignature(Self) \
  require(Self, int, push, Container_Item) \
  require(Self, int, pop)
#define Trait Container
#include "trait.h"

#define For IntContainer
#define Impl Container
#define Container_Item int
  def(int, push, int a1) { /* ... */ }
  def(int, pop) { /* ... */ }
#include "trait.h"
#undef Container_Item

#define For StrContainer
#define Impl Container
#define Container_Item const char *
  def(int, push, const char *a1) { /* ... */ }
  def(int, pop) { /* ... */ }
#include "trait.h"
#undef Container_Item
```

## Forward declarations

Normally, `call()` is not available inside `def()` bodies because SD entries haven't been emitted yet. The `Forward` flag fixes this:

```c
#define For Dog
#define Impl Animal
#define Forward
#include "trait.h"
  def(int, get_snacks) {
    return self->snacks;
  }
  def(void, feed, int amount) {
    int before = call(Animal.get_snacks, self);  // works!
    self->snacks += amount;
  }
#include "trait.h"
```

The first `#include` with `Forward` pre-emits extern declarations and SD entries, so `call()` resolves correctly inside the function bodies.
