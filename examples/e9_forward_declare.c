// clang-format off
// e9_forward_declare.c — forward-declare: call() inside def() + defaults
//
// Tests Forward with both dynamic and static traits, including default methods
// (overridden and not overridden) to ensure no redeclaration errors.
//
// Order: all dynamic trait defs/impls first, then static, to avoid the
// ___TRAIT_IS_STATIC_CURRENT flag leaking across trait definitions.
#include "../trait.h"
#include <stdio.h>
#include <assert.h>

// ═════════════════════════════════════════════════════════════════════════════
// 1. Dynamic trait: Animal (required + default)
//    Signature declares method names only — no bodies.
//    Default bodies go in a For=Default block below.
// ═════════════════════════════════════════════════════════════════════════════
#define Dynamic
#define Trait Animal
#define AnimalSignature(Self)                    \
  required(Self, int,  get_snacks)            \
  required(Self, void, feed, int)             \
  defaults(Self, int, get_age)
#include "../trait.h"

// Default implementation for Animal
#define For Default
#define Impl Animal
int def(get_age) { (void)self; return 42; }
#include "../trait.h"

// ═════════════════════════════════════════════════════════════════════════════
// Type definitions
// ═════════════════════════════════════════════════════════════════════════════
typedef struct { int snacks; int age; } Dog;
typedef struct { int snacks; } Cat;

// ═════════════════════════════════════════════════════════════════════════════
// 2. Impl: Animal for Dog (dynamic, Forward, default OVERRIDDEN)
// ═════════════════════════════════════════════════════════════════════════════
#define For Dog
#define Impl Animal
#define Forward
#include "../trait.h"
  int def(get_snacks) { return self->snacks; }
  void def(feed, int amount) {
    int before = call(Animal.get_snacks, self);
    self->snacks += amount;
    int after = call(Animal.get_snacks, self);
    printf("  Dog: fed %d, snacks %d -> %d\n", amount, before, after);
  }
  #define Override_Dog_Animal_get_age 1
  int def(get_age) { return self->age; }
#include "../trait.h"

// ═════════════════════════════════════════════════════════════════════════════
// 3. Impl: Animal for Cat (dynamic, Forward, default NOT overridden)
// ═════════════════════════════════════════════════════════════════════════════
#define For Cat
#define Impl Animal
#define Forward
#include "../trait.h"
  int def(get_snacks) { return self->snacks; }
  void def(feed, int amount) { self->snacks += amount; }
  // get_age: NOT overridden — DFL wrapper uses default body (returns 42)
#include "../trait.h"

// ═════════════════════════════════════════════════════════════════════════════
// 4. Static trait: Drawable (required + default)
//    Signature declares method names only — no bodies.
// ═════════════════════════════════════════════════════════════════════════════
#define Trait Drawable
#define DrawableSignature(Self)                     \
  required(Self, void, draw)                      \
  defaults(Self, int,  is_visible)
#include "../trait.h"

// Default implementation for Drawable
#define For Default
#define Impl Drawable
int def(is_visible) { (void)self; return 1; }
#include "../trait.h"

// ═════════════════════════════════════════════════════════════════════════════
// Type definitions (static)
// ═════════════════════════════════════════════════════════════════════════════
typedef struct { const char *label; } Widget;
typedef struct { const char *label; int hidden; } HiddenWidget;

// ═════════════════════════════════════════════════════════════════════════════
// 5. Impl: Drawable for Widget (static, Forward, default NOT overridden)
// ═════════════════════════════════════════════════════════════════════════════
#define For Widget
#define Impl Drawable
#define Forward
#include "../trait.h"
  void def(draw) { printf("  Drawing widget: %s\n", self->label); }
  // is_visible: NOT overridden — SDFL wrapper uses default (returns 1)
#include "../trait.h"

// ═════════════════════════════════════════════════════════════════════════════
// 6. Impl: Drawable for HiddenWidget (static, Forward, default OVERRIDDEN)
// ═════════════════════════════════════════════════════════════════════════════
#define For HiddenWidget
#define Impl Drawable
#define Forward
#include "../trait.h"
  void def(draw) { printf("  Drawing widget: %s\n", self->label); }
  #define Override_HiddenWidget_Drawable_is_visible 1
  int def(is_visible) { return !self->hidden; }
#include "../trait.h"

// ═════════════════════════════════════════════════════════════════════════════
// main — test all scenarios
// ═════════════════════════════════════════════════════════════════════════════
int main(void) {
  int pass = 1;
  int tests = 0, passed = 0;
#define TEST(cond, msg)                                                        \
  do {                                                                         \
    tests++;                                                                   \
    if (cond) {                                                                \
      passed++;                                                                \
    } else {                                                                   \
      printf("  FAIL: %s\n", msg);                                             \
      pass = 0;                                                                \
    }                                                                          \
  } while (0)

  printf("=== forward_declare: call() inside def() + defaults ===\n\n");

  // ── Dog (dynamic, default overridden) ─────────────────────────────────
  printf("--- Dog (dynamic, default get_age OVERRIDDEN) ---\n");
  {
    Dog d = { .snacks = 5, .age = 7 };
    call(Animal.feed, &d, 3);
    TEST(d.snacks == 8, "Dog.feed(3) -> snacks == 8");
    int age = call(Animal.get_age, &d);
    TEST(age == 7, "Dog.get_age() == 7 (overridden)");
    printf("  Dog.get_age() = %d\n", age);

    DynAnimal da = dyn(Animal, &d);
    TEST(call(Animal.get_snacks, &da) == 8,
         "Dog.get_snacks via DynAnimal == 8");
  }

  // ── Cat (dynamic, default NOT overridden) ─────────────────────────────
  printf("\n--- Cat (dynamic, default get_age NOT overridden) ---\n");
  {
    Cat c = { .snacks = 10 };
    call(Animal.feed, &c, 5);
    TEST(c.snacks == 15, "Cat.feed(5) -> snacks == 15");
    int age = call(Animal.get_age, &c);
    TEST(age == 42, "Cat.get_age() == 42 (from DFL wrapper)");
    printf("  Cat.get_age() = %d (default)\n", age);
  }

  // ── Widget (static, default not overridden) ───────────────────────────
  printf("\n--- Widget (static, default is_visible NOT overridden) ---\n");
  {
    Widget w = { "button" };
    call(Drawable.draw, &w);
    int vis = call(Drawable.is_visible, &w);
    TEST(vis == 1, "Widget.is_visible() == 1 (from SDFL wrapper)");
    printf("  Widget.is_visible() = %d (default)\n", vis);
  }

  // ── HiddenWidget (static, default overridden) ─────────────────────────
  printf("\n--- HiddenWidget (static, default is_visible OVERRIDDEN) ---\n");
  {
    HiddenWidget hw1 = { "panel",   0 };
    HiddenWidget hw2 = { "secret", 1 };
    int vis1 = call(Drawable.is_visible, &hw1);
    int vis2 = call(Drawable.is_visible, &hw2);
    TEST(vis1 == 1, "HiddenWidget(visible).is_visible() == 1");
    TEST(vis2 == 0, "HiddenWidget(hidden).is_visible() == 0");
    printf("  HiddenWidget(visible).is_visible() = %d\n", vis1);
    printf("  HiddenWidget(hidden).is_visible() = %d\n", vis2);
  }

  // ── IMPLS compile-time checks ──────────────────────────────────────────
  static_assert(IMPLS(Dog, Animal),     "Dog must implement Animal");
  static_assert(IMPLS(Cat, Animal),     "Cat must implement Animal");
  static_assert(IMPLS(Widget, Drawable), "Widget must implement Drawable");
  static_assert(IMPLS(HiddenWidget, Drawable), "HiddenWidget must implement Drawable");

  printf("\n=== Results: %d/%d tests passed ===\n", passed, tests);
  if (pass) printf("ALL PASS\n");
  return pass ? 0 : 1;
}
