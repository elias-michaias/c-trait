/*
 * e11_static_defaults.c — Static trait with default methods
 *
 * Tests:
 * 1. Static trait with require + default
 * 2. Default implementation (simple: returns constant)
 * 3. Type uses default (no override)
 * 4. Type overrides default via def()
 * 5. call() via SD dispatch for both types
 * 6. No vtable, no DynTrait (no dynamic dispatch)
 */
#include "../trait.h"
#include <assert.h>
#include <stdio.h>

// ---- trait: Drawable (static, require + default) ----------------------------
// require: draw() — each type must implement
// default: is_visible() — returns 1 (visible by default)
#define Trait Drawable
#define DrawableSignature(Self)                                                \
  require(Self, void, draw) default(Self, int, is_visible)
#include "../trait.h"

// ---- default implementation -------------------------------------------------
#define For Default
#define Impl Drawable
int def(is_visible) {
  (void)self;
  return 1; // visible by default
}
#include "../trait.h"

// ---- type definitions -------------------------------------------------------
typedef struct {
  const char *label;
} Widget;

typedef struct {
  const char *label;
  int hidden;
} HiddenWidget;

// ---- impl: Drawable for Widget (uses default is_visible) --------------------
#define For Widget
#define Impl Drawable
void def(draw) { printf("  Drawing widget: %s\n", self->label); }
// is_visible uses default (returns 1)
#include "../trait.h"

// ---- impl: Drawable for HiddenWidget (overrides is_visible) -----------------
#define For HiddenWidget
#define Impl Drawable
void def(draw) { printf("  Drawing widget: %s\n", self->label); }
#define Override_HiddenWidget_Drawable_is_visible 1
int def(is_visible) { return !self->hidden; }
#include "../trait.h"

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

  printf("=== Static defaults test ===\n\n");

  // -- Test 1: Widget uses default is_visible --
  printf("--- Test 1: Widget (default is_visible) ---\n");
  {
    Widget w = {"button"};
    call(Drawable.draw, &w);
    int vis = call(Drawable.is_visible, &w);
    TEST(vis == 1, "Widget.is_visible() == 1 (default)");
    printf("  Widget.is_visible() = %d\n", vis);
  }

  // -- Test 2: HiddenWidget overrides is_visible --
  printf("\n--- Test 2: HiddenWidget (overridden is_visible) ---\n");
  {
    HiddenWidget hw1 = {"panel", 0};
    HiddenWidget hw2 = {"secret", 1};

    call(Drawable.draw, &hw1);
    int vis1 = call(Drawable.is_visible, &hw1);
    TEST(vis1 == 1, "HiddenWidget(visible).is_visible() == 1");
    printf("  HiddenWidget(visible).is_visible() = %d\n", vis1);

    call(Drawable.draw, &hw2);
    int vis2 = call(Drawable.is_visible, &hw2);
    TEST(vis2 == 0, "HiddenWidget(hidden).is_visible() == 0");
    printf("  HiddenWidget(hidden).is_visible() = %d\n", vis2);
  }

  // -- Test 3: No vtable/DynTrait — compile-time proof --
  printf("\n--- Test 3: No vtable/DynTrait (compile-time) ---\n");
  printf("  OK (compiled without vtable/DynTrait)\n");

  // -- Test 4: Direct static function calls --
  printf("\n--- Test 4: Direct static function calls ---\n");
  {
    Widget w2 = {"label"};
    Widget_Drawable_draw(&w2);
    int vis = Widget_Drawable_is_visible(&w2);
    TEST(vis == 1, "Widget_Drawable_is_visible() == 1 (direct)");
    printf("  Widget_Drawable_is_visible() = %d (direct)\n", vis);

    HiddenWidget hw3 = {"secret2", 1};
    HiddenWidget_Drawable_draw(&hw3);
    int vis2 = HiddenWidget_Drawable_is_visible(&hw3);
    TEST(vis2 == 0, "HiddenWidget_Drawable_is_visible() == 0 (direct)");
    printf("  HiddenWidget_Drawable_is_visible() = %d (direct)\n", vis2);
  }

  printf("\n=== Results: %d/%d tests passed ===\n", passed, tests);
  if (pass)
    printf("ALL PASS\n");
  return pass ? 0 : 1;
}
