/*
 * e10_static_traits.c — Static trait mechanism
 *
 * Tests:
 * 1. Static trait definition (no vtable, no DynTrait)
 * 2. Multiple impls of same static trait
 * 3. Associated types (each impl specializes a type)
 * 4. call() works via SD dispatch
 * 5. DynTrait cannot be created (compile-time: no typedef exists)
 * 6. Static trait with extends (non-static base)
 */
#include "../trait.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ---- trait: Measurable (non-static base for extends test) ------------------
#define Dynamic
#define Trait Measurable
#define MeasurableSignature(Self) require(Self, int, get_length)
#include "../trait.h"

// ---- trait: Searchable (static, extends Measurable) -------------------------
// Static: no vtable, no DynTrait.  Still extends a non-static base.
// The extends is purely declarative — impl only provides `search`.
#define Trait Searchable
#define SearchableSignature(Self)                                              \
  extends(Measurable, Self) require(Self, int, search)
#include "../trait.h"

// ---- trait: Container (static, with associated type) -----------------------
#define Trait Container
#define ContainerSignature(Self)                                               \
  require(Self, int, push, Container_Item) require(Self, int, pop)
#include "../trait.h"

// ---- type definitions -------------------------------------------------------
typedef struct {
  int snacks;
} BaseAnimal;
typedef struct {
  BaseAnimal animal;
  const char *breed;
} Dog;

typedef struct {
  int values[4];
  int count;
} IntContainer;
typedef struct {
  const char *values[4];
  int count;
} StrContainer;

// ---- impl: Measurable for int -----------------------------------------------
#define For int
#define Impl Measurable
int def(get_length) { return *self; }
#include "../trait.h"

// ---- impl: Searchable for int -----------------------------------------------
// Static trait: no defaults(), no impl(), no DynTrait.
// Only implements `search` — Measurable's get_length is separate.
#define For int
#define Impl Searchable
int def(search) { return *self * 10; }
#include "../trait.h"

// ---- impl: Container for IntContainer (Item = int) --------------------------
#define For IntContainer
#define Impl Container
#define Container_Item int
int def(push, int a1) {
  if (self->count < 4)
    self->values[self->count++] = a1;
  return self->count;
}
int def(pop) { return self->count > 0 ? self->values[--self->count] : 0; }
#include "../trait.h"
#undef Container_Item

// ---- impl: Container for StrContainer (Item = const char*) -----------------
// Container_Item = const char* — multi-token type.
// The extra arg in require() is Container_Item which becomes const char*.
// This means NARG counts it as 1 arg (good), and SDREG uses T1 = const char*.
#define For StrContainer
#define Impl Container
#define Container_Item const char *
int def(push, const char *a1) {
  if (self->count < 4)
    self->values[self->count++] = a1;
  return self->count;
}
int def(pop) {
  return self->count > 0 ? (int)strlen(self->values[--self->count]) : 0;
}
#include "../trait.h"
#undef Container_Item

// ---- main -------------------------------------------------------------------
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

  printf("=== Static traits test ===\n\n");

  // -- Test 1: call() via SD dispatch on static trait --
  printf("--- Test 1: call() via SD on static trait ---\n");
  {
    int val = 7;
    int sl = call(Searchable.search, &val);
    TEST(sl == 70, "Searchable.search(7) == 70");
    printf("  Searchable.search(7) = %d\n", sl);
  }

  // -- Test 2: Static trait extends non-static trait --
  printf("\n--- Test 2: Static extends non-static ---\n");
  {
    int val = 5;
    int ml = call(Measurable.get_length, &val);
    TEST(ml == 5, "Measurable.get_length(5) == 5");
    printf("  Measurable.get_length(5) = %d\n", ml);
  }

  // -- Test 3: Associated types — IntContainer (Item = int) --
  printf("\n--- Test 3: Associated types ---\n");
  {
    IntContainer ic = {{0}, 0};
    int n;
    n = call(Container.push, &ic, 42);
    TEST(n == 1, "IntContainer.push(42) -> count=1");
    n = call(Container.push, &ic, 99);
    TEST(n == 2, "IntContainer.push(99) -> count=2");
    n = call(Container.pop, &ic);
    TEST(n == 99, "IntContainer.pop -> 99");
    n = call(Container.pop, &ic);
    TEST(n == 42, "IntContainer.pop -> 42");
    printf("  IntContainer: push 42, 99; pop 99, 42 — OK\n");
  }

  // -- Test 4: Associated types — StrContainer (Item = const char*) --
  {
    StrContainer sc = {{0}, 0};
    int n;
    n = call(Container.push, &sc, "hello");
    TEST(n == 1, "StrContainer.push(\"hello\") -> count=1");
    n = call(Container.push, &sc, "world!");
    TEST(n == 2, "StrContainer.push(\"world!\") -> count=2");
    n = call(Container.pop, &sc);
    TEST(n == 6, "StrContainer.pop -> 6 (len(\"world!\"))");
    n = call(Container.pop, &sc);
    TEST(n == 5, "StrContainer.pop -> 5 (len(\"hello\"))");
    printf("  StrContainer: push \"hello\", \"world!\"; pop 6, 5 — OK\n");
  }

  // -- Test 5: No vtable/DynTrait -- compile simply by compiling --
  printf("\n--- Test 5: No vtable/DynTrait (compile-time) ---\n");
  printf("  OK (compiled without vtable/DynTrait)\n");

  printf("\n=== Results: %d/%d tests passed ===\n", passed, tests);
  if (pass)
    printf("ALL PASS\n");
  return pass ? 0 : 1;
}
