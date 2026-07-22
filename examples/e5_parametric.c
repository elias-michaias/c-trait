// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Container (parametric) -------------------------------------------
// T acts as a type parameter; macro arity handles passing it cleanly.
// Each instantiation (Container_int, Container_str) is a separate trait.
#define ContainerSignature(Self, T) \
  require(Self, T, get)         \
  require(Self, void, set, T)

#define Container_intSignature(Self) ContainerSignature(Self, int)
#define Container_strSignature(Self) ContainerSignature(Self, const char *)
#define Dynamic
#define Trait Container_int
#include "../trait.h"
#define Dynamic
#define Trait Container_str
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int *ptr; } IntBox;
typedef struct { const char *text; } StrBox;


// ---- impl: Container_int for IntBox ------------------------------------------
#define For IntBox
#define Impl Container_int
  def(int, get) { return *self->ptr; }
  def(void, set, int val) { *self->ptr = val; }
#include "../trait.h"

// ---- impl: Container_str for StrBox ------------------------------------------
#define For StrBox
#define Impl Container_str
  def(const char *, get) { return self->text; }
  def(void, set, const char *val) { self->text = val; }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
int main(void) {
  int x = 10;
  IntBox ib = { .ptr = &x };
  StrBox sb = { .text = "hello" };

  printf("=== parametric traits: Container ===\n");
  DynContainer_int ci = to_trait(IntBox, Container_int, &ib);
  printf("IntBox get: %d\n", call(Container_int.get, &ci));
  call(Container_int.set, &ci, 99);
  printf("IntBox get after set: %d\n", call(Container_int.get, &ci));

  DynContainer_str cs = to_trait(StrBox, Container_str, &sb);
  printf("StrBox get: %s\n", call(Container_str.get, &cs));
  call(Container_str.set, &cs, "world");
  printf("StrBox get after set: %s\n", call(Container_str.get, &cs));

  return 0;
}
