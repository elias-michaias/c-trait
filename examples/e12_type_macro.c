// clang-format off
// Test: #define For with a bespoke single-token type macro (vec(T) -> vec_##T)
// Verifies that For is fully expanded before being used, so that
// generic type macros that produce single-token results work as the For type.
#include "../trait.h"
#include <stdio.h>

// ---- bespoke type macro (single-token expansion) --------------------------------
#define vec(T) vec_##T

// ---- trait: Drawable ----------------------------------------------------------
#define Dynamic
#define Trait Drawable
#define DrawableSignature(Self) require(Self, void, draw)
#include "../trait.h"

// ---- struct vec_int (the expanded form of vec(int)) ---------------------------
typedef struct { int x, y; } vec_int;

// ---- impl: Drawable for vec(int) ----------------------------------------------
#define For vec(int)
#define Impl Drawable
  void def(draw) {
    printf("vec_int(%d, %d)\n", self->x, self->y);
  }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
int main(void) {
  vec_int v = { .x = 3, .y = 7 };
  DynDrawable dd = to_trait(vec(int), Drawable, &v);
  printf("=== type_macro: Drawable for vec(int) ===\n");
  call(Drawable.draw, &dd);
  return 0;
}
