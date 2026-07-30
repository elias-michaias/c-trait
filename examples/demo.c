// clang-format off
#include "../trait.h"
#include <stdio.h>

// ── Traits ───────────────────────────────────────────────────────────────

#define Trait Animal
#define Dynamic
#define AnimalSignature(Self)                    \
  required(Self, int,  get_snacks)            \
  defaults(Self, void, feed, int)             \
  defaults(Self, void, check)
#include "../trait.h"

#define Trait Pet
#define Dynamic
#define PetSignature(Self)                       \
  extends(Animal, Self)                      \
  required(Self, void, play)
#include "../trait.h"

#define Trait Show
#define Dynamic
#define ShowSignature(Self) required(Self, void, show)
#include "../trait.h"

// ── Defaults ─────────────────────────────────────────────────────────────

#define For Default
#define Dynamic
#define Impl Animal
  void def(check)     { (void)self; printf("generic animal\n"); }
  void def(feed, int n) { (void)self; printf("fed %d\n", n); }
#include "../trait.h"

// ── Types ────────────────────────────────────────────────────────────────

typedef struct { int snacks; } Base;
typedef struct { Base base; const char *breed; } Dog;

// ── Impls ────────────────────────────────────────────────────────────────

#define For Dog
#define Impl Animal
  int def(get_snacks) { return self->base.snacks; }
  void def(feed, int n) { self->base.snacks += n; }
#define Override_Dog_Animal_feed 1
#include "../trait.h"

#define For Dog
#define Impl Pet
  void def(play) { (void)self; printf("Dog plays fetch!\n"); }
#include "../trait.h"

#define For Dog
#define Impl Show
  void def(show) { printf("Dog(%s)\n", self->breed); }
#include "../trait.h"

// ── Use ──────────────────────────────────────────────────────────────────

int main(void) {
  Dog rex = { .base = { .snacks = 2 }, .breed = "Labrador" };

  DynAnimal a = dyn(Animal, &rex);
  call(Animal.check, &a);
  call(Animal.feed, &rex, 5);
  printf("snacks: %d\n\n", call(Animal.get_snacks, &a));

  DynPet p = dyn(Pet, &rex);
  // vcall macro = don't need to specify trait
  call(Pet.play, &p);

  DynShow s = dyn(Show, &rex);
  call(Show.show, &s);
}
