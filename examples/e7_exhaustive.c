// clang-format off
// e7_exhaustive.c — Exhaustive tests for c-trait
// Covers: multiple traits, multiple types, varying arg counts/types,
// require/default/def, immutable, extends, parametric traits,
// vcall/to_trait/from_trait/new_trait, assertions.
#include "../trait.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

// ============================================================================
// TRAIT DEFINITIONS
// ============================================================================

// ---- Stringify: 0-arg require (immutable) -----------------------------------
#define StringifySignature(Self)                            \
  require(immutable(Self), const char *, stringify)
#define Dynamic
#define Trait Stringify
#include "../trait.h"

// ---- Describable: 0-arg default (immutable) + 0-arg require -----------------
#define DescribableSignature(Self)                           \
  require(immutable(Self), const char *, name)           \
  default(immutable(Self), int,          name_len)
#define Dynamic
#define Trait Describable
#include "../trait.h"

#define For Default
#define Impl Describable
  int constdef(name_len) {
    return (int)strlen(call(Describable.name, self));
  }
#include "../trait.h"

// ---- Arithmetic: 1-arg methods, mixed mutability ----------------------------
#define ArithmeticSignature(Self)                        \
  require(Self,            void, add, int)               \
  require(Self,            void, mul, int)               \
  require(immutable(Self), int,  value)                  \
  default(immutable(Self), int,  doubled)                \
  default(Self,            void, reset)
#define Dynamic
#define Trait Arithmetic
#include "../trait.h"

#define For Default
#define Impl Arithmetic
  int constdef(doubled) {
    return call(Arithmetic.value, self) * 2;
  }
  void def(reset) {
    call(Arithmetic.mul, self, 0);
  }
#include "../trait.h"

// ---- Transform: 2-arg method ------------------------------------------------
#define TransformSignature(Self)                             \
  require(Self, int, apply, int, int)                    \
  default(immutable(Self), const char *, kind)
#define Dynamic
#define Trait Transform
#include "../trait.h"

#define For Default
#define Impl Transform
  const char * constdef(kind) {
    (void)self;
    return "unknown";
  }
#include "../trait.h"

// ---- Mapper: 2-arg method with pointer + int --------------------------------
#define MapperSignature(Self)                                \
  require(immutable(Self), int, map_val, int, int)
#define Dynamic
#define Trait Mapper
#include "../trait.h"

// ---- Cloneable: returns pointer type ----------------------------------------
#define CloneableSignature(Self)                             \
  require(immutable(Self), void *, clone)
#define Dynamic
#define Trait Cloneable
#include "../trait.h"

// ---- Resettable: 0-arg mutable require + default ----------------------------
#define ResettableSignature(Self)                            \
  require(Self, void, zero_out)                          \
  default(Self, void, zero_and_report)
#define Dynamic
#define Trait Resettable
#include "../trait.h"

#define For Default
#define Impl Resettable
  void def(zero_and_report) {
    call(Resettable.zero_out, self);
    printf("  zeroed out\n");
  }
#include "../trait.h"

// ---- Measurable extends Describable: trait inheritance -----------------------
#define MeasurableSignature(Self)                            \
  extends(Describable, Self)                             \
  require(immutable(Self), int,    measure)              \
  default(immutable(Self), int,    is_big)
#define Dynamic
#define Trait Measurable
#include "../trait.h"

#define For Default
#define Impl Measurable
  int constdef(is_big) {
    return call(Measurable.measure, self) > 100;
  }
#include "../trait.h"

// ---- Parametric: Container with int and double ------------------------------
#define ContainerSignature(Self, T)                          \
  require(immutable(Self), T,    peek)                   \
  require(Self,            void, poke, T)

#define Container_intSignature(Self)    ContainerSignature(Self, int)
#define Container_doubleSignature(Self) ContainerSignature(Self, double)
#define Dynamic
#define Trait Container_int
#include "../trait.h"
#define Dynamic
#define Trait Container_double
#include "../trait.h"


// ============================================================================
// TYPE DEFINITIONS
// ============================================================================

typedef struct { int val; } IntWrapper;
typedef struct { double val; } DoubleWrapper;
typedef struct { const char *label; int x; int y; } Point;
typedef struct { const char *label; double width; double height; } Rect;
typedef struct { char buf[64]; int len; } StrBuf;
typedef struct { int a; int b; int c; int d; } Quad;


// ============================================================================
// IMPLS FOR IntWrapper
// ============================================================================

// Stringify for IntWrapper
#define For IntWrapper
#define Impl Stringify
  const char * constdef(stringify) {
    (void)self;
    // returns a fixed string for test simplicity
    return "IntWrapper";
  }
#include "../trait.h"

// Describable for IntWrapper
#define For IntWrapper
#define Impl Describable
  const char * constdef(name) { (void)self; return "IntWrapper"; }
#include "../trait.h"

// Arithmetic for IntWrapper
#define For IntWrapper
#define Impl Arithmetic
  void def(add, int n) { self->val += n; }
  void def(mul, int n) { self->val *= n; }
  int constdef(value)       { return self->val; }
  // uses default doubled and reset
#include "../trait.h"

// Resettable for IntWrapper
#define For IntWrapper
#define Impl Resettable
  void def(zero_out) { self->val = 0; }
  // uses default zero_and_report
#include "../trait.h"

// Container_int for IntWrapper
#define For IntWrapper
#define Impl Container_int
  int constdef(peek)          { return self->val; }
  void def(poke, int v)  { self->val = v; }
#include "../trait.h"

// Mapper for IntWrapper
#define For IntWrapper
#define Impl Mapper
  int constdef(map_val, int a, int b) {
    return self->val + a + b;
  }
#include "../trait.h"


// ============================================================================
// IMPLS FOR DoubleWrapper
// ============================================================================

// Stringify for DoubleWrapper
#define For DoubleWrapper
#define Impl Stringify
  const char * constdef(stringify) {
    (void)self;
    return "DoubleWrapper";
  }
#include "../trait.h"

// Describable for DoubleWrapper
#define For DoubleWrapper
#define Impl Describable
  const char * constdef(name) { (void)self; return "DoubleWrapper"; }
  // override default name_len to always return 13
  #define Override_DoubleWrapper_Describable_name_len 1
  int constdef(name_len) { (void)self; return 13; }
#include "../trait.h"


// Container_double for DoubleWrapper
#define For DoubleWrapper
#define Impl Container_double
  double constdef(peek)           { return self->val; }
  void def(poke, double v)   { self->val = v; }
#include "../trait.h"

// Mapper for DoubleWrapper
#define For DoubleWrapper
#define Impl Mapper
  int constdef(map_val, int a, int b) {
    return (int)self->val * a * b;
  }
#include "../trait.h"


// ============================================================================
// IMPLS FOR Point
// ============================================================================

// Stringify for Point
#define For Point
#define Impl Stringify
  const char * constdef(stringify) { return self->label; }
#include "../trait.h"

// Describable for Point
#define For Point
#define Impl Describable
  const char * constdef(name) { return self->label; }
  // uses default name_len
#include "../trait.h"

// Arithmetic for Point (operates on x)
#define For Point
#define Impl Arithmetic
  void def(add, int n) { self->x += n; }
  void def(mul, int n) { self->x *= n; }
  int constdef(value)       { return self->x; }
  // override reset to zero both x and y
  void def(reset)    { self->x = 0; self->y = 0; }
#define Override_Point_Arithmetic_reset 1
#include "../trait.h"

// Transform for Point
#define For Point
#define Impl Transform
  int def(apply, int a, int b) { self->x += a; self->y += b; return self->x + self->y; }
  const char * constdef(kind) { (void)self; return "point_translate"; }
#define Override_Point_Transform_kind 1
#include "../trait.h"

// Mapper for Point
#define For Point
#define Impl Mapper
  int constdef(map_val, int a, int b) {
    return self->x * a + self->y * b;
  }
#include "../trait.h"

// Resettable for Point
#define For Point
#define Impl Resettable
  void def(zero_out) { self->x = 0; self->y = 0; }
#include "../trait.h"

// Measurable for Point (extends Describable)
#define For Point
#define Impl Measurable
  int constdef(measure) { return self->x * self->x + self->y * self->y; }
  // uses default is_big
#include "../trait.h"

// Mapper for Rect
#define For Rect
#define Impl Mapper
  int constdef(map_val, int a, int b) {
    return (int)(self->width * a + self->height * b);
  }
#include "../trait.h"


// ============================================================================
// IMPLS FOR Rect
// ============================================================================

// Stringify for Rect
#define For Rect
#define Impl Stringify
  const char * constdef(stringify) { return self->label; }
#include "../trait.h"

// Describable for Rect
#define For Rect
#define Impl Describable
  const char * constdef(name) { return self->label; }
#include "../trait.h"

// Measurable for Rect (extends Describable)
#define For Rect
#define Impl Measurable
  int constdef(measure) { return (int)(self->width * self->height); }
  // override is_big: big if area > 50
  int constdef(is_big) { return (int)(self->width * self->height) > 50; }
#define Override_Rect_Measurable_is_big 1
#include "../trait.h"

// Container_double for Rect (peek/poke width)
#define For Rect
#define Impl Container_double
  double constdef(peek)           { return self->width; }
  void def(poke, double v)   { self->width = v; }
#include "../trait.h"


// ============================================================================
// IMPLS FOR StrBuf
// ============================================================================

// Stringify for StrBuf
#define For StrBuf
#define Impl Stringify
  const char * constdef(stringify) { return self->buf; }
#include "../trait.h"

// Describable for StrBuf
#define For StrBuf
#define Impl Describable
  const char * constdef(name) { (void)self; return "StrBuf"; }
  int constdef(name_len) { (void)self; return 6; }
#define Override_StrBuf_Describable_name_len 1
#include "../trait.h"

// Cloneable for StrBuf
#define For StrBuf
#define Impl Cloneable
  static StrBuf _strbuf_clone_storage;
  void * constdef(clone) {
    _strbuf_clone_storage = *self;
    return &_strbuf_clone_storage;
  }
#include "../trait.h"


// ============================================================================
// IMPLS FOR Quad
// ============================================================================

// Mapper for Quad
#define For Quad
#define Impl Mapper
  int constdef(map_val, int a, int b) {
    return self->a * a + self->b * b;
  }
#include "../trait.h"

// Arithmetic for Quad (operates on 'a')
#define For Quad
#define Impl Arithmetic
  void def(add, int n) { self->a += n; }
  void def(mul, int n) { self->a *= n; }
  int constdef(value)       { return self->a; }
  // override doubled to sum all fields doubled
  int constdef(doubled)   { return (self->a + self->b + self->c + self->d) * 2; }
#define Override_Quad_Arithmetic_doubled 1
#include "../trait.h"

// Resettable for Quad
#define For Quad
#define Impl Resettable
  void def(zero_out) { self->a = 0; self->b = 0; self->c = 0; self->d = 0; }
  // override zero_and_report
  void def(zero_and_report) {
    self->a = 0; self->b = 0; self->c = 0; self->d = 0;
    printf("  quad fully zeroed\n");
  }
#define Override_Quad_Resettable_zero_and_report 1
#include "../trait.h"

// Transform for Quad
#define For Quad
#define Impl Transform
  int def(apply, int x, int y) {
    self->a += x;
    self->b += y;
    return self->a + self->b + self->c + self->d;
  }
  const char * constdef(kind) { (void)self; return "quad_shift"; }
#define Override_Quad_Transform_kind 1
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
  printf("=== e7_exhaustive: comprehensive trait tests ===\n");

  // ---- Instantiate types ----------------------------------------------------
  IntWrapper    iw  = { .val = 10 };
  DoubleWrapper dw  = { .val = 3.14 };
  Point         pt  = { .label = "origin", .x = 3, .y = 4 };
  Rect          r   = { .label = "box", .width = 8.0, .height = 7.0 };
  StrBuf        sb  = { .buf = "hello", .len = 5 };

  // ==========================================================================
  SECTION("Stringify (0-arg, immutable, require-only)");
  // ==========================================================================
  {
    DynStringify s1 = to_trait(IntWrapper, Stringify, &iw);
    DynStringify s2 = to_trait(DoubleWrapper, Stringify, &dw);
    DynStringify s3 = to_trait(Point, Stringify, &pt);
    DynStringify s4 = to_trait(Rect, Stringify, &r);
    DynStringify s5 = to_trait(StrBuf, Stringify, &sb);

    CHECK(strcmp(call(Stringify.stringify, &s1), "IntWrapper") == 0);
    CHECK(strcmp(call(Stringify.stringify, &s2), "DoubleWrapper") == 0);
    CHECK(strcmp(call(Stringify.stringify, &s3), "origin") == 0);
    CHECK(strcmp(call(Stringify.stringify, &s4), "box") == 0);
    CHECK(strcmp(call(Stringify.stringify, &s5), "hello") == 0);
  }

  // ==========================================================================
  SECTION("Describable (0-arg, immutable, require + default + def)");
  // ==========================================================================
  {
    DynDescribable d1 = to_trait(IntWrapper, Describable, &iw);
    DynDescribable d2 = to_trait(DoubleWrapper, Describable, &dw);
    DynDescribable d3 = to_trait(Point, Describable, &pt);
    DynDescribable d4 = to_trait(Rect, Describable, &r);
    DynDescribable d5 = to_trait(StrBuf, Describable, &sb);

    // name (required)
    CHECK(strcmp(call(Describable.name, &d1), "IntWrapper") == 0);
    CHECK(strcmp(call(Describable.name, &d2), "DoubleWrapper") == 0);
    CHECK(strcmp(call(Describable.name, &d3), "origin") == 0);
    CHECK(strcmp(call(Describable.name, &d4), "box") == 0);
    CHECK(strcmp(call(Describable.name, &d5), "StrBuf") == 0);

    // name_len: default (strlen of name) vs def
    CHECK(call(Describable.name_len, &d1) == 10);  // default: strlen("IntWrapper")
    CHECK(call(Describable.name_len, &d2) == 13);  // def: always 13
    CHECK(call(Describable.name_len, &d3) == 6);   // default: strlen("origin")
    CHECK(call(Describable.name_len, &d4) == 3);   // default: strlen("box")
    CHECK(call(Describable.name_len, &d5) == 6);   // def: always 6
  }

  // ==========================================================================
  SECTION("Arithmetic (1-arg, mutable+immutable, require+default+def)");
  // ==========================================================================
  {
    // IntWrapper: uses default doubled & reset
    IntWrapper iw2 = { .val = 5 };
    DynArithmetic a1 = to_trait(IntWrapper, Arithmetic, &iw2);

    CHECK(call(Arithmetic.value, &a1) == 5);
    call(Arithmetic.add, &a1, 3);
    CHECK(call(Arithmetic.value, &a1) == 8);
    call(Arithmetic.mul, &a1, 2);
    CHECK(call(Arithmetic.value, &a1) == 16);
    CHECK(call(Arithmetic.doubled, &a1) == 32);   // default: value * 2
    call(Arithmetic.reset, &a1);                  // default: mul by 0
    CHECK(call(Arithmetic.value, &a1) == 0);

    // Point: overrides reset
    Point pt2 = { .label = "p", .x = 3, .y = 4 };
    DynArithmetic a2 = to_trait(Point, Arithmetic, &pt2);

    CHECK(call(Arithmetic.value, &a2) == 3);
    call(Arithmetic.add, &a2, 7);
    CHECK(call(Arithmetic.value, &a2) == 10);
    call(Arithmetic.reset, &a2);                  // def: zeros x AND y
    CHECK(pt2.x == 0);
    CHECK(pt2.y == 0);

    // Quad: overrides doubled
    Quad q2 = { .a = 2, .b = 3, .c = 4, .d = 5 };
    DynArithmetic a3 = to_trait(Quad, Arithmetic, &q2);

    CHECK(call(Arithmetic.value, &a3) == 2);
    CHECK(call(Arithmetic.doubled, &a3) == 28);   // def: (2+3+4+5)*2
    call(Arithmetic.add, &a3, 8);
    CHECK(call(Arithmetic.value, &a3) == 10);
    CHECK(call(Arithmetic.doubled, &a3) == 44);   // (10+3+4+5)*2
  }

  // ==========================================================================
  SECTION("Transform (2-arg method + default kind)");
  // ==========================================================================
  {
    // Point: overrides kind
    Point pt3 = { .label = "t", .x = 0, .y = 0 };
    DynTransform t1 = to_trait(Point, Transform, &pt3);

    int sum = call(Transform.apply, &t1, 5, 10);
    CHECK(sum == 15);                      // x=5, y=10, sum=15
    CHECK(pt3.x == 5);
    CHECK(pt3.y == 10);
    CHECK(strcmp(call(Transform.kind, &t1), "point_translate") == 0);

    // Quad: overrides kind
    Quad q3 = { .a = 0, .b = 0, .c = 1, .d = 1 };
    DynTransform t2 = to_trait(Quad, Transform, &q3);

    sum = call(Transform.apply, &t2, 10, 20);
    CHECK(sum == 32);                      // a=10, b=20, c=1, d=1
    CHECK(q3.a == 10);
    CHECK(q3.b == 20);
    CHECK(strcmp(call(Transform.kind, &t2), "quad_shift") == 0);
  }

  // ==========================================================================
  SECTION("Mapper (2-arg method, immutable)");
  // ==========================================================================
  {
    // IntWrapper: self->val + a + b
    IntWrapper iw3 = { .val = 10 };
    DynMapper m1 = to_trait(IntWrapper, Mapper, &iw3);
    CHECK(call(Mapper.map_val, &m1, 3, 7) == 20);   // 10+3+7

    // DoubleWrapper: (int)self->val * a * b
    DoubleWrapper dw2 = { .val = 3.0 };
    DynMapper m2 = to_trait(DoubleWrapper, Mapper, &dw2);
    CHECK(call(Mapper.map_val, &m2, 4, 5) == 60);   // 3*4*5

    // Point: x*a + y*b
    Point pt5 = { .label = "m", .x = 2, .y = 3 };
    DynMapper m3 = to_trait(Point, Mapper, &pt5);
    CHECK(call(Mapper.map_val, &m3, 10, 100) == 320); // 2*10+3*100

    // Rect: (int)(width*a + height*b)
    Rect r2 = { .label = "mr", .width = 2.0, .height = 3.0 };
    DynMapper m4 = to_trait(Rect, Mapper, &r2);
    CHECK(call(Mapper.map_val, &m4, 5, 10) == 40);   // 2*5+3*10

    // Quad: a*x + b*y
    Quad q4 = { .a = 3, .b = 7, .c = 0, .d = 0 };
    DynMapper m5 = to_trait(Quad, Mapper, &q4);
    CHECK(call(Mapper.map_val, &m5, 2, 4) == 34);    // 3*2+7*4
  }

  // ==========================================================================
  SECTION("Cloneable (returns pointer)");
  // ==========================================================================
  {
    StrBuf sb2 = { .buf = "clone_me", .len = 8 };
    DynCloneable cl = to_trait(StrBuf, Cloneable, &sb2);
    StrBuf *cloned = (StrBuf *)call(Cloneable.clone, &cl);
    CHECK(cloned != &sb2);
    CHECK(strcmp(cloned->buf, "clone_me") == 0);
    CHECK(cloned->len == 8);
  }

  // ==========================================================================
  SECTION("Resettable (0-arg mutable, default + def)");
  // ==========================================================================
  {
    // IntWrapper: uses default zero_and_report
    IntWrapper iw4 = { .val = 99 };
    DynResettable r1 = to_trait(IntWrapper, Resettable, &iw4);
    printf("  IntWrapper zero_and_report: ");
    call(Resettable.zero_and_report, &r1);
    CHECK(iw4.val == 0);

    // Point: uses default zero_and_report
    Point pt6 = { .label = "r", .x = 5, .y = 5 };
    DynResettable r2 = to_trait(Point, Resettable, &pt6);
    call(Resettable.zero_out, &r2);
    CHECK(pt6.x == 0);
    CHECK(pt6.y == 0);

    // Quad: overrides zero_and_report
    Quad q5 = { .a = 1, .b = 2, .c = 3, .d = 4 };
    DynResettable r3 = to_trait(Quad, Resettable, &q5);
    printf("  Quad zero_and_report: ");
    call(Resettable.zero_and_report, &r3);
    CHECK(q5.a == 0);
    CHECK(q5.b == 0);
    CHECK(q5.c == 0);
    CHECK(q5.d == 0);
  }

  // ==========================================================================
  SECTION("Measurable extends Describable (trait inheritance)");
  // ==========================================================================
  {
    // Point: default is_big (threshold 100)
    Point pt7 = { .label = "small_pt", .x = 3, .y = 4 };
    DynMeasurable m1 = to_trait(Point, Measurable, &pt7);
    CHECK(call(Measurable.measure, &m1) == 25);   // 3*3 + 4*4
    CHECK(call(Measurable.is_big, &m1) == 0);

    // Describable methods via DynDescribable (separate trait object)
    DynDescribable dd_pt = to_trait(Point, Describable, &pt7);
    CHECK(strcmp(call(Describable.name, &dd_pt), "small_pt") == 0);
    CHECK(call(Describable.name_len, &dd_pt) == 8);  // default strlen("small_pt")

    // Rect: overrides is_big (threshold 50)
    Rect r3 = { .label = "big_rect", .width = 10.0, .height = 6.0 };
    DynMeasurable m2 = to_trait(Rect, Measurable, &r3);
    CHECK(call(Measurable.measure, &m2) == 60);
    CHECK(call(Measurable.is_big, &m2) == 1);

    // Describable via DynDescribable
    DynDescribable dd_r3 = to_trait(Rect, Describable, &r3);
    CHECK(strcmp(call(Describable.name, &dd_r3), "big_rect") == 0);

    // small rect
    Rect r4 = { .label = "tiny", .width = 2.0, .height = 3.0 };
    DynMeasurable m3 = to_trait(Rect, Measurable, &r4);
    CHECK(call(Measurable.measure, &m3) == 6);
    CHECK(call(Measurable.is_big, &m3) == 0);
  }

  // ==========================================================================
  SECTION("Parametric traits: Container_int, Container_double");
  // ==========================================================================
  {
    IntWrapper iw5 = { .val = 42 };
    DynContainer_int ci = to_trait(IntWrapper, Container_int, &iw5);
    CHECK(call(Container_int.peek, &ci) == 42);
    call(Container_int.poke, &ci, 100);
    CHECK(call(Container_int.peek, &ci) == 100);
    CHECK(iw5.val == 100);

    DoubleWrapper dw3 = { .val = 2.718 };
    DynContainer_double cd1 = to_trait(DoubleWrapper, Container_double, &dw3);
    CHECK(call(Container_double.peek, &cd1) > 2.717 && call(Container_double.peek, &cd1) < 2.719);
    call(Container_double.poke, &cd1, 1.414);
    CHECK(call(Container_double.peek, &cd1) > 1.413 && call(Container_double.peek, &cd1) < 1.415);

    // Rect also implements Container_double (peek/poke width)
    Rect r5 = { .label = "w", .width = 5.0, .height = 3.0 };
    DynContainer_double cd2 = to_trait(Rect, Container_double, &r5);
    CHECK(call(Container_double.peek, &cd2) > 4.999 && call(Container_double.peek, &cd2) < 5.001);
    call(Container_double.poke, &cd2, 99.0);
    CHECK(r5.width > 98.999 && r5.width < 99.001);
  }

  // ==========================================================================
  SECTION("from_trait: recover concrete pointer");
  // ==========================================================================
  {
    Point pt8 = { .label = "recover", .x = 11, .y = 22 };
    DynStringify s = to_trait(Point, Stringify, &pt8);
    Point *recovered = from_trait(Point, Stringify, s);
    CHECK(recovered == &pt8);
    CHECK(recovered->x == 11);
    CHECK(recovered->y == 22);

    Rect r6 = { .label = "fr", .width = 1.0, .height = 2.0 };
    DynMeasurable m = to_trait(Rect, Measurable, &r6);
    Rect *rrec = from_trait(Rect, Measurable, m);
    CHECK(rrec == &r6);
    CHECK(rrec->width > 0.999 && rrec->width < 1.001);
  }

  // ==========================================================================
  SECTION("new_trait: literal construction");
  // ==========================================================================
  {
    DynStringify s = new_trait(IntWrapper, Stringify, { .val = 0 });
    CHECK(strcmp(call(Stringify.stringify, &s), "IntWrapper") == 0);

    DynContainer_int ci = new_trait(IntWrapper, Container_int, { .val = 77 });
    CHECK(call(Container_int.peek, &ci) == 77);
  }

  // ==========================================================================
  SECTION("Direct static function calls (Type_Trait_method pattern)");
  // ==========================================================================
  {
    // Static dispatch can be done directly by calling the generated functions
    IntWrapper iw6 = { .val = 5 };
    CHECK(IntWrapper_Arithmetic_value(&iw6) == 5);
    IntWrapper_Arithmetic_add(&iw6, 10);
    CHECK(IntWrapper_Arithmetic_value(&iw6) == 15);
    IntWrapper_Arithmetic_mul(&iw6, 3);
    CHECK(IntWrapper_Arithmetic_value(&iw6) == 45);
    CHECK(IntWrapper_Arithmetic_doubled(&iw6) == 90);

    Point pt9 = { .label = "s", .x = 7, .y = 3 };
    CHECK(Point_Arithmetic_value(&pt9) == 7);
    Point_Arithmetic_add(&pt9, 3);
    CHECK(Point_Arithmetic_value(&pt9) == 10);

    Quad q6 = { .a = 2, .b = 4, .c = 6, .d = 8 };
    CHECK(Quad_Arithmetic_doubled(&q6) == 40);  // (2+4+6+8)*2

    // Stringify direct calls
    CHECK(strcmp(IntWrapper_Stringify_stringify(&iw6), "IntWrapper") == 0);
    CHECK(strcmp(Point_Stringify_stringify(&pt9), "s") == 0);

    // Mapper direct calls
    CHECK(IntWrapper_Mapper_map_val(&iw6, 5, 10) == 60);  // 45+5+10

    // Transform direct calls
    Point pt10 = { .label = "sc", .x = 0, .y = 0 };
    int r = Point_Transform_apply(&pt10, 3, 4);
    CHECK(r == 7);
    CHECK(pt10.x == 3);
    CHECK(pt10.y == 4);
  }

  // ==========================================================================
  SECTION("Same type, many traits (IntWrapper has 6 trait impls)");
  // ==========================================================================
  {
    IntWrapper iw7 = { .val = 42 };

    // All 6 traits on the same instance
    DynStringify    s  = to_trait(IntWrapper, Stringify, &iw7);
    DynDescribable  d  = to_trait(IntWrapper, Describable, &iw7);
    DynArithmetic   a  = to_trait(IntWrapper, Arithmetic, &iw7);
    DynResettable   rs = to_trait(IntWrapper, Resettable, &iw7);
    DynContainer_int ci = to_trait(IntWrapper, Container_int, &iw7);
    DynMapper       mp = to_trait(IntWrapper, Mapper, &iw7);

    CHECK(strcmp(call(Stringify.stringify, &s), "IntWrapper") == 0);
    CHECK(strcmp(call(Describable.name, &d), "IntWrapper") == 0);
    CHECK(call(Arithmetic.value, &a) == 42);
    CHECK(call(Container_int.peek, &ci) == 42);

    call(Arithmetic.add, &a, 8);
    CHECK(call(Arithmetic.value, &a) == 50);
    CHECK(call(Container_int.peek, &ci) == 50);  // same underlying object

    call(Resettable.zero_out, &rs);
    CHECK(iw7.val == 0);
    CHECK(call(Arithmetic.value, &a) == 0);
    CHECK(call(Container_int.peek, &ci) == 0);

    CHECK(call(Mapper.map_val, &mp, 1, 2) == 3);  // 0+1+2
  }

  // ==========================================================================
  SECTION("Same trait, many types (Stringify has 5 impls)");
  // ==========================================================================
  {
    IntWrapper    iw8 = { .val = 0 };
    DoubleWrapper dw4 = { .val = 0 };
    Point         pt11 = { .label = "multi", .x = 0, .y = 0 };
    Rect          r7 = { .label = "multi_rect", .width = 0, .height = 0 };
    StrBuf        sb3 = { .buf = "multi_str", .len = 9 };

    DynStringify arr[5];
    arr[0] = to_trait(IntWrapper, Stringify, &iw8);
    arr[1] = to_trait(DoubleWrapper, Stringify, &dw4);
    arr[2] = to_trait(Point, Stringify, &pt11);
    arr[3] = to_trait(Rect, Stringify, &r7);
    arr[4] = to_trait(StrBuf, Stringify, &sb3);

    const char *expected[] = { "IntWrapper", "DoubleWrapper", "multi", "multi_rect", "multi_str" };
    for (int i = 0; i < 5; i++) {
      CHECK(strcmp(call(Stringify.stringify, &arr[i]), expected[i]) == 0);
    }
  }

  // ==========================================================================
  SECTION("Mutation through trait objects is reflected in concrete type");
  // ==========================================================================
  {
    Point pt12 = { .label = "mut", .x = 0, .y = 0 };

    // Mutate via Arithmetic trait
    DynArithmetic a = to_trait(Point, Arithmetic, &pt12);
    call(Arithmetic.add, &a, 100);
    CHECK(pt12.x == 100);

    // Mutate via Transform trait
    DynTransform t = to_trait(Point, Transform, &pt12);
    call(Transform.apply, &t, -50, 25);
    CHECK(pt12.x == 50);
    CHECK(pt12.y == 25);

    // Reset via Resettable
    DynResettable r = to_trait(Point, Resettable, &pt12);
    call(Resettable.zero_out, &r);
    CHECK(pt12.x == 0);
    CHECK(pt12.y == 0);
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
