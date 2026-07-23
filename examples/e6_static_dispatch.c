// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Animal -----------------------------------------------------------
#define AnimalSignature(Self)                    \
  require(Self, int,  get_snacks)            \
  default(immutable(Self), void, check)      \
  default(Self, void, feed, int)
#define Dynamic
#define Trait Animal
#include "../trait.h"

// ---- default implementations for Animal ------------------------------------
#define For Default
#define Impl Animal
  void constdef(check) {
    (void)self;
    printf("(default) generic animal.\n");
  }
  void def(feed, int amount) {
    (void)self;
    printf("(default) fed %d.\n", amount);
  }
#include "../trait.h"

// ---- types ------------------------------------------------------------------
typedef struct { int snacks; } Cat;
typedef struct { int snacks; const char *breed; } Dog;

// ---- impl: Animal for Cat ---------------------------------------------------
#define For Cat
#define Impl Animal
  int def(get_snacks) { return self->snacks; }
  void def(feed, int amount) { self->snacks += amount; }
#define Override_Cat_Animal_feed 1
#include "../trait.h"

// ---- impl: Animal for Dog ---------------------------------------------------
#define For Dog
#define Impl Animal
  int def(get_snacks) { return self->snacks; }
  void def(feed, int amount) { self->snacks += amount; }
#define Override_Dog_Animal_feed 1
#include "../trait.h"

// ---- main: static dispatch tests -------------------------------------------
int main(void) {
  Cat c = { .snacks = 3 };
  Dog d = { .snacks = 5, .breed = "Labrador" };

  printf("=== call: static dispatch (no vtable) ===\n");

  // call resolves at compile time to Cat_Animal_get_snacks / Dog_Animal_get_snacks
  printf("Cat snacks: %d\n", call(Animal.get_snacks, &c));
  printf("Dog snacks: %d\n", call(Animal.get_snacks, &d));

  // call resolves to Cat_Animal_feed / Dog_Animal_feed
  call(Animal.feed, &c, 2);
  call(Animal.feed, &d, 3);
  printf("Cat snacks after feed: %d\n", call(Animal.get_snacks, &c));
  printf("Dog snacks after feed: %d\n", call(Animal.get_snacks, &d));

  // call with default method (check is immutable/const)
  call(Animal.check, &c);
  call(Animal.check, &d);

  // Dynamic dispatch still works alongside static dispatch
  printf("\n=== call: dynamic dispatch (for comparison) ===\n");
  DynAnimal ac = to_trait(Cat, Animal, &c);
  DynAnimal ad = to_trait(Dog, Animal, &d);
  printf("Cat snacks (vcall): %d\n", call(Animal.get_snacks, &ac));
  printf("Dog snacks (vcall): %d\n", call(Animal.get_snacks, &ad));

  return 0;
}
