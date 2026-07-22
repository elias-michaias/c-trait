// clang-format off
// e8_arity.c — Tests for impl methods of arbitrary arity (0–4 extra args).
// Covers: unary (self-only), binary (self + 1), ternary (self + 2),
// quaternary (self + 3), and quinary (self + 4) methods.
// Tests require, default, def, immutable, call, and direct calls.
#include "../trait.h"
#include <assert.h>
#include <stdio.h>

// ============================================================================
// TRAIT DEFINITIONS
// ============================================================================

// ---- Arity0: 0 extra args (unary: self only) --------------------------------
#define Arity0Signature(Self)                                \
  require(Self, int, get_val)                            \
  require(immutable(Self), int, peek_val)                \
  default(Self, void, double_it)
#define Dynamic
#define Trait Arity0
#include "../trait.h"

#define For Default
#define Impl Arity0
  def(void, double_it) {
    int v = call(Arity0.get_val, self);
    // Use add with the same value to double it
    (void)v;
  }
#include "../trait.h"

// ---- Arity1: 1 extra arg (binary: self + 1) --------------------------------
#define Arity1Signature(Self)                                \
  require(Self, void, set_val, int)                      \
  require(immutable(Self), int, add_pure, int)           \
  default(Self, void, increment, int)
#define Dynamic
#define Trait Arity1
#include "../trait.h"

#define For Default
#define Impl Arity1
  def(void, increment, int n) {
    int _new = call(Arity1.add_pure, self, n);
    call(Arity1.set_val, self, _new);
  }
#include "../trait.h"

// ---- Arity2: 2 extra args (ternary: self + 2) ------------------------------
#define Arity2Signature(Self)                                \
  require(Self, int, combine, int, int)                  \
  default(immutable(Self), int, combine_default, int, int)
#define Dynamic
#define Trait Arity2
#include "../trait.h"

#define For Default
#define Impl Arity2
  constdef(int, combine_default, int a, int b) {
    (void)self;
    return a + b;
  }
#include "../trait.h"

// ---- Arity3: 3 extra args (quaternary: self + 3) ----------------------------
#define Arity3Signature(Self)                                \
  require(Self, int, mix3, int, int, int)                \
  require(immutable(Self), int, sum3, int, int, int)     \
  default(Self, void, accum3, int, int, int)
#define Dynamic
#define Trait Arity3
#include "../trait.h"

#define For Default
#define Impl Arity3
  def(void, accum3, int a, int b, int c) {
    int total = call(Arity3.sum3, self, a, b, c);
    (void)total;
  }
#include "../trait.h"

// ---- Arity4: 4 extra args (quinary: self + 4) ------------------------------
#define Arity4Signature(Self)                                      \
  require(Self, int, mix4, int, int, int, int)                 \
  require(immutable(Self), int, sum4, int, int, int, int)      \
  default(immutable(Self), int, weighted4, int, int, int, int)
#define Dynamic
#define Trait Arity4
#include "../trait.h"

#define For Default
#define Impl Arity4
  constdef(int, weighted4, int a, int b, int c, int d) {
    return call(Arity4.sum4, self, a, b, c, d);
  }
#include "../trait.h"


// ============================================================================
// TYPE DEFINITIONS
// ============================================================================

typedef struct { int val; } Accum;
typedef struct { int x; int y; } Pair;


// ============================================================================
// IMPLS FOR Accum
// ============================================================================

// Arity0 for Accum
#define For Accum
#define Impl Arity0
  constdef(int, get_val) { return self->val; }
  constdef(int, peek_val) { return self->val; }
  // uses default double_it
#include "../trait.h"

// Arity1 for Accum
#define For Accum
#define Impl Arity1
  def(void, set_val, int v) { self->val = v; }
  constdef(int, add_pure, int n) { return self->val + n; }
  // uses default increment
#include "../trait.h"

// Arity2 for Accum
#define For Accum
#define Impl Arity2
  def(int, combine, int a, int b) { self->val = a * b; return self->val; }
  // uses default combine_default
#include "../trait.h"

// Arity3 for Accum
#define For Accum
#define Impl Arity3
  def(int, mix3, int a, int b, int c) {
    self->val = a + b + c;
    return self->val;
  }
  constdef(int, sum3, int a, int b, int c) {
    return self->val + a + b + c;
  }
  // uses default accum3
#include "../trait.h"

// Arity4 for Accum
#define For Accum
#define Impl Arity4
  def(int, mix4, int a, int b, int c, int d) {
    self->val = a + b + c + d;
    return self->val;
  }
  constdef(int, sum4, int a, int b, int c, int d) {
    return self->val + a + b + c + d;
  }
  // uses default weighted4
#include "../trait.h"


// ============================================================================
// IMPLS FOR Pair
// ============================================================================

// Arity0 for Pair
#define For Pair
#define Impl Arity0
  constdef(int, get_val) { return self->x + self->y; }
  constdef(int, peek_val) { return self->x + self->y; }
#include "../trait.h"

// Arity1 for Pair
#define For Pair
#define Impl Arity1
  def(void, set_val, int v) { self->x = v; self->y = 0; }
  constdef(int, add_pure, int n) { return self->x + self->y + n; }
  // override default increment
  def(void, increment, int n) { self->x += n; }
#define Override_Pair_Arity1_increment 1
#include "../trait.h"

// Arity2 for Pair
#define For Pair
#define Impl Arity2
  def(int, combine, int a, int b) {
    self->x = a;
    self->y = b;
    return a + b;
  }
  // override default combine_default
  constdef(int, combine_default, int a, int b) {
    return self->x * a + self->y * b;
  }
#define Override_Pair_Arity2_combine_default 1
#include "../trait.h"

// Arity3 for Pair
#define For Pair
#define Impl Arity3
  def(int, mix3, int a, int b, int c) {
    self->x = a + b;
    self->y = c;
    return self->x + self->y;
  }
  constdef(int, sum3, int a, int b, int c) {
    return self->x + self->y + a + b + c;
  }
#include "../trait.h"

// Arity4 for Pair
#define For Pair
#define Impl Arity4
  def(int, mix4, int a, int b, int c, int d) {
    self->x = a + b;
    self->y = c + d;
    return self->x + self->y;
  }
  constdef(int, sum4, int a, int b, int c, int d) {
    return self->x + self->y + a + b + c + d;
  }
  // override default weighted4
  constdef(int, weighted4, int a, int b, int c, int d) {
    return self->x * a + self->y * b + c + d;
  }
#define Override_Pair_Arity4_weighted4 1
#include "../trait.h"


// ============================================================================
// HELPER
// ============================================================================

static int tests_run   = 0;
static int tests_passed = 0;

#define CHECK(expr) do {                                                     \
    tests_run++;                                                             \
    if (expr) { tests_passed++; }                                            \
    else { printf("  FAIL line %d: %s\n", __LINE__, #expr); }                \
  } while (0)

#define SECTION(title) printf("\n--- %s ---\n", title)


// ============================================================================
// MAIN
// ============================================================================

int main(void) {
  printf("=== e8_arity: method arity tests (0–4 extra args) ===\n");

  // ==========================================================================
  SECTION("Arity0: 0 extra args (unary methods)");
  // ==========================================================================
  {
    Accum a = { .val = 42 };
    DynArity0 t = to_trait(Accum, Arity0, &a);

    CHECK(call(Arity0.get_val, &t) == 42);
    CHECK(call(Arity0.peek_val, &t) == 42);

    // Direct call
    CHECK(Accum_Arity0_get_val(&a) == 42);
    CHECK(Accum_Arity0_peek_val(&a) == 42);

    Pair p = { .x = 3, .y = 7 };
    DynArity0 t2 = to_trait(Pair, Arity0, &p);
    CHECK(call(Arity0.get_val, &t2) == 10);
    CHECK(call(Arity0.peek_val, &t2) == 10);
  }

  // ==========================================================================
  SECTION("Arity1: 1 extra arg (binary methods)");
  // ==========================================================================
  {
    // Accum: uses default increment
    Accum a = { .val = 10 };
    DynArity1 t = to_trait(Accum, Arity1, &a);

    CHECK(call(Arity1.add_pure, &t, 5) == 15);
    CHECK(a.val == 10);  // add_pure is immutable, no mutation

    call(Arity1.set_val, &t, 20);
    CHECK(a.val == 20);

    // default increment: set_val(add_pure(n))
    call(Arity1.increment, &t, 7);
    CHECK(a.val == 27);

    // Pair: def increment to just add to x
    Pair p = { .x = 10, .y = 5 };
    DynArity1 t2 = to_trait(Pair, Arity1, &p);

    CHECK(call(Arity1.add_pure, &t2, 3) == 18);  // 10+5+3
    call(Arity1.increment, &t2, 4);              // def: x += 4
    CHECK(p.x == 14);
    CHECK(p.y == 5);  // y unchanged

    // Direct calls
    CHECK(Accum_Arity1_add_pure(&a, 3) == 30);  // 27+3
    Accum_Arity1_set_val(&a, 100);
    CHECK(a.val == 100);
  }

  // ==========================================================================
  SECTION("Arity2: 2 extra args (ternary methods)");
  // ==========================================================================
  {
    Accum a = { .val = 0 };
    DynArity2 t = to_trait(Accum, Arity2, &a);

    int r = call(Arity2.combine, &t, 6, 7);
    CHECK(r == 42);
    CHECK(a.val == 42);

    // default combine_default: a + b (ignores self)
    CHECK(call(Arity2.combine_default, &t, 10, 20) == 30);

    // Pair: def combine_default
    Pair p = { .x = 3, .y = 4 };
    DynArity2 t2 = to_trait(Pair, Arity2, &p);

    call(Arity2.combine, &t2, 5, 6);
    CHECK(p.x == 5);
    CHECK(p.y == 6);

    // def combine_default: x*a + y*b
    CHECK(call(Arity2.combine_default, &t2, 10, 100) == 650);  // 5*10 + 6*100

    // Direct calls
    CHECK(Pair_Arity2_combine_default(&p, 2, 3) == 28);  // 5*2 + 6*3
  }

  // ==========================================================================
  SECTION("Arity3: 3 extra args (quaternary methods)");
  // ==========================================================================
  {
    Accum a = { .val = 100 };
    DynArity3 t = to_trait(Accum, Arity3, &a);

    // sum3 (immutable): self->val + a + b + c
    CHECK(call(Arity3.sum3, &t, 1, 2, 3) == 106);  // 100+1+2+3
    CHECK(a.val == 100);  // unchanged

    // mix3 (mutable): self->val = a+b+c
    int r = call(Arity3.mix3, &t, 10, 20, 30);
    CHECK(r == 60);
    CHECK(a.val == 60);

    // sum3 again with new value
    CHECK(call(Arity3.sum3, &t, 1, 1, 1) == 63);  // 60+1+1+1

    // Pair
    Pair p = { .x = 0, .y = 0 };
    DynArity3 t2 = to_trait(Pair, Arity3, &p);

    int r2 = call(Arity3.mix3, &t2, 5, 10, 15);
    CHECK(r2 == 30);     // x=5+10=15, y=15, total=30
    CHECK(p.x == 15);
    CHECK(p.y == 15);

    CHECK(call(Arity3.sum3, &t2, 1, 2, 3) == 36);  // 15+15+1+2+3

    // Direct calls
    CHECK(Accum_Arity3_sum3(&a, 0, 0, 0) == 60);
    Accum_Arity3_mix3(&a, 1, 2, 3);
    CHECK(a.val == 6);
  }

  // ==========================================================================
  SECTION("Arity4: 4 extra args (quinary methods)");
  // ==========================================================================
  {
    Accum a = { .val = 0 };
    DynArity4 t = to_trait(Accum, Arity4, &a);

    // mix4 (mutable): self->val = a+b+c+d
    int r = call(Arity4.mix4, &t, 1, 2, 3, 4);
    CHECK(r == 10);
    CHECK(a.val == 10);

    // sum4 (immutable): self->val + a+b+c+d
    CHECK(call(Arity4.sum4, &t, 10, 20, 30, 40) == 110);  // 10+10+20+30+40
    CHECK(a.val == 10);  // unchanged

    // default weighted4 (calls sum4): self->val + a+b+c+d
    CHECK(call(Arity4.weighted4, &t, 1, 1, 1, 1) == 14);  // 10+1+1+1+1

    // Pair: def weighted4
    Pair p = { .x = 2, .y = 3 };
    DynArity4 t2 = to_trait(Pair, Arity4, &p);

    int r2 = call(Arity4.mix4, &t2, 10, 20, 30, 40);
    CHECK(r2 == 100);    // x=10+20=30, y=30+40=70, total=100
    CHECK(p.x == 30);
    CHECK(p.y == 70);

    CHECK(call(Arity4.sum4, &t2, 1, 2, 3, 4) == 110);  // 30+70+1+2+3+4

    // def weighted4: x*a + y*b + c + d
    CHECK(call(Arity4.weighted4, &t2, 2, 3, 5, 7) == 282);  // 30*2+70*3+5+7

    // Direct calls
    CHECK(Accum_Arity4_sum4(&a, 0, 0, 0, 0) == 10);
    CHECK(Pair_Arity4_weighted4(&p, 1, 1, 0, 0) == 100);  // 30+70+0+0
  }

  // ==========================================================================
  SECTION("Mixed arity: same type uses all arities");
  // ==========================================================================
  {
    Accum a = { .val = 5 };

    DynArity0 t0 = to_trait(Accum, Arity0, &a);
    DynArity1 t1 = to_trait(Accum, Arity1, &a);
    DynArity2 t2 = to_trait(Accum, Arity2, &a);
    DynArity3 t3 = to_trait(Accum, Arity3, &a);
    DynArity4 t4 = to_trait(Accum, Arity4, &a);

    CHECK(call(Arity0.get_val, &t0) == 5);
    call(Arity1.set_val, &t1, 10);
    CHECK(call(Arity0.get_val, &t0) == 10);  // same underlying object

    call(Arity2.combine, &t2, 3, 4);
    CHECK(a.val == 12);  // 3*4

    call(Arity3.mix3, &t3, 1, 2, 3);
    CHECK(a.val == 6);   // 1+2+3

    call(Arity4.mix4, &t4, 10, 20, 30, 40);
    CHECK(a.val == 100); // 10+20+30+40

    CHECK(call(Arity0.peek_val, &t0) == 100);
  }

  // ==========================================================================
  // Summary
  // ==========================================================================
  printf("\n=== Results: %d/%d tests passed ===\n", tests_passed, tests_run);
  if (tests_passed != tests_run) {
    printf("SOME TESTS FAILED\n");
    return 1;
  }
  printf("ALL TESTS PASSED\n");
  return 0;
}
