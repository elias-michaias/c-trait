// clang-format off
// Test: def() derives the self parameter's constness from the trait signature
// (immutable(Self) -> const self).
//
// Covers:
//   - dynamic + static traits
//   - required and default methods
//   - a default override
//   - a default body (For == Default) that is itself immutable
//   - mixed mutability within a single impl block, all written with def()
#include "../trait.h"
#include <stdio.h>
#include <string.h>

static int failures;

#define CHECK(cond)                                                            \
  do {                                                                         \
    if (!(cond)) {                                                             \
      printf("  FAIL: %s\n", #cond);                                           \
      failures++;                                                              \
    }                                                                          \
  } while (0)

// ---- dynamic trait: Counter -------------------------------------------------
#define CounterSignature(Self)               \
  dynamic(Self)                               \
  required(immutable(Self), int,  value)      \
  required(Self, void, incr)                  \
  defaults(immutable(Self), int,  doubled)
#define Trait Counter
#include "../trait.h"

// Default immutable body written with plain def()
#define For Default
#define Impl Counter
  int def(doubled) {
    return $(Counter.value, self) * 2;
  }
#include "../trait.h"

// ---- static trait: Named ----------------------------------------------------
#define NamedSignature(Self)                    \
  required(immutable(Self), const char *, name) \
  required(Self, void, rename, const char *)
#define Trait Named
#include "../trait.h"

// ---- static trait with an immutable default: Scaled -------------------------
#define ScaledSignature(Self)                \
  required(immutable(Self), int, base)       \
  defaults(immutable(Self), int, scaled)
#define Trait Scaled
#include "../trait.h"

#define For Default
#define Impl Scaled
  int def(scaled) { (void)self; return 100; }
#include "../trait.h"

// ---- impl: Counter for Cell (overrides doubled) -----------------------------
typedef struct { int n; } Cell;

#define For Cell
#define Impl Counter
  int  def(value) { return self->n; }
  void def(incr)  { self->n += 1; }
  #define Override_Cell_Counter_doubled 1
  int  def(doubled) { return self->n * 3; }
#include "../trait.h"

// ---- impl: Counter for Box (uses the default doubled) -----------------------
typedef struct { int n; } Box;

#define For Box
#define Impl Counter
  int  def(value) { return self->n; }
  void def(incr)  { self->n += 2; }
#include "../trait.h"

// ---- static impl: Named for Tagged ------------------------------------------
typedef struct { const char *label; } Tagged;

#define For Tagged
#define Impl Named
  const char *def(name) { return self->label; }
  void def(rename, const char *new_name) { self->label = new_name; }
#include "../trait.h"

// ---- static impl: Scaled for Sample (uses default scaled) -------------------
typedef struct { int b; } Sample;

#define For Sample
#define Impl Scaled
  int def(base) { return self->b; }
#include "../trait.h"

int main(void) {
  printf("=== const-derived def ===\n");

  Cell c = { .n = 5 };
  DynCounter dc = dyn(Counter, &c);
  CHECK($(Counter.value, &dc) == 5);      // immutable, const Cell *self
  $(Counter.incr, &dc);                    // mutable, Cell *self
  CHECK($(Counter.value, &dc) == 6);
  CHECK($(Counter.doubled, &dc) == 18);    // overridden

  Box b = { .n = 4 };
  DynCounter db = dyn(Counter, &b);
  $(Counter.incr, &db);
  CHECK($(Counter.value, &db) == 6);
  CHECK($(Counter.doubled, &db) == 12);    // default body (immutable)

  Tagged t = { .label = "alpha" };
  CHECK(strcmp($(Named.name, &t), "alpha") == 0);   // static, immutable
  $(Named.rename, &t, "beta");                       // static, mutable
  CHECK(strcmp($(Named.name, &t), "beta") == 0);

  Sample s = { .b = 3 };
  CHECK($(Scaled.base, &s) == 3);          // static, immutable required
  CHECK($(Scaled.scaled, &s) == 100);      // static, immutable default via def

  if (failures) {
    printf("  %d check(s) FAILED\n", failures);
    return 1;
  }
  printf("  all checks passed\n");
  return 0;
}
