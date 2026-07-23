// clang-format off
// e9_forward_declare.c — test forward_declare: call() inside def() bodies
//
// The forward_declare mechanism pre-emits SD entries before def() bodies,
// so call(Trait.method, &self) works inside impl blocks.
#include "../trait.h"
#include <stdio.h>
#include <assert.h>

// ---- trait: Animal -----------------------------------------------------------
#define Dynamic
#define Trait Animal
#define AnimalSignature(Self)                    \
  require(Self, int,  get_snacks)            \
  require(Self, void, feed, int)
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int snacks; } Dog;

// ---- impl: Animal for Dog (using forward_declare) ----------------------------
// The forward_declare path emits extern decls + SD entries, so call() works
// inside the def() bodies below.
#define For Dog
#define Impl Animal
#define Forward
#include "../trait.h"
  int def(get_snacks) {
    return self->snacks;
  }
  void def(feed, int amount) {
    // call() inside def(): dispatches to Dog_Animal_get_snacks via SD entry
    int before = call(Animal.get_snacks, self);
    self->snacks += amount;
    int after = call(Animal.get_snacks, self);
    printf("Dog: fed %d, snacks %d -> %d\n", amount, before, after);
  }
#include "../trait.h"

// ---- main --------------------------------------------------------------------
int main(void) {
  Dog d = { .snacks = 5 };

  printf("=== forward_declare: call() inside def() bodies ===\n");
  call(Animal.feed, &d, 3);
  assert(d.snacks == 8);

  // Also verify call() from outside still works
  int s = call(Animal.get_snacks, &d);
  assert(s == 8);
  printf("get_snacks: %d\n", s);

  // Verify DynAnimal dispatch works too
  DynAnimal da = to_trait(Dog, Animal, &d);
  call(Animal.feed, &da, 2);
  assert(d.snacks == 10);

  printf("ALL PASS\n");
  return 0;
}
