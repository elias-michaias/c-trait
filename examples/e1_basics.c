// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Animal -----------------------------------------------------------
// Defines a trait with required methods (must be implemented) and default methods
// (automatically provided unless overridden).
#define Dynamic
#define Trait Animal
#define AnimalSignature(Self)                    \
  require(Self, int,  get_snacks)            \
  default(immutable(Self), void, check)      \
  default(Self, void, eat_snack)             \
  default(Self, void, feed, int)
#include "../trait.h"

// ---- default implementation for Animal ---------------------------------------
// When `For == Default`, these are the default method bodies.
#define For Default
#define Impl Animal
  constdef(void, check) {
    (void)self;
    printf("(default) generic animal.\n");
  }
  def(void, eat_snack) {
    if (call(Animal.get_snacks, self) > 0) call(Animal.feed, self, -1);
    else printf("(default) no snacks!\n");
  }
  def(void, feed, int amount) {
    (void)self;
    printf("(default) fed %d.\n", amount);
  }
#include "../trait.h"


// ---- trait: Show -------------------------------------------------------------
// A simple trait with one required method.
#define Dynamic
#define Trait Show
#define ShowSignature(Self) require(Self, void, show)
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int snacks; } BaseAnimal;
typedef struct { BaseAnimal animal; const char *breed; } Dog;


// ---- impl: Animal for Dog ----------------------------------------------------
#define For Dog
#define Impl Animal
  def(int, get_snacks) { return self->animal.snacks; }
  #define Override_Dog_Animal_feed 1
  def(void, feed, int amount) { self->animal.snacks += amount; }
#include "../trait.h"

// ---- impl: Show for Dog ------------------------------------------------------
#define For Dog
#define Impl Show
  def(void, show) {
    printf("Dog{breed=%s, snacks=%d}\n", self->breed, self->animal.snacks);
  }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
int main(void) {
  Dog d = { .animal = { .snacks = 2 }, .breed = "Golden Retriever" };
  DynAnimal da = to_trait(Dog, Animal, &d);

  printf("=== defaults: check/feed forwarded, get_snacks custom ===\n");
  call(Animal.check, &da);
  call(Animal.eat_snack, &da);
  printf("get_snacks: %d\n", call(Animal.get_snacks, &da));
  call(Animal.feed, &da, 5);
  printf("get_snacks: %d\n\n", call(Animal.get_snacks, &da));

  printf("=== Show trait (required method, vcall) ===\n");
  {
    DynShow s = to_trait(Dog, Show, &d);
    call(Show.show, &s);
  }

  return 0;
}
