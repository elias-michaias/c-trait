// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Container (parametric) -------------------------------------------
// T acts as a type parameter; macro arity handles passing it cleanly.
// Each instantiation (Container_int, Container_str) is a separate trait.
#define ContainerSignature(Self, T) \
  dynamic(Self) \
  required(Self, T, get)         \
  required(Self, void, set, T)

#define Container_intSignature(Self) ContainerSignature(Self, int)
#define Container_strSignature(Self) ContainerSignature(Self, const char *)
#define Trait Container_int
#include "../trait.h"
#define Trait Container_str
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int *ptr; } IntBox;
typedef struct { const char *text; } StrBox;


// ---- impl: Container_int for IntBox ------------------------------------------
#define For IntBox
#define Impl Container_int
  int def(get) { return *self->ptr; }
  void def(set, int val) { *self->ptr = val; }
#include "../trait.h"

// ---- impl: Container_str for StrBox ------------------------------------------
#define For StrBox
#define Impl Container_str
  const char * def(get) { return self->text; }
  void def(set, const char *val) { self->text = val; }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
int main(void) {
  int x = 10;
  IntBox ib = { .ptr = &x };
  StrBox sb = { .text = "hello" };

  printf("=== parametric traits: Container ===\n");
  DynContainer_int ci = dyn(Container_int, &ib);
  printf("IntBox get: %d\n", $(Container_int.get, &ci));
  $(Container_int.set, &ci, 99);
  printf("IntBox get after set: %d\n", $(Container_int.get, &ci));

  DynContainer_str cs = dyn(Container_str, &sb);
  printf("StrBox get: %s\n", $(Container_str.get, &cs));
  $(Container_str.set, &cs, "world");
  printf("StrBox get after set: %s\n", $(Container_str.get, &cs));

  return 0;
}
