// Auto-impl: second #include "trait.h" triggers impl()/cleanup
#ifdef For
#ifdef Impl
#ifdef ___TRAIT_SD_ACTIVE
#define Self For
// ═══════════════════════════════════════════════════════════════════════════════
// SD SELF-INCLUDE LOOP BODY
//
// This branch is entered during the SD loop iteration.  For and Impl are still
// defined.  ___TRAIT_SD_PASS is the current method index (0, 1, 2, ...).
//
// Each iteration:
//   1. Check sentinel → if past last method, stop looping.
//   2. Emit SD registration (typedef + wrapper function) for the current method.
//   4. Increment pass counter (___TRAIT_SD_PASS).
//   4. Increment pass counter (___TRAIT_SD_PASS).
//   5. Self-include trait.h for the next iteration.
// ═══════════════════════════════════════════════════════════════════════════════
#if !___TRAIT_SD_IS_STOP(___TRAIT_SD_PASS, Impl)
// Emit SD slot: typedef concrete type, typedef selector type, wrapper function
___TRAIT_SD_EMIT(___TRAIT_SD_SELECT(___TRAIT_SD_PASS, Impl))
// Increment 7-digit octal SD counter
#if   ___TRAIT_SD_C1 == 0
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 1
#elif ___TRAIT_SD_C1 == 1
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 2
#elif ___TRAIT_SD_C1 == 2
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 3
#elif ___TRAIT_SD_C1 == 3
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 4
#elif ___TRAIT_SD_C1 == 4
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 5
#elif ___TRAIT_SD_C1 == 5
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 6
#elif ___TRAIT_SD_C1 == 6
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 7
#elif ___TRAIT_SD_C1 == 7
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 0
#if   ___TRAIT_SD_C2 == 0
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 1
#elif ___TRAIT_SD_C2 == 1
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 2
#elif ___TRAIT_SD_C2 == 2
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 3
#elif ___TRAIT_SD_C2 == 3
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 4
#elif ___TRAIT_SD_C2 == 4
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 5
#elif ___TRAIT_SD_C2 == 5
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 6
#elif ___TRAIT_SD_C2 == 6
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 7
#elif ___TRAIT_SD_C2 == 7
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 0
#if   ___TRAIT_SD_C3 == 0
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 1
#elif ___TRAIT_SD_C3 == 1
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 2
#elif ___TRAIT_SD_C3 == 2
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 3
#elif ___TRAIT_SD_C3 == 3
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 4
#elif ___TRAIT_SD_C3 == 4
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 5
#elif ___TRAIT_SD_C3 == 5
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 6
#elif ___TRAIT_SD_C3 == 6
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 7
#elif ___TRAIT_SD_C3 == 7
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 0
#if   ___TRAIT_SD_C4 == 0
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 1
#elif ___TRAIT_SD_C4 == 1
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 2
#elif ___TRAIT_SD_C4 == 2
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 3
#elif ___TRAIT_SD_C4 == 3
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 4
#elif ___TRAIT_SD_C4 == 4
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 5
#elif ___TRAIT_SD_C4 == 5
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 6
#elif ___TRAIT_SD_C4 == 6
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 7
#elif ___TRAIT_SD_C4 == 7
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 0
#if   ___TRAIT_SD_C5 == 0
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 1
#elif ___TRAIT_SD_C5 == 1
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 2
#elif ___TRAIT_SD_C5 == 2
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 3
#elif ___TRAIT_SD_C5 == 3
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 4
#elif ___TRAIT_SD_C5 == 4
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 5
#elif ___TRAIT_SD_C5 == 5
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 6
#elif ___TRAIT_SD_C5 == 6
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 7
#elif ___TRAIT_SD_C5 == 7
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 0
#if   ___TRAIT_SD_C6 == 0
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 1
#elif ___TRAIT_SD_C6 == 1
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 2
#elif ___TRAIT_SD_C6 == 2
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 3
#elif ___TRAIT_SD_C6 == 3
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 4
#elif ___TRAIT_SD_C6 == 4
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 5
#elif ___TRAIT_SD_C6 == 5
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 6
#elif ___TRAIT_SD_C6 == 6
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 7
#elif ___TRAIT_SD_C6 == 7
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 0
#if   ___TRAIT_SD_C7 == 0
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 1
#elif ___TRAIT_SD_C7 == 1
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 2
#elif ___TRAIT_SD_C7 == 2
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 3
#elif ___TRAIT_SD_C7 == 3
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 4
#elif ___TRAIT_SD_C7 == 4
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 5
#elif ___TRAIT_SD_C7 == 5
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 6
#elif ___TRAIT_SD_C7 == 6
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 7
#elif ___TRAIT_SD_C7 == 7
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 0
#error "c-trait: too many SD slots (max 2097152)"
#endif
#endif
#endif
#endif
#endif
#endif
#endif
// Increment pass counter (max 8 methods per trait)
#if   ___TRAIT_SD_PASS == 0
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 1
#elif ___TRAIT_SD_PASS == 1
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 2
#elif ___TRAIT_SD_PASS == 2
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 3
#elif ___TRAIT_SD_PASS == 3
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 4
#elif ___TRAIT_SD_PASS == 4
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 5
#elif ___TRAIT_SD_PASS == 5
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 6
#elif ___TRAIT_SD_PASS == 6
#undef  ___TRAIT_SD_PASS
#define ___TRAIT_SD_PASS 7
#elif ___TRAIT_SD_PASS == 7
#error "c-trait: too many methods per trait for SD (max 8)"
#endif
// Self-include for next iteration
#include "trait.h"
#endif // !___TRAIT_SD_IS_STOP
// ═══════════════════════════════════════════════════════════════════════════════
// END SD LOOP
// ═══════════════════════════════════════════════════════════════════════════════
#elif defined(___TRAIT_DYNSD_ACTIVE)
// ═══════════════════════════════════════════════════════════════════════════════
// DYNSD SELF-INCLUDE LOOP BODY
//
// This branch emits SD entries for DynTraitname (the trait object type), so
// that call(Animal.method, &dyn_obj) dispatches through the vtable.
// For/Impl are still defined.  The SD counter is shared with the SD loop.
// ═══════════════════════════════════════════════════════════════════════════════
#if !___TRAIT_SD_IS_STOP(___TRAIT_DYNSD_PASS, Impl)
// Emit DynSD slot: DynImpl as concrete type, selector type, vtable wrapper
___TRAIT_DYNSD_EMIT(___TRAIT_SD_SELECT(___TRAIT_DYNSD_PASS, Impl))
// Increment 6-digit octal SD counter (shared with SD loop)
#if   ___TRAIT_SD_C1 == 0
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 1
#elif ___TRAIT_SD_C1 == 1
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 2
#elif ___TRAIT_SD_C1 == 2
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 3
#elif ___TRAIT_SD_C1 == 3
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 4
#elif ___TRAIT_SD_C1 == 4
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 5
#elif ___TRAIT_SD_C1 == 5
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 6
#elif ___TRAIT_SD_C1 == 6
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 7
#elif ___TRAIT_SD_C1 == 7
#undef  ___TRAIT_SD_C1
#define ___TRAIT_SD_C1 0
#if   ___TRAIT_SD_C2 == 0
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 1
#elif ___TRAIT_SD_C2 == 1
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 2
#elif ___TRAIT_SD_C2 == 2
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 3
#elif ___TRAIT_SD_C2 == 3
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 4
#elif ___TRAIT_SD_C2 == 4
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 5
#elif ___TRAIT_SD_C2 == 5
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 6
#elif ___TRAIT_SD_C2 == 6
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 7
#elif ___TRAIT_SD_C2 == 7
#undef  ___TRAIT_SD_C2
#define ___TRAIT_SD_C2 0
#if   ___TRAIT_SD_C3 == 0
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 1
#elif ___TRAIT_SD_C3 == 1
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 2
#elif ___TRAIT_SD_C3 == 2
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 3
#elif ___TRAIT_SD_C3 == 3
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 4
#elif ___TRAIT_SD_C3 == 4
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 5
#elif ___TRAIT_SD_C3 == 5
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 6
#elif ___TRAIT_SD_C3 == 6
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 7
#elif ___TRAIT_SD_C3 == 7
#undef  ___TRAIT_SD_C3
#define ___TRAIT_SD_C3 0
#if   ___TRAIT_SD_C4 == 0
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 1
#elif ___TRAIT_SD_C4 == 1
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 2
#elif ___TRAIT_SD_C4 == 2
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 3
#elif ___TRAIT_SD_C4 == 3
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 4
#elif ___TRAIT_SD_C4 == 4
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 5
#elif ___TRAIT_SD_C4 == 5
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 6
#elif ___TRAIT_SD_C4 == 6
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 7
#elif ___TRAIT_SD_C4 == 7
#undef  ___TRAIT_SD_C4
#define ___TRAIT_SD_C4 0
#if   ___TRAIT_SD_C5 == 0
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 1
#elif ___TRAIT_SD_C5 == 1
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 2
#elif ___TRAIT_SD_C5 == 2
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 3
#elif ___TRAIT_SD_C5 == 3
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 4
#elif ___TRAIT_SD_C5 == 4
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 5
#elif ___TRAIT_SD_C5 == 5
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 6
#elif ___TRAIT_SD_C5 == 6
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 7
#elif ___TRAIT_SD_C5 == 7
#undef  ___TRAIT_SD_C5
#define ___TRAIT_SD_C5 0
#if   ___TRAIT_SD_C6 == 0
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 1
#elif ___TRAIT_SD_C6 == 1
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 2
#elif ___TRAIT_SD_C6 == 2
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 3
#elif ___TRAIT_SD_C6 == 3
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 4
#elif ___TRAIT_SD_C6 == 4
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 5
#elif ___TRAIT_SD_C6 == 5
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 6
#elif ___TRAIT_SD_C6 == 6
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 7
#elif ___TRAIT_SD_C6 == 7
#undef  ___TRAIT_SD_C6
#define ___TRAIT_SD_C6 0
#if   ___TRAIT_SD_C7 == 0
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 1
#elif ___TRAIT_SD_C7 == 1
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 2
#elif ___TRAIT_SD_C7 == 2
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 3
#elif ___TRAIT_SD_C7 == 3
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 4
#elif ___TRAIT_SD_C7 == 4
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 5
#elif ___TRAIT_SD_C7 == 5
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 6
#elif ___TRAIT_SD_C7 == 6
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 7
#elif ___TRAIT_SD_C7 == 7
#undef  ___TRAIT_SD_C7
#define ___TRAIT_SD_C7 0
#error "c-trait: too many SD slots (max 2097152)"
#endif
#endif
#endif
#endif
#endif
#endif
#endif
// Increment DynSD pass counter (max 8 methods per trait)
#if   ___TRAIT_DYNSD_PASS == 0
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 1
#elif ___TRAIT_DYNSD_PASS == 1
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 2
#elif ___TRAIT_DYNSD_PASS == 2
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 3
#elif ___TRAIT_DYNSD_PASS == 3
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 4
#elif ___TRAIT_DYNSD_PASS == 4
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 5
#elif ___TRAIT_DYNSD_PASS == 5
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 6
#elif ___TRAIT_DYNSD_PASS == 6
#undef  ___TRAIT_DYNSD_PASS
#define ___TRAIT_DYNSD_PASS 7
#elif ___TRAIT_DYNSD_PASS == 7
#error "c-trait: too many methods per trait for DynSD (max 8)"
#endif
// Self-include for next iteration
#include "trait.h"
#endif // !___TRAIT_SD_IS_STOP
// ═══════════════════════════════════════════════════════════════════════════════
// END DYNSD LOOP
// ═══════════════════════════════════════════════════════════════════════════════
#else // !___TRAIT_SD_ACTIVE && !___TRAIT_DYNSD_ACTIVE — normal impl registration
#define ___TRAIT_IS_DEFAULT_FOR_Default ___TRAIT_PROBE()
#define ___TRAIT_EXPAND(x) x
#define ___TRAIT_IS_FOR_DEFAULT()                                                \
  ___TRAIT_CHECK(___TRAIT_EXPAND(___TRAIT_CAT(___TRAIT_IS_DEFAULT_FOR_, For)))
#if ___TRAIT_IS_FOR_DEFAULT()
#undef For
#undef Impl
#else

#ifdef Forward
// ═════════════════════════════════════════════════════════════════════════════
// FORWARD DECLARATION PATH
//
// Usage:
//   #define For Dog
//   #define Impl Animal
//   #define Forward
//   #include "trait.h"          ← this path: FWDDECL + SD/DynSD loops
//     int def(get_snacks) { call(Animal.get_snacks, self); }
//     void def(feed, int amount) { ... }
//   #include "trait.h"          ← normal path: defaults/impl/counter/enforce
//
// Emits extern declarations for each impl function, then runs SD/DynSD loops
// so that call() resolves to the correct wrapper at compile time.  The actual
// function bodies (def()) follow between the two includes.
// ═════════════════════════════════════════════════════════════════════════════
___TRAIT_PASTE(Impl, Signature)((Impl, FWDDECL))

// ── SD loop: emit type info + wrapper functions for call() ──────────────────
#define ___TRAIT_SD_ACTIVE 1
#define ___TRAIT_SD_PASS 0
#include "trait.h"
#undef ___TRAIT_SD_ACTIVE
#undef ___TRAIT_SD_PASS

// Set flag so the second #include "trait.h" skips SD loop.
#define ___TRAIT_FWDIMPL_DONE 1
#undef Forward

#else
// ═════════════════════════════════════════════════════════════════════════════
// NORMAL PATH (also serves as post-forward-declare path)
//
// When ___TRAIT_FWDIMPL_DONE is set (second #include after Forward),
// defaults/impl/counter/enforce still run but SD/DynSD loops are skipped.
// When ___TRAIT_IS_STATIC_CURRENT is set, defaults/impl/DynSD/enforce are skipped.
// ═════════════════════════════════════════════════════════════════════════════
#ifndef ___TRAIT_IS_STATIC_CURRENT
defaults();
impl()
#else
static_defaults()
#endif


// ── SD loop (skip if already emitted in forward-declare pass) ────────────
#ifndef ___TRAIT_FWDIMPL_DONE

// ── Start SD (selector-based dispatch) self-include loop ─────────────────
#define ___TRAIT_SD_ACTIVE 1
#define ___TRAIT_SD_PASS 0
#include "trait.h"
#undef ___TRAIT_SD_ACTIVE
#undef ___TRAIT_SD_PASS
// ── End SD loop ──────────────────────────────────────────────────────────

#else
#undef ___TRAIT_FWDIMPL_DONE
#endif

// ── Enforce extends: verify base traits are implemented ─────────────────────
// Skip for static traits (no vtable to reference for enforcement).
#ifndef ___TRAIT_IS_STATIC_CURRENT
___TRAIT_PASTE(Impl, Signature)((Impl, ENFORCE))
#endif

#undef For
#undef Impl
#endif // Forward
#endif
#undef ___TRAIT_IS_DEFAULT_FOR_Default
#undef ___TRAIT_EXPAND
#undef ___TRAIT_IS_FOR_DEFAULT
#endif // !___TRAIT_SD_ACTIVE && !___TRAIT_DYNSD_ACTIVE
#endif
#endif

// ── Reinclude: trait definition ─────────────────────────────────────────────
// Usage:
//   #define Trait Animal
//   #include "trait.h"
//
// Equivalent to the single-line `trait(Animal);` macro call, but uses the
// reinclude mechanism.  Because this section runs as preprocessor directives
// (not macro expansion), it can emit #define/#undef — enabling future
// automation of per-trait helpers that ordinary macros cannot produce.
//
// ___TRAIT_TRAIT_PASTE_(x) pastes the LITERAL token `Trait` (which is NOT a
// macro parameter, so ## uses it as-is) with the expanded trait name.
// This avoids the problem where `___TRAIT_PASTE(Trait, X)` would expand
// the macro `Trait` before pasting.
// ─────────────────────────────────────────────────────────────────────────────
#ifdef Trait
#ifndef For

// ── Static trait detection ───────────────────────────────────────────────────
// Traits are static by default (no vtable, no DynTrait, no dynamic dispatch).
// #define Dynamic before #define Trait opts into full dynamic features:
// vtable, DynTrait, DFL defaults, impl(), ENFORCE, DynSD.
// The flag persists until the next trait definition clears it.
#undef ___TRAIT_IS_STATIC_CURRENT
#ifndef Dynamic
#define ___TRAIT_IS_STATIC_CURRENT
#else
#undef Dynamic
#endif

#ifndef ___TRAIT_IS_STATIC_CURRENT
typedef struct {
  ___TRAIT_TRAIT_PASTE(Trait)((Trait, FN))
} glue(Trait, _vtable);
typedef struct {
  void *self;
  const glue(Trait, _vtable) *vt;
} glue(Dyn, Trait);
#else
// Static: minimal DynTrait (for default function signatures, no vtable)
typedef struct { void *self; } glue(Dyn, Trait);
#endif
___TRAIT_TRAIT_PASTE(Trait)((Trait, STAG))
typedef struct {
  ___TRAIT_TRAIT_PASTE(Trait)((Trait, SSEL))
} glue(Trait, ___sel_t);
___TRAIT_UNUSED static ___TRAIT_CONSTEXPR glue(Trait, ___sel_t)
    Trait = {0};

// ── DynSD: emit vtable-dispatch wrappers at trait declaration ────────────
// Registered once per trait (not per-impl) so that _Generic pair types
// remain unique — all DynSD entries for the same trait produce identical
// pair types (sel_type, DynTrait), and _Generic forbids duplicates.
#ifndef ___TRAIT_IS_STATIC_CURRENT
#define For void
#define Impl Trait
#define ___TRAIT_DYNSD_ACTIVE 1
#define ___TRAIT_DYNSD_PASS 0
#include "trait.h"
#undef ___TRAIT_DYNSD_ACTIVE
#undef ___TRAIT_DYNSD_PASS
#undef Impl
#undef For
#endif

#undef Trait

#endif
#endif

#ifndef TRAIT_ALT_H
#define TRAIT_ALT_H

// GNU C extensions used: ##__VA_ARGS__ (replaced by __VA_OPT__ in C23),
// __typeof__ (replaced by typeof in C23).  No __attribute__((weak)) —
// default method overrides use the PROBE trick + user-declared
// #define Override_<Type>_<Trait>_<Method> 1 instead.

// -----------------------------------------------------------------------------
// Pasting / concatenation helpers
// -----------------------------------------------------------------------------
#define glue_(a, b) a##b
#define glue(a, b) glue_(a, b)
#define glue3(a, b, c) glue(glue(a, b), c)
#define glue4(a, b, c, d) glue(glue3(a, b, c), d)
#define glue5(a, b, c, d, e) glue(glue4(a, b, c, d), e)
#define glue6(a, b, c, d, e, f) glue(glue5(a, b, c, d, e), f)
#define glue7(a, b, c, d, e, f, g) glue(glue6(a, b, c, d, e, f), g)
#define glue8(a, b, c, d, e, f, g, h) glue(glue7(a, b, c, d, e, f, g), h)
#define glue9(a, b, c, d, e, f, g, h, i) glue(glue8(a, b, c, d, e, f, g, h), i)

// Independent paste pair for Dyn prefix — avoids blue-paint conflict with glue.
#define ___TRAIT_DYN_(a, b) a##b
#define ___TRAIT_DYN(T) ___TRAIT_DYN_(Dyn, T)

#define ___TRAIT_PASTE_HELPER(a, b) a##b
#define ___TRAIT_PASTE(a, b) ___TRAIT_PASTE_HELPER(a, b)

// -----------------------------------------------------------------------------
// Override detection (PROBE trick — 100% standard C)
//
// When a user writes redef()/credef() for a default method, they also define:
//   #define Override_<Type>_<Trait>_<Method> 1
// before the #include "trait.h" that processes the impl block.
// The trait name is included to avoid collisions when a type implements
// two traits with the same method name.
// The PROBE trick detects whether that macro is defined, without requiring
// #ifdef (which can't use token pasting).
//
// ___TRAIT_IS_OVR(For, Trait, Name) expands to 1 if overridden, 0 if not.
// ___TRAIT_IF_OVR(For, Trait, Name, Then, Else, ...) expands to Then if
//   overridden, Else(__VA_ARGS__) if not.
// -----------------------------------------------------------------------------
#define ___TRAIT_OVR_PROBE(x) x, 1
#define ___TRAIT_GET_2ND(x, y, ...) y
#define ___TRAIT_IS_PROBE(...) ___TRAIT_GET_2ND(__VA_ARGS__, 0)

#define ___TRAIT_OVR_NAME_(CType, Trait, Name) glue6(Override_, CType, _, Trait, _, Name)
#define ___TRAIT_OVR_NAME(CType, Trait, Name) ___TRAIT_OVR_NAME_(CType, Trait, Name)

#define ___TRAIT_OVR_TEST(x) ___TRAIT_OVR_TEST_DISPATCH(x)
#define ___TRAIT_OVR_TEST_DISPATCH(x) glue(___TRAIT_OVR_TEST_DISPATCH_, x)
#define ___TRAIT_OVR_TEST_DISPATCH_1 ___TRAIT_OVR_PROBE(~)

#define ___TRAIT_IS_OVR(CType, Trait, Name) \
  ___TRAIT_IS_PROBE(___TRAIT_OVR_TEST(___TRAIT_OVR_NAME(CType, Trait, Name)))

// The deferral (Else receives __VA_ARGS__) prevents prescan from
// expanding the DFL macro body too early (braced initializers contain
// commas that would break macro argument parsing).
#define ___TRAIT_IF_OVR(CType, Trait, Name, Then, Else, ...) \
  glue(___TRAIT_OVR_BRANCH_, ___TRAIT_IS_OVR(CType, Trait, Name))(Then, Else, __VA_ARGS__)
#define ___TRAIT_OVR_BRANCH_0(Then, Else, ...) Else(__VA_ARGS__)
#define ___TRAIT_OVR_BRANCH_1(Then, Else, ...) Then

// Paste the expanded trait name with the literal suffix `Signature`.
// Because `x` is expanded before substitution, `___TRAIT_TRAIT_PASTE(Animal)`
// produces `AnimalSignature` — matching the user-defined macro name.
// This avoids the problem where `___TRAIT_PASTE(Trait, x)` would expand
// the macro `Trait` before pasting.
#define ___TRAIT_TRAIT_PASTE_(x) x##Signature
#define ___TRAIT_TRAIT_PASTE(x) ___TRAIT_TRAIT_PASTE_(x)

// -----------------------------------------------------------------------------
// Compiler portability
// -----------------------------------------------------------------------------
// C23 mode detection
#if defined(__STDC_VERSION__) && __STDC_VERSION__ >= 202311L
#define ___TRAIT_C23 1
#else
#define ___TRAIT_C23 0
#endif

#if ___TRAIT_C23
#define ___TRAIT_UNUSED [[maybe_unused]]
#define ___TRAIT_TYPEOF typeof
#define ___TRAIT_CONSTEXPR const
#elif defined(__GNUC__) || defined(__clang__)
#define ___TRAIT_UNUSED __attribute__((__unused__))
#define ___TRAIT_TYPEOF __typeof__
#define ___TRAIT_CONSTEXPR const
#else
#define ___TRAIT_UNUSED
#define ___TRAIT_TYPEOF __typeof__
#define ___TRAIT_CONSTEXPR
#endif

// -----------------------------------------------------------------------------
// Small macro utilities
// -----------------------------------------------------------------------------
#define ___TRAIT_PROBE() ~, 1,
#define ___TRAIT_SECOND(a, b, ...) b
#define ___TRAIT_CHECK(...) ___TRAIT_SECOND(__VA_ARGS__, 0)

#define ___TRAIT_CAT(a, b) glue(a, b)

// Detect whether a token macro is defined to 1.
#define ___TRAIT_IS_DEFINED(x) ___TRAIT_CHECK(___TRAIT_CAT(___TRAIT_DEF_CHECK_, x))
#define ___TRAIT_DEF_CHECK_1 ___TRAIT_PROBE()

// Count arguments in a variadic list up to 4.
#define ___TRAIT_NARG_IMPL(_0, _1, _2, _3, _4, N, ...) N
#define ___TRAIT_NARG(...) ___TRAIT_NARG_IMPL(dummy, ##__VA_ARGS__, 4, 3, 2, 1, 0)

// -----------------------------------------------------------------------------
// Self-spec tuples
//   mutable:   (NameSignature, ACTION)
//   immutable:  (___TRAIT_IMMUTABLE, (NameSignature, ACTION))
// -----------------------------------------------------------------------------
#define ___TRAIT_IMMUTABLE ___TRAIT_IMMUTABLE
#define immutable(SelfSpec) (___TRAIT_IMMUTABLE, SelfSpec)

#define ___TRAIT_SELF_FIRST(a, ...) a
#define ___TRAIT_SELF_SECOND(a, b, ...) b
#define ___TRAIT_IS_IMMUTABLE_TOKEN____TRAIT_IMMUTABLE ___TRAIT_PROBE()
#define ___TRAIT_IS_IMMUTABLE(SelfSpec)                                          \
  ___TRAIT_CHECK(                                                                \
      ___TRAIT_CAT(___TRAIT_IS_IMMUTABLE_TOKEN_, ___TRAIT_SELF_FIRST SelfSpec))

#define ___TRAIT_SELF_UNWRAP(SelfSpec)                                           \
  glue(___TRAIT_SELF_UNWRAP_, ___TRAIT_IS_IMMUTABLE(SelfSpec))(SelfSpec)
#define ___TRAIT_SELF_UNWRAP_0(SelfSpec) SelfSpec
#define ___TRAIT_SELF_UNWRAP_1(SelfSpec) ___TRAIT_SELF_SECOND SelfSpec

#define ___TRAIT_GET_TYPE_IMPL(Type, Action) Type
#define ___TRAIT_GET_TYPE(SelfSpec) ___TRAIT_GET_TYPE_IMPL SelfSpec

#define ___TRAIT_GET_ACTION_IMPL(Type, Action) Action
#define ___TRAIT_GET_ACTION(SelfSpec) ___TRAIT_GET_ACTION_IMPL SelfSpec

#define ___TRAIT_SPEC_TYPE(SelfSpec) ___TRAIT_GET_TYPE(___TRAIT_SELF_UNWRAP(SelfSpec))
#define ___TRAIT_SPEC_ACTION(SelfSpec)                                           \
  ___TRAIT_GET_ACTION(___TRAIT_SELF_UNWRAP(SelfSpec))

// -----------------------------------------------------------------------------
// Trait name detection for the Default sentinel in impl blocks
// -----------------------------------------------------------------------------
#define ___TRAIT_IS_DEFAULT_TOKEN_Default ___TRAIT_PROBE()
#define ___TRAIT_IS_DEFAULT(For)                                                 \
  ___TRAIT_CHECK(___TRAIT_CAT(___TRAIT_IS_DEFAULT_TOKEN_, For))

#define ___TRAIT_IS_VOID_token_void ___TRAIT_PROBE()
#define ___TRAIT_IS_VOID(Ret) ___TRAIT_CHECK(___TRAIT_CAT(___TRAIT_IS_VOID_token_, Ret))

// -----------------------------------------------------------------------------
// Vtable / trait object helper names
// -----------------------------------------------------------------------------
#define ___TRAIT_VTTYPE(I) glue(I, _vtable)
#define ___TRAIT_VTNAME(F, I) glue4(F, _, I, _vtable)

// -----------------------------------------------------------------------------
// Method metadata names (reserved for future use)
// -----------------------------------------------------------------------------

// -----------------------------------------------------------------------------
// Dispatch by action
// -----------------------------------------------------------------------------
#define trait_default(SelfSpec, Ret, Name, ...)                                \
  glue4(___TRAIT_ACT_, ___TRAIT_SPEC_ACTION(SelfSpec), _DEFAULT_,                  \
        ___TRAIT_IS_IMMUTABLE(SelfSpec))(___TRAIT_SPEC_TYPE(SelfSpec), Ret, Name,  \
                                       ##__VA_ARGS__)

#define trait_require(SelfSpec, Ret, Name, ...)                                \
  glue4(___TRAIT_ACT_, ___TRAIT_SPEC_ACTION(SelfSpec), _REQUIRE_,                  \
        ___TRAIT_IS_IMMUTABLE(SelfSpec))(___TRAIT_SPEC_TYPE(SelfSpec), Ret, Name,  \
                                       ##__VA_ARGS__)

#define default(SelfSpec, Ret, Name, ...)                                      \
  trait_default(SelfSpec, Ret, Name, ##__VA_ARGS__)
#define require(SelfSpec, Ret, Name, ...)                                      \
  trait_require(SelfSpec, Ret, Name, ##__VA_ARGS__)

// -----------------------------------------------------------------------------
// Actions: FN (vtable fields)
// -----------------------------------------------------------------------------
#define ___TRAIT_ACT_FN_REQUIRE_0(Type, Ret, Name, ...)                          \
  Ret (*Name)(void *, ##__VA_ARGS__);
#define ___TRAIT_ACT_FN_REQUIRE_1(Type, Ret, Name, ...)                          \
  Ret (*Name)(const void *, ##__VA_ARGS__);
#define ___TRAIT_ACT_FN_DEFAULT_0(Type, Ret, Name, ...)                          \
  Ret (*Name)(void *, ##__VA_ARGS__);
#define ___TRAIT_ACT_FN_DEFAULT_1(Type, Ret, Name, ...)                          \
  Ret (*Name)(const void *, ##__VA_ARGS__);

// -----------------------------------------------------------------------------
// Actions: STAG (per-method unique tag typedef for selector struct)
// -----------------------------------------------------------------------------
#define ___TRAIT_ACT_STAG_REQUIRE_0(Type, Ret, Name, ...)                        \
  typedef struct { char _; } glue5(___sel_, Type, _, Name, _t);
#define ___TRAIT_ACT_STAG_REQUIRE_1(Type, Ret, Name, ...)                        \
  typedef struct { char _; } glue5(___sel_, Type, _, Name, _t);
#define ___TRAIT_ACT_STAG_DEFAULT_0(Type, Ret, Name, ...)                        \
  typedef struct { char _; } glue5(___sel_, Type, _, Name, _t);
#define ___TRAIT_ACT_STAG_DEFAULT_1(Type, Ret, Name, ...)                        \
  typedef struct { char _; } glue5(___sel_, Type, _, Name, _t);

// -----------------------------------------------------------------------------
// Actions: SSEL (selector struct field for each method)
// -----------------------------------------------------------------------------
#define ___TRAIT_ACT_SSEL_REQUIRE_0(Type, Ret, Name, ...)                        \
  glue5(___sel_, Type, _, Name, _t) Name;
#define ___TRAIT_ACT_SSEL_REQUIRE_1(Type, Ret, Name, ...)                        \
  glue5(___sel_, Type, _, Name, _t) Name;
#define ___TRAIT_ACT_SSEL_DEFAULT_0(Type, Ret, Name, ...)                        \
  glue5(___sel_, Type, _, Name, _t) Name;
#define ___TRAIT_ACT_SSEL_DEFAULT_1(Type, Ret, Name, ...)                        \
  glue5(___sel_, Type, _, Name, _t) Name;

// -----------------------------------------------------------------------------
// Actions: MLIST (emit comma-separated method tuples for SD iteration)
//
// Each require/default emits: , (ConstFlag, Ret, Name, ExtraArgs...)
// The leading comma ensures proper separation between tuples.
// The ConstFlag (0=mutable, 1=immutable) is derived from the action suffix.
// -----------------------------------------------------------------------------
#define ___TRAIT_ACT_MLIST_REQUIRE_0(Type, Ret, Name, ...)                       \
  , (Type, 0, Ret, Name, ##__VA_ARGS__)
#define ___TRAIT_ACT_MLIST_REQUIRE_1(Type, Ret, Name, ...)                       \
  , (Type, 1, Ret, Name, ##__VA_ARGS__)
#define ___TRAIT_ACT_MLIST_DEFAULT_0(Type, Ret, Name, ...)                       \
  , (Type, 0, Ret, Name, ##__VA_ARGS__)
#define ___TRAIT_ACT_MLIST_DEFAULT_1(Type, Ret, Name, ...)                       \
  , (Type, 1, Ret, Name, ##__VA_ARGS__)

// extends is purely declarative — no method tuples propagated to MLIST.
#define ___TRAIT_EXTENDS_MLIST(Base, SelfSpec) /* no-op */

// -----------------------------------------------------------------------------
// Actions: BIND (vtable initializer)
// -----------------------------------------------------------------------------
#define ___TRAIT_ACT_BIND_REQUIRE_0(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(void *, ##__VA_ARGS__))(void (*)(void))glue5(For, _, Type,  \
                                                                _, Name),
#define ___TRAIT_ACT_BIND_REQUIRE_1(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(const void *, ##__VA_ARGS__))(void (*)(void))glue5(         \
      For, _, Type, _, Name),
#define ___TRAIT_ACT_BIND_DEFAULT_0(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(void *, ##__VA_ARGS__))(void (*)(void))glue5(For, _, Type,  \
                                                                _, Name),
#define ___TRAIT_ACT_BIND_DEFAULT_1(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(const void *, ##__VA_ARGS__))(void (*)(void))glue5(         \
      For, _, Type, _, Name),

// -----------------------------------------------------------------------------
// Actions: DFL (generate default wrappers in an impl block)
// -----------------------------------------------------------------------------

#define ___TRAIT_DFL_0_00(Type, Ret, Name)                                       \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(void *self) {   \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    return glue5(Default, _, Type, _, Name)(&_obj);                            \
  }

#define ___TRAIT_DFL_0_10(Type, Ret, Name)                                       \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _,                       \
                                        Name)(const void *self) {              \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    return glue5(Default, _, Type, _, Name)(&_obj);                            \
  }

#define ___TRAIT_DFL_1_00(Type, Ret, Name)                                       \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(void *self) {  \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    glue5(Default, _, Type, _, Name)(&_obj);                                   \
  }

#define ___TRAIT_DFL_1_10(Type, Ret, Name)                                       \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _,                      \
                                         Name)(const void *self) {             \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    glue5(Default, _, Type, _, Name)(&_obj);                                   \
  }

#define ___TRAIT_DFL_0_01(Type, Ret, Name, T1)                                   \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(void *self,     \
                                                               T1 a1) {        \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    return glue5(Default, _, Type, _, Name)(&_obj, a1);                        \
  }

#define ___TRAIT_DFL_0_11(Type, Ret, Name, T1)                                   \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _,                       \
                                        Name)(const void *self, T1 a1) {       \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    return glue5(Default, _, Type, _, Name)(&_obj, a1);                        \
  }

#define ___TRAIT_DFL_1_01(Type, Ret, Name, T1)                                   \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(void *self,    \
                                                                T1 a1) {       \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    glue5(Default, _, Type, _, Name)(&_obj, a1);                               \
  }

#define ___TRAIT_DFL_1_11(Type, Ret, Name, T1)                                   \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _,                      \
                                         Name)(const void *self, T1 a1) {      \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    glue5(Default, _, Type, _, Name)(&_obj, a1);                               \
  }

#define ___TRAIT_DFL_0_02(Type, Ret, Name, T1, T2)                               \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(void *self,     \
                                                               T1 a1, T2 a2) { \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                    \
  }

#define ___TRAIT_DFL_0_12(Type, Ret, Name, T1, T2)                               \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      const void *self, T1 a1, T2 a2) {                                        \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                    \
  }

#define ___TRAIT_DFL_1_02(Type, Ret, Name, T1, T2)                               \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _,                      \
                                         Name)(void *self, T1 a1, T2 a2) {     \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                           \
  }

#define ___TRAIT_DFL_1_12(Type, Ret, Name, T1, T2)                               \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      const void *self, T1 a1, T2 a2) {                                        \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                           \
  }

#define ___TRAIT_DFL_0_03(Type, Ret, Name, T1, T2, T3)                            \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      void *self, T1 a1, T2 a2, T3 a3) {                                       \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                \
  }

#define ___TRAIT_DFL_0_13(Type, Ret, Name, T1, T2, T3)                           \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      const void *self, T1 a1, T2 a2, T3 a3) {                                 \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                \
  }

#define ___TRAIT_DFL_1_03(Type, Ret, Name, T1, T2, T3)                           \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      void *self, T1 a1, T2 a2, T3 a3) {                                       \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                       \
  }

#define ___TRAIT_DFL_1_13(Type, Ret, Name, T1, T2, T3)                           \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      const void *self, T1 a1, T2 a2, T3 a3) {                                 \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                       \
  }

#define ___TRAIT_DFL_0_04(Type, Ret, Name, T1, T2, T3, T4)                       \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                                \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);            \
  }

#define ___TRAIT_DFL_0_14(Type, Ret, Name, T1, T2, T3, T4)                       \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      const void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                          \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);            \
  }

#define ___TRAIT_DFL_1_04(Type, Ret, Name, T1, T2, T3, T4)                       \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                                \
    glue(Dyn, Type) _obj = {.self = self, .vt = &___TRAIT_VTNAME(For, Type)};               \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);                   \
  }

#define ___TRAIT_DFL_1_14(Type, Ret, Name, T1, T2, T3, T4)                       \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      const void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                          \
    glue(Dyn, Type) _obj = {.self = (void *)self, .vt = &___TRAIT_VTNAME(For, Type)};       \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);                   \
  }

#define ___TRAIT_ACT_DFL_REQUIRE_0(Type, Ret, Name, ...) /* required: no wrap */
#define ___TRAIT_ACT_DFL_REQUIRE_1(Type, Ret, Name, ...) /* required: no wrap */

#define ___TRAIT_ACT_DFL_DEFAULT_0(Type, Ret, Name, ...)                         \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_DFL_, 0, _, 0, ___TRAIT_NARG(__VA_ARGS__)),                     \
    Type, Ret, Name, ##__VA_ARGS__)
#define ___TRAIT_ACT_DFL_DEFAULT_1(Type, Ret, Name, ...)                         \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_DFL_, 0, _, 1, ___TRAIT_NARG(__VA_ARGS__)),                     \
    Type, Ret, Name, ##__VA_ARGS__)

// -----------------------------------------------------------------------------
// Actions: SDFL (static default wrappers — no vtable, no DynTrait construction)
//
// Like DFL but the Dyn<Trait> wrapper only stores {.self = ptr} with no .vt.
// Used for static traits where defaults require no dynamic dispatch.
// The Default_Trait_method takes Dyn<Trait>* (a minimal {void *self} struct).
// Limitation: default bodies cannot call other trait methods on self.
// -----------------------------------------------------------------------------
#define ___TRAIT_SDFL_0_00(Type, Ret, Name)                                      \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(void *self) {   \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    return glue5(Default, _, Type, _, Name)(&_obj);                            \
  }

#define ___TRAIT_SDFL_0_10(Type, Ret, Name)                                      \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _,                       \
                                        Name)(const void *self) {              \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    return glue5(Default, _, Type, _, Name)(&_obj);                            \
  }

#define ___TRAIT_SDFL_1_00(Type, Ret, Name)                                      \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(void *self) {  \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    glue5(Default, _, Type, _, Name)(&_obj);                                   \
  }

#define ___TRAIT_SDFL_1_10(Type, Ret, Name)                                      \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _,                      \
                                         Name)(const void *self) {             \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    glue5(Default, _, Type, _, Name)(&_obj);                                   \
  }

#define ___TRAIT_SDFL_0_01(Type, Ret, Name, T1)                                  \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(void *self,     \
                                                                T1 a1) {        \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    return glue5(Default, _, Type, _, Name)(&_obj, a1);                        \
  }

#define ___TRAIT_SDFL_0_11(Type, Ret, Name, T1)                                  \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _,                       \
                                        Name)(const void *self, T1 a1) {       \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    return glue5(Default, _, Type, _, Name)(&_obj, a1);                        \
  }

#define ___TRAIT_SDFL_1_01(Type, Ret, Name, T1)                                  \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(void *self,    \
                                                                 T1 a1) {       \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    glue5(Default, _, Type, _, Name)(&_obj, a1);                               \
  }

#define ___TRAIT_SDFL_1_11(Type, Ret, Name, T1)                                  \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _,                      \
                                         Name)(const void *self, T1 a1) {      \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    glue5(Default, _, Type, _, Name)(&_obj, a1);                               \
  }

#define ___TRAIT_SDFL_0_02(Type, Ret, Name, T1, T2)                              \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(void *self,     \
                                                                T1 a1, T2 a2) { \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                    \
  }

#define ___TRAIT_SDFL_0_12(Type, Ret, Name, T1, T2)                              \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      const void *self, T1 a1, T2 a2) {                                        \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                    \
  }

#define ___TRAIT_SDFL_1_02(Type, Ret, Name, T1, T2)                              \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _,                      \
                                         Name)(void *self, T1 a1, T2 a2) {     \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                           \
  }

#define ___TRAIT_SDFL_1_12(Type, Ret, Name, T1, T2)                              \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      const void *self, T1 a1, T2 a2) {                                        \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2);                           \
  }

#define ___TRAIT_SDFL_0_03(Type, Ret, Name, T1, T2, T3)                          \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      void *self, T1 a1, T2 a2, T3 a3) {                                       \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                \
  }

#define ___TRAIT_SDFL_0_13(Type, Ret, Name, T1, T2, T3)                          \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      const void *self, T1 a1, T2 a2, T3 a3) {                                 \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                \
  }

#define ___TRAIT_SDFL_1_03(Type, Ret, Name, T1, T2, T3)                          \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      void *self, T1 a1, T2 a2, T3 a3) {                                       \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                       \
  }

#define ___TRAIT_SDFL_1_13(Type, Ret, Name, T1, T2, T3)                          \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      const void *self, T1 a1, T2 a2, T3 a3) {                                 \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3);                       \
  }

#define ___TRAIT_SDFL_0_04(Type, Ret, Name, T1, T2, T3, T4)                      \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                                \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);            \
  }

#define ___TRAIT_SDFL_0_14(Type, Ret, Name, T1, T2, T3, T4)                      \
  ___TRAIT_UNUSED static inline Ret glue5(For, _, Type, _, Name)(                \
      const void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                          \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    return glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);            \
  }

#define ___TRAIT_SDFL_1_04(Type, Ret, Name, T1, T2, T3, T4)                      \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                                \
    glue(Dyn, Type) _obj = {.self = self};                                      \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);                   \
  }

#define ___TRAIT_SDFL_1_14(Type, Ret, Name, T1, T2, T3, T4)                      \
  ___TRAIT_UNUSED static inline void glue5(For, _, Type, _, Name)(               \
      const void *self, T1 a1, T2 a2, T3 a3, T4 a4) {                          \
    glue(Dyn, Type) _obj = {.self = (void *)self};                              \
    glue5(Default, _, Type, _, Name)(&_obj, a1, a2, a3, a4);                   \
  }

#define ___TRAIT_ACT_SDFL_REQUIRE_0(Type, Ret, Name, ...) /* required: no wrap */
#define ___TRAIT_ACT_SDFL_REQUIRE_1(Type, Ret, Name, ...) /* required: no wrap */

#define ___TRAIT_ACT_SDFL_DEFAULT_0(Type, Ret, Name, ...)                        \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_SDFL_, 0, _, 0, ___TRAIT_NARG(__VA_ARGS__)),                    \
    Type, Ret, Name, ##__VA_ARGS__)
#define ___TRAIT_ACT_SDFL_DEFAULT_1(Type, Ret, Name, ...)                        \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_SDFL_, 0, _, 1, ___TRAIT_NARG(__VA_ARGS__)),                    \
    Type, Ret, Name, ##__VA_ARGS__))

// -----------------------------------------------------------------------------
// The `trait(...)` declaration expands the signature to emit:
//   FN:   vtable fields
//   FWD:  forwarding wrappers
//   STAG: selector tags
//   SSEL: selector struct fields
// -----------------------------------------------------------------------------
#define trait(NameSignature)                                                       \
  typedef struct {                                                                 \
    ___TRAIT_PASTE(NameSignature, Signature)((NameSignature, FN))                     \
  } NameSignature##_vtable;                                                        \
  typedef struct {                                                                 \
    void *self;                                                                    \
    const NameSignature##_vtable *vt;                                              \
  } Dyn##NameSignature;                                                            \
  ___TRAIT_PASTE(NameSignature, Signature)((NameSignature, FWD))                     \
  ___TRAIT_PASTE(NameSignature, Signature)((NameSignature, STAG))                    \
  typedef struct {                                                                 \
    ___TRAIT_PASTE(NameSignature, Signature)((NameSignature, SSEL))                  \
  } NameSignature##___sel_t;                                                       \
  ___TRAIT_UNUSED static ___TRAIT_CONSTEXPR NameSignature##___sel_t                             \
      NameSignature = {0}

// -----------------------------------------------------------------------------
// `extends(Base, Self)` declares a supertrait constraint: the derived trait
// requires the base trait to also be implemented.  This is purely
// declarative — no methods are copied into the derived namespace and no
// vtables are merged.  Each trait is implemented independently (Rust model).
//
// Enforcement: the SD loop's MLIST action replays the base trait's methods,
// so the SD entry for inherited methods calls For_BaseTrait_Method.  If the
// implementing type hasn't implemented the base trait, that symbol is
// undefined → linker error.
// -----------------------------------------------------------------------------
#define extends(Base, SelfSpec)                                                \
  glue(___TRAIT_EXTENDS_, ___TRAIT_GET_ACTION(SelfSpec))(Base, SelfSpec)
#define ___TRAIT_EXTENDS_FN(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_FWD(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_STAG(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_SSEL(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_DFL(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_SDFL(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_BIND(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_FWDDECL(Base, SelfSpec) /* no-op */
#define ___TRAIT_EXTENDS_ENFORCE(Base, SelfSpec)                                 \
  ___TRAIT_UNUSED static void *const                                              \
      glue5(___trait_enforce, _, For, _, Base) =                                  \
          (void *)&glue4(For, _, Base, _vtable);

// -----------------------------------------------------------------------------
// `def(...)` defines the implementation function body.
// `redef(...)` defines an overriding implementation for a default method.
// The self type is chosen automatically from trait metadata.
// If `For == Default`, the body is for the trait's default implementation and
// uses `Impl` as the receiver type; otherwise it uses `For`.
// -----------------------------------------------------------------------------
#define ___TRAIT_IMPL_SELF_BASE_0 For
#define ___TRAIT_IMPL_SELF_BASE_1 ___TRAIT_DYN(Impl)
#define ___TRAIT_IMPL_SELF_BASE_SEL(n) glue(___TRAIT_IMPL_SELF_BASE_, n)
#define ___TRAIT_IMPL_SELF_BASE ___TRAIT_IMPL_SELF_BASE_SEL(___TRAIT_IS_DEFAULT(For))

// -----------------------------------------------------------------------------
// `def(...)` defines the implementation function body (mutable self).
// `constdef(...)` defines the implementation function body (const self).
// For `For == Default`, self is `DynImpl *` / `const DynImpl *`.
// For concrete types, self is `For *` / `const For *`.
// The user chooses def/constdef based on the method's constness in the
// trait declaration (`immutable(Self)` → constdef).
//
// To override a default method, use def/constdef (same as for required
// methods) and also define:
//   #define Override_<Type>_<Trait>_<Method> 1
// before the #include "trait.h" that processes the impl block, so that
// defaults() knows to skip the DFL wrapper for that method.
// -----------------------------------------------------------------------------
#define def(Name, ...)                                                         \
  glue5(For, _, Impl, _,                                                       \
        Name)(___TRAIT_IMPL_SELF_BASE * self, ##__VA_ARGS__)

#define constdef(Name, ...)                                                    \
  glue5(For, _, Impl, _,                                                       \
        Name)(const ___TRAIT_IMPL_SELF_BASE * self, ##__VA_ARGS__)

// -----------------------------------------------------------------------------
// `defaults()` emits wrappers for default methods when implementing a trait.
// `static_defaults()` emits SDFL wrappers for static traits (no vtable).
// `impl()` emits the vtable object plus trait conversion helpers.
// -----------------------------------------------------------------------------
#define defaults()                                                             \
  ___TRAIT_UNUSED static const ___TRAIT_VTTYPE(Impl) ___TRAIT_VTNAME(For, Impl);   \
  ___TRAIT_PASTE(Impl, Signature)((Impl, DFL))

#define static_defaults()                                                      \
  ___TRAIT_PASTE(Impl, Signature)((Impl, SDFL))

#define impl()                                                                 \
  ___TRAIT_UNUSED static const ___TRAIT_VTTYPE(Impl)                          \
      ___TRAIT_VTNAME(For, Impl) = {___TRAIT_PASTE(Impl, Signature)((Impl, BIND))};    \
  ___TRAIT_UNUSED static inline glue(Dyn, Impl)                                 \
      glue3(For, _as_, Impl)(For * obj) {                                      \
    return (glue(Dyn, Impl)){.self = obj, .vt = &___TRAIT_VTNAME(For, Impl)};    \
  }                                                                            \
  ___TRAIT_UNUSED static inline For *glue3(For, _from_, Impl)(                   \
      glue(Dyn, Impl) obj) {                                                   \
    return (For *)obj.self;                                                    \
  }

#define impl_vt() impl()

// -----------------------------------------------------------------------------
// Call-site ergonomics
// -----------------------------------------------------------------------------
#define to_trait(Type, Trait, ptr) Type##_as_##Trait(ptr)
#define from_trait(Type, Trait, obj) Type##_from_##Trait(obj)

// -----------------------------------------------------------------------------
/* Literal construction */
#define new_trait(Type, Trait, ...) Type##_as_##Trait(&(Type)__VA_ARGS__)

// ── ENFORCE action: impl-site enforcement of extends ─────────────────────────
// For each extends(Base), emits a static reference to For##_Base##_vtable.
// If the type hasn't implemented the base trait, the symbol is undefined
// → linker error at impl site.
// require/default methods are no-ops for ENFORCE.
#define ___TRAIT_ACT_ENFORCE_REQUIRE_0(Type, Ret, Name, ...) /* no-op */
#define ___TRAIT_ACT_ENFORCE_REQUIRE_1(Type, Ret, Name, ...) /* no-op */
#define ___TRAIT_ACT_ENFORCE_DEFAULT_0(Type, Ret, Name, ...) /* no-op */
#define ___TRAIT_ACT_ENFORCE_DEFAULT_1(Type, Ret, Name, ...) /* no-op */

// ── FWDDECL action: extern declarations for forward-declare mode ─────────────
// When #define Forward is active, emits extern declarations for each
// impl function so that SD entries (which call these functions) can be emitted
// before the def() bodies.
// _0 suffix = mutable (For *), _1 suffix = immutable/const (const For *).
#define ___TRAIT_ACT_FWDDECL_REQUIRE_0(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      For *, ##__VA_ARGS__);
#define ___TRAIT_ACT_FWDDECL_REQUIRE_1(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      const For *, ##__VA_ARGS__);
#define ___TRAIT_ACT_FWDDECL_DEFAULT_0(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      For *, ##__VA_ARGS__);
#define ___TRAIT_ACT_FWDDECL_DEFAULT_1(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      const For *, ##__VA_ARGS__);

// =============================================================================
// SD (selector-based dispatch) infrastructure
//
// Enables: call(Animal.get_snacks, &cat)
//
// Architecture: flat (type × method) counter where each slot stores both the
// concrete type and the selector type.  call() walks this counter checking both
// types simultaneously with &&.
//
// The SD counter is populated during impl registration via self-include loops:
//   1. SD loop: emits entries for concrete types (static dispatch)
//   2. DynSD loop: emits entries for DynTraitname (dynamic dispatch via vtable)
// =============================================================================

// -----------------------------------------------------------------------------
// MSEL: position-selector macros
//
// ___TRAIT_MSEL_K(dummy, a0, a1, ..., aK, ...) → aK
// The `dummy` argument absorbs the leading comma from MLIST expansion.
// Supports up to 8 methods per trait.
// -----------------------------------------------------------------------------
#define ___TRAIT_MSEL_0(d, a, ...) a
#define ___TRAIT_MSEL_1(d, a, b, ...) b
#define ___TRAIT_MSEL_2(d, a, b, c, ...) c
#define ___TRAIT_MSEL_3(d, a, b, c, e, ...) e
#define ___TRAIT_MSEL_4(d, a, b, c, e, f, ...) f
#define ___TRAIT_MSEL_5(d, a, b, c, e, f, g, ...) g
#define ___TRAIT_MSEL_6(d, a, b, c, e, f, g, h, ...) h
#define ___TRAIT_MSEL_7(d, a, b, c, e, f, g, h, i, ...) i

// Relay macro: forces expansion of args before argument splitting.
// This is critical because MLIST expansion produces commas that must be
// visible as argument separators when MSEL_K identifies its arguments.
#define ___TRAIT_SD_APPLY(M, ...) M(__VA_ARGS__)

// Select the Kth method tuple from a trait's MLIST expansion.
// Returns a parenthesized tuple: (NameSignature, ConstFlag, Ret, Name, ExtraArgs...)
// Sentinel tuples (_STOP) are appended to safely handle out-of-range K.
#define ___TRAIT_SD_SELECT(K, TraitImpl)                                         \
  ___TRAIT_SD_APPLY(glue(___TRAIT_MSEL_, K),                                       \
      0 ___TRAIT_PASTE(TraitImpl, Signature)((TraitImpl, MLIST))                   \
      , (_STOP) , (_STOP) , (_STOP) , (_STOP)                                  \
      , (_STOP) , (_STOP) , (_STOP) , (_STOP))

// -----------------------------------------------------------------------------
// Sentinel detection for the self-include loop.
// ___TRAIT_SD_IS_STOP(K, TraitImpl) → 1 if method K is past the last method.
// Works in #if context: fully expands to an integer constant 0 or 1.
// -----------------------------------------------------------------------------
#define ___TRAIT_SD_TUPLE_FIRST_I(a, ...) a
#define ___TRAIT_SD_TUPLE_FIRST(t) ___TRAIT_SD_TUPLE_FIRST_I t
#define ___TRAIT_SD_STOP_CHECK__STOP ___TRAIT_PROBE()
#define ___TRAIT_SD_IS_STOP(K, TraitImpl)                                        \
  ___TRAIT_CHECK(glue(___TRAIT_SD_STOP_CHECK_,                                     \
      ___TRAIT_SD_TUPLE_FIRST(___TRAIT_SD_SELECT(K, TraitImpl))))

// -----------------------------------------------------------------------------
// SD registration emission
//
// ___TRAIT_SD_EMIT(tuple) unpacks a method tuple and emits:
//   1. typedef For → ___trait_sd_D6D5D4D3D2D1_ty  (concrete type)
//   2. typedef selector → ___trait_sd_D6D5D4D3D2D1_sty  (selector type)
//   3. static inline wrapper function ___trait_sd_fn_D6D5D4D3D2D1
//
// Uses For (concrete type) and Impl (trait name) which are still defined
// during the SD self-include loop.
// -----------------------------------------------------------------------------
#define ___TRAIT_SD_EMIT(tuple) ___TRAIT_SD_EMIT_I tuple
#define ___TRAIT_SD_EMIT_I(NameSignature, ConstFlag, Ret, Name, ...)                 \
  typedef For glue8(___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _ty);   \
  typedef glue5(___sel_, Impl, _, Name, _t) glue8(                               \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _sty);               \
  typedef glue5(___sel_, NameSignature, _, Name, _t) glue8(                           \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _asty);             \
  typedef void (*glue8(___trait_sd_pair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, Impl, _, Name, _t), For); \
  typedef void (*glue8(___trait_sd_apair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, NameSignature, _, Name, _t), For); \
  glue5(___TRAIT_SDREG_, 0, _, ConstFlag,                                            \
        ___TRAIT_NARG(__VA_ARGS__))(NameSignature, Ret, Name, ##__VA_ARGS__)

// -----------------------------------------------------------------------------
// SDREG: SD wrapper function emitters
//
// SDREG wrapper emitter:
//   - Function name uses SD counter: ___trait_sd_fn_D6D5D4D3D2D1
//   - Body calls For_Impl_Method (using current For and Impl macros)
//   - Parameters: (Ret, Name, ExtraArgs...) — no Type parameter needed
//     since For and Impl are available as macros
// -----------------------------------------------------------------------------
#define ___TRAIT_SDREG_FN                                                        \
  glue7(___trait_sd_fn_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1)
#define ___TRAIT_SDREG_IMPL(NameSignature, Name) glue5(For, _, NameSignature, _, Name)

// ── non-void return ─────────────────────────────────────────────────────────
#define ___TRAIT_SDREG_0_00(NameSignature, Ret, Name)                                \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(For * self) {                \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self);                           \
  }
#define ___TRAIT_SDREG_0_10(NameSignature, Ret, Name)                                \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(const For *self) {           \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self);                           \
  }
#define ___TRAIT_SDREG_0_01(NameSignature, Ret, Name, T1)                            \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(For * self, T1 a1) {         \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1);                       \
  }
#define ___TRAIT_SDREG_0_11(NameSignature, Ret, Name, T1)                            \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(const For *self, T1 a1) {    \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1);                       \
  }
#define ___TRAIT_SDREG_0_02(NameSignature, Ret, Name, T1, T2)                        \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(For * self, T1 a1, T2 a2) {  \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2);                   \
  }
#define ___TRAIT_SDREG_0_12(NameSignature, Ret, Name, T1, T2)                        \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(const For *self, T1 a1,      \
                                                    T2 a2) {                    \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2);                   \
  }
#define ___TRAIT_SDREG_0_03(NameSignature, Ret, Name, T1, T2, T3)                    \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(For * self, T1 a1, T2 a2,    \
                                                    T3 a3) {                    \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3);               \
  }
#define ___TRAIT_SDREG_0_13(NameSignature, Ret, Name, T1, T2, T3)                    \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(const For *self, T1 a1,      \
                                                    T2 a2, T3 a3) {            \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3);               \
  }
#define ___TRAIT_SDREG_0_04(NameSignature, Ret, Name, T1, T2, T3, T4)                \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(For * self, T1 a1, T2 a2,    \
                                                    T3 a3, T4 a4) {            \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3, a4);           \
  }
#define ___TRAIT_SDREG_0_14(NameSignature, Ret, Name, T1, T2, T3, T4)                \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(const For *self, T1 a1,      \
                                                    T2 a2, T3 a3, T4 a4) {     \
    return ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3, a4);           \
  }

// ── void return ─────────────────────────────────────────────────────────────
#define ___TRAIT_SDREG_1_00(NameSignature, Ret, Name)                                \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(For * self) {               \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self);                                  \
  }
#define ___TRAIT_SDREG_1_10(NameSignature, Ret, Name)                                \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(const For *self) {          \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self);                                  \
  }
#define ___TRAIT_SDREG_1_01(NameSignature, Ret, Name, T1)                            \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(For * self, T1 a1) {        \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1);                              \
  }
#define ___TRAIT_SDREG_1_11(NameSignature, Ret, Name, T1)                            \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(const For *self, T1 a1) {   \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1);                              \
  }
#define ___TRAIT_SDREG_1_02(NameSignature, Ret, Name, T1, T2)                        \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(For * self, T1 a1, T2 a2) { \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2);                          \
  }
#define ___TRAIT_SDREG_1_12(NameSignature, Ret, Name, T1, T2)                        \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(const For *self, T1 a1,     \
                                                     T2 a2) {                   \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2);                          \
  }
#define ___TRAIT_SDREG_1_03(NameSignature, Ret, Name, T1, T2, T3)                    \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(For * self, T1 a1, T2 a2,   \
                                                     T3 a3) {                   \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3);                      \
  }
#define ___TRAIT_SDREG_1_13(NameSignature, Ret, Name, T1, T2, T3)                    \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(const For *self, T1 a1,     \
                                                     T2 a2, T3 a3) {           \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3);                      \
  }
#define ___TRAIT_SDREG_1_04(NameSignature, Ret, Name, T1, T2, T3, T4)                \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(For * self, T1 a1, T2 a2,   \
                                                     T3 a3, T4 a4) {           \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3, a4);                  \
  }
#define ___TRAIT_SDREG_1_14(NameSignature, Ret, Name, T1, T2, T3, T4)                \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(const For *self, T1 a1,     \
                                                     T2 a2, T3 a3, T4 a4) {    \
    ___TRAIT_SDREG_IMPL(NameSignature, Name)(self, a1, a2, a3, a4);                  \
  }

// =============================================================================
// DynSD (dynamic dispatch via selector) infrastructure
//
// When call(Animal.get_snacks, &dyn_obj) is used with a DynTraitname pointer,
// the SD chain matches DynTraitname as the concrete type and dispatches through
// the vtable.  DYNSDREG wrapper functions are emitted during a second
// self-include loop after the normal SD loop in impl registration.
// =============================================================================

// -----------------------------------------------------------------------------
// DYNSD registration emission
//
// Like ___TRAIT_SD_EMIT but uses DynImpl as the concrete type and generates
// vtable-dispatching wrapper functions instead of direct-call wrappers.
// -----------------------------------------------------------------------------
#define ___TRAIT_DYNSD_EMIT(tuple) ___TRAIT_DYNSD_EMIT_I tuple
#define ___TRAIT_DYNSD_EMIT_I(NameSignature, ConstFlag, Ret, Name, ...)              \
  typedef glue(Dyn, Impl) glue8(___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5,       \
                                  ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _ty);  \
  typedef glue5(___sel_, Impl, _, Name, _t) glue8(                               \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _sty);               \
  typedef glue5(___sel_, NameSignature, _, Name, _t) glue8(                           \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _asty);             \
  typedef void (*glue8(___trait_sd_pair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, Impl, _, Name, _t), glue(Dyn, Impl)); \
  typedef void (*glue8(___trait_sd_apair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, NameSignature, _, Name, _t), glue(Dyn, Impl)); \
  glue5(___TRAIT_DYNSDREG_, 0, _, ConstFlag,                                         \
        ___TRAIT_NARG(__VA_ARGS__))(Ret, Name, ##__VA_ARGS__)

// -----------------------------------------------------------------------------
// DYNSDREG: DynTraitname wrapper function emitters
//
// Like SDREG but:
//   - Parameter is DynImpl* (or const DynImpl*) instead of For*
//   - Body calls self->vt->Name(self->self, ...) instead of For_Impl_Name()
// -----------------------------------------------------------------------------

// ── non-void return ─────────────────────────────────────────────────────────
#define ___TRAIT_DYNSDREG_0_00(Ret, Name)                                        \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      glue(Dyn, Impl) *self) {                                                 \
    return self->vt->Name(self->self);                                         \
  }
#define ___TRAIT_DYNSDREG_0_10(Ret, Name)                                        \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      const glue(Dyn, Impl) *self) {                                           \
    return self->vt->Name(self->self);                                         \
  }
#define ___TRAIT_DYNSDREG_0_01(Ret, Name, T1)                                    \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      glue(Dyn, Impl) *self, T1 a1) {                                          \
    return self->vt->Name(self->self, a1);                                     \
  }
#define ___TRAIT_DYNSDREG_0_11(Ret, Name, T1)                                    \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      const glue(Dyn, Impl) *self, T1 a1) {                                    \
    return self->vt->Name(self->self, a1);                                     \
  }
#define ___TRAIT_DYNSDREG_0_02(Ret, Name, T1, T2)                                \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      glue(Dyn, Impl) *self, T1 a1, T2 a2) {                                   \
    return self->vt->Name(self->self, a1, a2);                                 \
  }
#define ___TRAIT_DYNSDREG_0_12(Ret, Name, T1, T2)                                \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      const glue(Dyn, Impl) *self, T1 a1, T2 a2) {                             \
    return self->vt->Name(self->self, a1, a2);                                 \
  }
#define ___TRAIT_DYNSDREG_0_03(Ret, Name, T1, T2, T3)                            \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3) {                            \
    return self->vt->Name(self->self, a1, a2, a3);                             \
  }
#define ___TRAIT_DYNSDREG_0_13(Ret, Name, T1, T2, T3)                            \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      const glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3) {                      \
    return self->vt->Name(self->self, a1, a2, a3);                             \
  }
#define ___TRAIT_DYNSDREG_0_04(Ret, Name, T1, T2, T3, T4)                        \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3, T4 a4) {                     \
    return self->vt->Name(self->self, a1, a2, a3, a4);                         \
  }
#define ___TRAIT_DYNSDREG_0_14(Ret, Name, T1, T2, T3, T4)                        \
  ___TRAIT_UNUSED static inline Ret ___TRAIT_SDREG_FN(                             \
      const glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3, T4 a4) {               \
    return self->vt->Name(self->self, a1, a2, a3, a4);                         \
  }

// ── void return ─────────────────────────────────────────────────────────────
#define ___TRAIT_DYNSDREG_1_00(Ret, Name)                                        \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      glue(Dyn, Impl) *self) {                                                  \
    self->vt->Name(self->self);                                                \
  }
#define ___TRAIT_DYNSDREG_1_10(Ret, Name)                                        \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      const glue(Dyn, Impl) *self) {                                            \
    self->vt->Name(self->self);                                                \
  }
#define ___TRAIT_DYNSDREG_1_01(Ret, Name, T1)                                    \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      glue(Dyn, Impl) *self, T1 a1) {                                           \
    self->vt->Name(self->self, a1);                                            \
  }
#define ___TRAIT_DYNSDREG_1_11(Ret, Name, T1)                                    \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      const glue(Dyn, Impl) *self, T1 a1) {                                     \
    self->vt->Name(self->self, a1);                                            \
  }
#define ___TRAIT_DYNSDREG_1_02(Ret, Name, T1, T2)                                \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      glue(Dyn, Impl) *self, T1 a1, T2 a2) {                                    \
    self->vt->Name(self->self, a1, a2);                                        \
  }
#define ___TRAIT_DYNSDREG_1_12(Ret, Name, T1, T2)                                \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      const glue(Dyn, Impl) *self, T1 a1, T2 a2) {                              \
    self->vt->Name(self->self, a1, a2);                                        \
  }
#define ___TRAIT_DYNSDREG_1_03(Ret, Name, T1, T2, T3)                            \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3) {                             \
    self->vt->Name(self->self, a1, a2, a3);                                    \
  }
#define ___TRAIT_DYNSDREG_1_13(Ret, Name, T1, T2, T3)                            \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      const glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3) {                       \
    self->vt->Name(self->self, a1, a2, a3);                                    \
  }
#define ___TRAIT_DYNSDREG_1_04(Ret, Name, T1, T2, T3, T4)                        \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3, T4 a4) {                      \
    self->vt->Name(self->self, a1, a2, a3, a4);                                \
  }
#define ___TRAIT_DYNSDREG_1_14(Ret, Name, T1, T2, T3, T4)                        \
  ___TRAIT_UNUSED static inline void ___TRAIT_SDREG_FN(                            \
      const glue(Dyn, Impl) *self, T1 a1, T2 a2, T3 a3, T4 a4) {                \
    self->vt->Name(self->self, a1, a2, a3, a4);                                \
  }

// =============================================================================
// SD counter: 6-digit octal, max 262144 selector dispatch slots.
// Each impl × method consumes one slot.
// Persistent across re-include passes (like the type counter).
// =============================================================================
#define ___TRAIT_SD_C1 0
#define ___TRAIT_SD_C2 0
#define ___TRAIT_SD_C3 0
#define ___TRAIT_SD_C4 0
#define ___TRAIT_SD_C5 0
#define ___TRAIT_SD_C6 0
#define ___TRAIT_SD_C7 0

// =============================================================================
// SD dispatch: _Generic-based (standard C11)
//
// Uses the "extendible _Generic" pattern: recursive macros generate _Generic
// slots from 0 to the current counter value.  The fptr trick dispatches on
// both selector type and concrete type simultaneously.
//
// The controlling expression:
//   (void (*)(___TRAIT_TYPEOF(sel), ___TRAIT_TYPEOF(*(obj))))0
// has type void (*)(SelectorType, ConcreteType), matching the pair typedefs
// emitted during SD registration.
// =============================================================================

// Single slot in the _Generic: primary + alias selector pair types
// clang-format off
#define ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,d1) \
  glue8(___trait_sd_pair_, d6,d5,d4,d3,d2,d1,_p): glue7(___trait_sd_fn_, d6,d5,d4,d3,d2,d1),

// ── R1: innermost level (digit d1, 0–7 per group) ──────────────────────────
#define ___TRAIT_SD_R1_0(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_1(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,0)
#define ___TRAIT_SD_R1_2(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,1) \
  ___TRAIT_SD_R1_1(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_3(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,2) \
  ___TRAIT_SD_R1_2(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_4(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,3) \
  ___TRAIT_SD_R1_3(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_5(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,4) \
  ___TRAIT_SD_R1_4(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_6(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,5) \
  ___TRAIT_SD_R1_5(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_7(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,6) \
  ___TRAIT_SD_R1_6(d6,d5,d4,d3,d2)
#define ___TRAIT_SD_R1_8(d6,d5,d4,d3,d2) \
  ___TRAIT_SD_SLOT(d6,d5,d4,d3,d2,7) \
  ___TRAIT_SD_R1_7(d6,d5,d4,d3,d2)

// ── R2: digit d2 (0–7, each emits a full R1_8 group) ───────────────────────
#define ___TRAIT_SD_R2_0(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_1(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,0)
#define ___TRAIT_SD_R2_2(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,1) \
  ___TRAIT_SD_R2_1(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_3(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,2) \
  ___TRAIT_SD_R2_2(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_4(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,3) \
  ___TRAIT_SD_R2_3(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_5(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,4) \
  ___TRAIT_SD_R2_4(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_6(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,5) \
  ___TRAIT_SD_R2_5(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_7(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,6) \
  ___TRAIT_SD_R2_6(d6,d5,d4,d3)
#define ___TRAIT_SD_R2_8(d6,d5,d4,d3) \
  ___TRAIT_SD_R1_8(d6,d5,d4,d3,7) \
  ___TRAIT_SD_R2_7(d6,d5,d4,d3)

// ── R3: digit d3 (0–7, each emits a full R2_8 group) ───────────────────────
#define ___TRAIT_SD_R3_0(d6,d5,d4)
#define ___TRAIT_SD_R3_1(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,0)
#define ___TRAIT_SD_R3_2(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,1) \
  ___TRAIT_SD_R3_1(d6,d5,d4)
#define ___TRAIT_SD_R3_3(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,2) \
  ___TRAIT_SD_R3_2(d6,d5,d4)
#define ___TRAIT_SD_R3_4(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,3) \
  ___TRAIT_SD_R3_3(d6,d5,d4)
#define ___TRAIT_SD_R3_5(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,4) \
  ___TRAIT_SD_R3_4(d6,d5,d4)
#define ___TRAIT_SD_R3_6(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,5) \
  ___TRAIT_SD_R3_5(d6,d5,d4)
#define ___TRAIT_SD_R3_7(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,6) \
  ___TRAIT_SD_R3_6(d6,d5,d4)
#define ___TRAIT_SD_R3_8(d6,d5,d4) \
  ___TRAIT_SD_R2_8(d6,d5,d4,7) \
  ___TRAIT_SD_R3_7(d6,d5,d4)

// ── R4: digit d4 (0–7, each emits a full R3_8 group) ───────────────────────
#define ___TRAIT_SD_R4_0(d6,d5)
#define ___TRAIT_SD_R4_1(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,0)
#define ___TRAIT_SD_R4_2(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,1) \
  ___TRAIT_SD_R4_1(d6,d5)
#define ___TRAIT_SD_R4_3(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,2) \
  ___TRAIT_SD_R4_2(d6,d5)
#define ___TRAIT_SD_R4_4(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,3) \
  ___TRAIT_SD_R4_3(d6,d5)
#define ___TRAIT_SD_R4_5(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,4) \
  ___TRAIT_SD_R4_4(d6,d5)
#define ___TRAIT_SD_R4_6(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,5) \
  ___TRAIT_SD_R4_5(d6,d5)
#define ___TRAIT_SD_R4_7(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,6) \
  ___TRAIT_SD_R4_6(d6,d5)
#define ___TRAIT_SD_R4_8(d6,d5) \
  ___TRAIT_SD_R3_8(d6,d5,7) \
  ___TRAIT_SD_R4_7(d6,d5)

// ── R5: digit d5 (0–7, each emits a full R4_8 group) ───────────────────────
#define ___TRAIT_SD_R5_0(d6)
#define ___TRAIT_SD_R5_1(d6) \
  ___TRAIT_SD_R4_8(d6,0)
#define ___TRAIT_SD_R5_2(d6) \
  ___TRAIT_SD_R4_8(d6,1) \
  ___TRAIT_SD_R5_1(d6)
#define ___TRAIT_SD_R5_3(d6) \
  ___TRAIT_SD_R4_8(d6,2) \
  ___TRAIT_SD_R5_2(d6)
#define ___TRAIT_SD_R5_4(d6) \
  ___TRAIT_SD_R4_8(d6,3) \
  ___TRAIT_SD_R5_3(d6)
#define ___TRAIT_SD_R5_5(d6) \
  ___TRAIT_SD_R4_8(d6,4) \
  ___TRAIT_SD_R5_4(d6)
#define ___TRAIT_SD_R5_6(d6) \
  ___TRAIT_SD_R4_8(d6,5) \
  ___TRAIT_SD_R5_5(d6)
#define ___TRAIT_SD_R5_7(d6) \
  ___TRAIT_SD_R4_8(d6,6) \
  ___TRAIT_SD_R5_6(d6)
#define ___TRAIT_SD_R5_8(d6) \
  ___TRAIT_SD_R4_8(d6,7) \
  ___TRAIT_SD_R5_7(d6)

// ── R6: digit d6 (most significant, 0–7) ────────────────────────────────────
#define ___TRAIT_SD_R6_0
#define ___TRAIT_SD_R6_1 \
  ___TRAIT_SD_R5_8(0)
#define ___TRAIT_SD_R6_2 \
  ___TRAIT_SD_R5_8(1) \
  ___TRAIT_SD_R6_1
#define ___TRAIT_SD_R6_3 \
  ___TRAIT_SD_R5_8(2) \
  ___TRAIT_SD_R6_2
#define ___TRAIT_SD_R6_4 \
  ___TRAIT_SD_R5_8(3) \
  ___TRAIT_SD_R6_3
#define ___TRAIT_SD_R6_5 \
  ___TRAIT_SD_R5_8(4) \
  ___TRAIT_SD_R6_4
#define ___TRAIT_SD_R6_6 \
  ___TRAIT_SD_R5_8(5) \
  ___TRAIT_SD_R6_5
#define ___TRAIT_SD_R6_7 \
  ___TRAIT_SD_R5_8(6) \
  ___TRAIT_SD_R6_6
#define ___TRAIT_SD_R6_8 \
  ___TRAIT_SD_R5_8(7) \
  ___TRAIT_SD_R6_7

// ── Assemble all slots ──────────────────────────────────────────────────────
#define ___TRAIT_SD_SLOTS                                                          \
  glue(___TRAIT_SD_R1_, ___TRAIT_SD_C1)(___TRAIT_SD_C6, ___TRAIT_SD_C5,          \
                                        ___TRAIT_SD_C4, ___TRAIT_SD_C3,          \
                                        ___TRAIT_SD_C2)                           \
  glue(___TRAIT_SD_R2_, ___TRAIT_SD_C2)(___TRAIT_SD_C6, ___TRAIT_SD_C5,          \
                                        ___TRAIT_SD_C4, ___TRAIT_SD_C3)          \
  glue(___TRAIT_SD_R3_, ___TRAIT_SD_C3)(___TRAIT_SD_C6, ___TRAIT_SD_C5,          \
                                        ___TRAIT_SD_C4)                           \
  glue(___TRAIT_SD_R4_, ___TRAIT_SD_C4)(___TRAIT_SD_C6, ___TRAIT_SD_C5)          \
  glue(___TRAIT_SD_R5_, ___TRAIT_SD_C5)(___TRAIT_SD_C6)                          \
  glue(___TRAIT_SD_R6_, ___TRAIT_SD_C6)

// ── call(sel, obj, ...) ─────────────────────────────────────────────────────
//
// Unified dispatch via _Generic.  The controlling expression is a null
// function-pointer whose type encodes both the selector and object types.
// Each registered SD entry provides a matching pair type.
// If no slot matches, the default arm yields a non-callable struct variable
// with a descriptive name — the compiler error reads:
//   "called object type 'struct ERROR_trait_not_implemented_for_this_type'
//    is not a function or function pointer"
// clang-format off
struct ERROR_trait_not_implemented_for_this_type;
extern struct ERROR_trait_not_implemented_for_this_type ERROR_trait_not_implemented_for_this_type;
#define call(sel, obj, ...)                                                       \
  _Generic(                                                                       \
      (void (*)(___TRAIT_TYPEOF(sel), ___TRAIT_TYPEOF(*(obj))))0,                 \
      ___TRAIT_SD_SLOTS                                                           \
      default: ERROR_trait_not_implemented_for_this_type                          \
  )(obj, ##__VA_ARGS__)

// =============================================================================
// C23 overrides
//
// In C23 mode, the GCC extension `, ##__VA_ARGS__` is a hard error.  Each
// affected macro is redefined here using the standard `__VA_OPT__` equivalent.
// The original C11 definitions above use `, ##__VA_ARGS__`.
// =============================================================================
#if ___TRAIT_C23

// ── NARG ──────────────────────────────────────────────────────────────────────
#undef  ___TRAIT_NARG
#define ___TRAIT_NARG(...) ___TRAIT_NARG_IMPL(dummy __VA_OPT__(,) __VA_ARGS__, 4, 3, 2, 1, 0)

// ── Dispatch ──────────────────────────────────────────────────────────────────
#undef  trait_default
#define trait_default(SelfSpec, Ret, Name, ...)                                \
  glue4(___TRAIT_ACT_, ___TRAIT_SPEC_ACTION(SelfSpec), _DEFAULT_,                  \
        ___TRAIT_IS_IMMUTABLE(SelfSpec))(___TRAIT_SPEC_TYPE(SelfSpec), Ret, Name  \
                                        __VA_OPT__(,) __VA_ARGS__)

#undef  trait_require
#define trait_require(SelfSpec, Ret, Name, ...)                                \
  glue4(___TRAIT_ACT_, ___TRAIT_SPEC_ACTION(SelfSpec), _REQUIRE_,                  \
        ___TRAIT_IS_IMMUTABLE(SelfSpec))(___TRAIT_SPEC_TYPE(SelfSpec), Ret, Name  \
                                        __VA_OPT__(,) __VA_ARGS__)

#undef  default
#define default(SelfSpec, Ret, Name, ...)                                      \
  trait_default(SelfSpec, Ret, Name __VA_OPT__(,) __VA_ARGS__)
#undef  require
#define require(SelfSpec, Ret, Name, ...)                                      \
  trait_require(SelfSpec, Ret, Name __VA_OPT__(,) __VA_ARGS__)

// ── FN actions (vtable fields) ────────────────────────────────────────────────
#undef  ___TRAIT_ACT_FN_REQUIRE_0
#define ___TRAIT_ACT_FN_REQUIRE_0(Type, Ret, Name, ...)                          \
  Ret (*Name)(void * __VA_OPT__(,) __VA_ARGS__);
#undef  ___TRAIT_ACT_FN_REQUIRE_1
#define ___TRAIT_ACT_FN_REQUIRE_1(Type, Ret, Name, ...)                          \
  Ret (*Name)(const void * __VA_OPT__(,) __VA_ARGS__);
#undef  ___TRAIT_ACT_FN_DEFAULT_0
#define ___TRAIT_ACT_FN_DEFAULT_0(Type, Ret, Name, ...)                          \
  Ret (*Name)(void * __VA_OPT__(,) __VA_ARGS__);
#undef  ___TRAIT_ACT_FN_DEFAULT_1
#define ___TRAIT_ACT_FN_DEFAULT_1(Type, Ret, Name, ...)                          \
  Ret (*Name)(const void * __VA_OPT__(,) __VA_ARGS__);

// ── MLIST actions ─────────────────────────────────────────────────────────────
#undef  ___TRAIT_ACT_MLIST_REQUIRE_0
#define ___TRAIT_ACT_MLIST_REQUIRE_0(Type, Ret, Name, ...)                       \
  , (Type, 0, Ret, Name __VA_OPT__(,) __VA_ARGS__)
#undef  ___TRAIT_ACT_MLIST_REQUIRE_1
#define ___TRAIT_ACT_MLIST_REQUIRE_1(Type, Ret, Name, ...)                       \
  , (Type, 1, Ret, Name __VA_OPT__(,) __VA_ARGS__)
#undef  ___TRAIT_ACT_MLIST_DEFAULT_0
#define ___TRAIT_ACT_MLIST_DEFAULT_0(Type, Ret, Name, ...)                       \
  , (Type, 0, Ret, Name __VA_OPT__(,) __VA_ARGS__)
#undef  ___TRAIT_ACT_MLIST_DEFAULT_1
#define ___TRAIT_ACT_MLIST_DEFAULT_1(Type, Ret, Name, ...)                       \
  , (Type, 1, Ret, Name __VA_OPT__(,) __VA_ARGS__)


// ── BIND actions (vtable initializer) ─────────────────────────────────────────
#undef  ___TRAIT_ACT_BIND_REQUIRE_0
#define ___TRAIT_ACT_BIND_REQUIRE_0(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(void * __VA_OPT__(,) __VA_ARGS__))(void (*)(void))glue5(For, _, Type, \
                                                                _, Name),
#undef  ___TRAIT_ACT_BIND_REQUIRE_1
#define ___TRAIT_ACT_BIND_REQUIRE_1(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(const void * __VA_OPT__(,) __VA_ARGS__))(void (*)(void))glue5( \
      For, _, Type, _, Name),
#undef  ___TRAIT_ACT_BIND_DEFAULT_0
#define ___TRAIT_ACT_BIND_DEFAULT_0(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(void * __VA_OPT__(,) __VA_ARGS__))(void (*)(void))glue5(For, _, Type, \
                                                                _, Name),
#undef  ___TRAIT_ACT_BIND_DEFAULT_1
#define ___TRAIT_ACT_BIND_DEFAULT_1(Type, Ret, Name, ...)                        \
  .Name = (Ret (*)(const void * __VA_OPT__(,) __VA_ARGS__))(void (*)(void))glue5( \
      For, _, Type, _, Name),

// ── DFL actions ───────────────────────────────────────────────────────────────
#undef  ___TRAIT_ACT_DFL_DEFAULT_0
#define ___TRAIT_ACT_DFL_DEFAULT_0(Type, Ret, Name, ...)                         \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_DFL_, 0, _, 0, ___TRAIT_NARG(__VA_ARGS__)),                     \
    Type, Ret, Name __VA_OPT__(,) __VA_ARGS__)
#undef  ___TRAIT_ACT_DFL_DEFAULT_1
#define ___TRAIT_ACT_DFL_DEFAULT_1(Type, Ret, Name, ...)                         \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_DFL_, 0, _, 1, ___TRAIT_NARG(__VA_ARGS__)),                     \
    Type, Ret, Name __VA_OPT__(,) __VA_ARGS__)

// ── SDFL actions ──────────────────────────────────────────────────────────────
#undef  ___TRAIT_ACT_SDFL_DEFAULT_0
#define ___TRAIT_ACT_SDFL_DEFAULT_0(Type, Ret, Name, ...)                        \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_SDFL_, 0, _, 0, ___TRAIT_NARG(__VA_ARGS__)),                    \
    Type, Ret, Name __VA_OPT__(,) __VA_ARGS__)
#undef  ___TRAIT_ACT_SDFL_DEFAULT_1
#define ___TRAIT_ACT_SDFL_DEFAULT_1(Type, Ret, Name, ...)                        \
  ___TRAIT_IF_OVR(For, Type, Name, ,                                                   \
    glue5(___TRAIT_SDFL_, 0, _, 1, ___TRAIT_NARG(__VA_ARGS__)),                    \
    Type, Ret, Name __VA_OPT__(,) __VA_ARGS__)

// ── FWDDECL actions ───────────────────────────────────────────────────────────
#undef  ___TRAIT_ACT_FWDDECL_REQUIRE_0
#define ___TRAIT_ACT_FWDDECL_REQUIRE_0(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      For * __VA_OPT__(,) __VA_ARGS__);
#undef  ___TRAIT_ACT_FWDDECL_REQUIRE_1
#define ___TRAIT_ACT_FWDDECL_REQUIRE_1(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      const For * __VA_OPT__(,) __VA_ARGS__);
#undef  ___TRAIT_ACT_FWDDECL_DEFAULT_0
#define ___TRAIT_ACT_FWDDECL_DEFAULT_0(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      For * __VA_OPT__(,) __VA_ARGS__);
#undef  ___TRAIT_ACT_FWDDECL_DEFAULT_1
#define ___TRAIT_ACT_FWDDECL_DEFAULT_1(Type, Ret, Name, ...)                     \
  extern Ret glue5(For, _, Type, _, Name)(                                        \
      const For * __VA_OPT__(,) __VA_ARGS__);

// ── SD_emit / DynSD_emit ─────────────────────────────────────────────────────
#undef  ___TRAIT_SD_EMIT_I
#define ___TRAIT_SD_EMIT_I(NameSignature, ConstFlag, Ret, Name, ...)                 \
  typedef For glue8(___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _ty);   \
  typedef glue5(___sel_, Impl, _, Name, _t) glue8(                               \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _sty);               \
  typedef glue5(___sel_, NameSignature, _, Name, _t) glue8(                           \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _asty);             \
  typedef void (*glue8(___trait_sd_pair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, Impl, _, Name, _t), For); \
  typedef void (*glue8(___trait_sd_apair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, NameSignature, _, Name, _t), For); \
  glue5(___TRAIT_SDREG_, 0, _, ConstFlag,                                            \
        ___TRAIT_NARG(__VA_ARGS__))(NameSignature, Ret, Name __VA_OPT__(,) __VA_ARGS__)

#undef  ___TRAIT_DYNSD_EMIT_I
#define ___TRAIT_DYNSD_EMIT_I(NameSignature, ConstFlag, Ret, Name, ...)              \
  typedef glue(Dyn, Impl) glue8(___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5,       \
                                  ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _ty);  \
  typedef glue5(___sel_, Impl, _, Name, _t) glue8(                               \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _sty);               \
  typedef glue5(___sel_, NameSignature, _, Name, _t) glue8(                           \
      ___trait_sd_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _asty);             \
  typedef void (*glue8(___trait_sd_pair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, Impl, _, Name, _t), glue(Dyn, Impl)); \
  typedef void (*glue8(___trait_sd_apair_, ___TRAIT_SD_C6, ___TRAIT_SD_C5, ___TRAIT_SD_C4, ___TRAIT_SD_C3, ___TRAIT_SD_C2, ___TRAIT_SD_C1, _p))(glue5(___sel_, NameSignature, _, Name, _t), glue(Dyn, Impl)); \
  glue5(___TRAIT_DYNSDREG_, 0, _, ConstFlag,                                         \
        ___TRAIT_NARG(__VA_ARGS__))(Ret, Name __VA_OPT__(,) __VA_ARGS__)

// ── def / constdef ────────────────────────────────────────────────────────────
#undef  def
#define def(Name, ...)                                                         \
  glue5(For, _, Impl, _,                                                       \
        Name)(___TRAIT_IMPL_SELF_BASE * self                                   \
              __VA_OPT__(,) __VA_ARGS__)

#undef  constdef
#define constdef(Name, ...)                                                    \
  glue5(For, _, Impl, _,                                                       \
        Name)(const ___TRAIT_IMPL_SELF_BASE * self                             \
              __VA_OPT__(,) __VA_ARGS__)

// ── call ──────────────────────────────────────────────────────────────────────
#undef  call
#define call(sel, obj, ...)                                                       \
  _Generic(                                                                       \
      (void (*)(___TRAIT_TYPEOF(sel), ___TRAIT_TYPEOF(*(obj))))0,                 \
      ___TRAIT_SD_SLOTS                                                          \
      default: ERROR_trait_not_implemented_for_this_type                          \
  )(obj __VA_OPT__(,) __VA_ARGS__)

#endif // ___TRAIT_C23

#endif // TRAIT_ALT_H
