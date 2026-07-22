// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Animal -----------------------------------------------------------
#define AnimalSignature(Self)                    \
  require(Self, int,  get_snacks)            \
  default(immutable(Self), void, check)      \
  default(Self, void, eat_snack)             \
  default(Self, void, feed, int)
#define Dynamic
#define Trait Animal
#include "../trait.h"

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


// ---- trait: Pet (extends Animal) ---------------------------------------------
// extends is purely declarative: Pet requires Animal, but has its own methods.
#define PetSignature(Self) \
  extends(Animal, Self) \
  require(Self, void, play)
#define Dynamic
#define Trait Pet
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int snacks; } BaseAnimal;
typedef struct { BaseAnimal animal; const char *breed; } Dog;


// ---- impl: Animal for Dog ----------------------------------------------------
#define For Dog
#define Impl Animal
  def(int, get_snacks) { return self->animal.snacks; }
  def(void, feed, int amount) { self->animal.snacks += amount; }
#define Override_Dog_Animal_feed 1
#include "../trait.h"

// ---- impl: Pet for Dog -------------------------------------------------------
// Only `play` — Pet's own method. No inherited methods.
#define For Dog
#define Impl Pet
  def(void, play) {
    (void)self;
    printf("Dog plays fetch!\n");
  }
#include "../trait.h"


// ==== Multi-extension tests ===================================================

// ---- trait: Greetable (standalone) --------------------------------------------
#define GreetableSignature(Self) \
  require(immutable(Self), void, greet)
#define Dynamic
#define Trait Greetable
#include "../trait.h"

#define For Default
#define Impl Greetable
#include "../trait.h"


// ---- trait: Describable (standalone) ------------------------------------------
#define DescribableSignature(Self) \
  require(immutable(Self), void, describe) \
  default(immutable(Self), int, priority)
#define Dynamic
#define Trait Describable
#include "../trait.h"

#define For Default
#define Impl Describable
  constdef(int, priority) {
    (void)self;
    return 0;
  }
#include "../trait.h"


// ---- SuperPet: extends Pet ---------------------------------------------------
// Purely declarative: SuperPet requires Pet, has its own method.
#define SuperPetSignature(Self) \
  extends(Pet, Self) \
  require(Self, void, super_play)
#define Dynamic
#define Trait SuperPet
#include "../trait.h"


// ---- Introducible: multi-base extends ----------------------------------------
// Purely declarative: requires both Greetable and Describable.
#define IntroducibleSignature(Self) \
  extends(Greetable, Self) \
  extends(Describable, Self) \
  require(immutable(Self), void, introduce, const char *)
#define Dynamic
#define Trait Introducible
#include "../trait.h"


// ---- type definitions for multi-extension ------------------------------------
typedef struct { BaseAnimal animal; const char *breed; } Puppy;
typedef struct { const char *name; int age; } Person;


// ---- impl: Animal for Puppy --------------------------------------------------
#define For Puppy
#define Impl Animal
  def(int, get_snacks) { return self->animal.snacks; }
  def(void, feed, int amount) { self->animal.snacks += amount; }
#define Override_Puppy_Animal_feed 1
#include "../trait.h"

// ---- impl: Pet for Puppy -----------------------------------------------------
#define For Puppy
#define Impl Pet
  def(void, play) {
    (void)self;
    printf("Puppy plays with ball!\n");
  }
#include "../trait.h"

// ---- impl: SuperPet for Puppy ------------------------------------------------
#define For Puppy
#define Impl SuperPet
  def(void, super_play) {
    (void)self;
    printf("Puppy does a backflip!\n");
  }
#include "../trait.h"


// ---- impl: Greetable for Person ----------------------------------------------
#define For Person
#define Impl Greetable
  constdef(void, greet) {
    printf("Hi, I'm %s.\n", self->name);
  }
#include "../trait.h"

// ---- impl: Describable for Person --------------------------------------------
#define For Person
#define Impl Describable
  constdef(void, describe) {
    printf("%s, age %d.\n", self->name, self->age);
  }
#include "../trait.h"

// ---- impl: Introducible for Person -------------------------------------------
// Only introduce — cross-trait calls via SD dispatch on concrete type.
#define For Person
#define Impl Introducible
  constdef(void, introduce, const char *to) {
    printf("%s introduces self to %s: ", self->name, to);
    call(Greetable.greet, self);
    printf("About me: ");
    call(Describable.describe, self);
  }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
static int tests = 0, passed = 0;
#define TEST(cond, msg) do { tests++; if (cond) { passed++; } \
  else { printf("  FAIL: %s\n", msg); } } while(0)

int main(void) {
  Dog d = { .animal = { .snacks = 2 }, .breed = "Golden Retriever" };
  Puppy pw = { .animal = { .snacks = 3 }, .breed = "Beagle" };
  Person p = { .name = "Alice", .age = 30 };

  // --- Basic Animal (standalone) ---
  printf("=== Animal (standalone) ===\n");
  DynAnimal da = to_trait(Dog, Animal, &d);
  TEST(call(Animal.get_snacks, &da) == 2, "get_snacks == 2");
  call(Animal.feed, &da, 2);
  TEST(call(Animal.get_snacks, &da) == 4, "get_snacks == 4 after feed(2)");
  call(Animal.check, &da);        // default
  call(Animal.eat_snack, &da);    // default: get_snacks > 0, feed(-1)

  // --- Pet (new method, no inheritance) ---
  printf("\n=== Pet (own method only) ===\n");
  DynPet dp = to_trait(Dog, Pet, &d);
  call(Pet.play, &dp);            // "Dog plays fetch!"
  TEST(1, "Pet.play works");

  // --- Chain: Animal → Pet → SuperPet ---
  printf("\n=== Chain: Animal → Pet → SuperPet ===\n");
  DynAnimal pa = to_trait(Puppy, Animal, &pw);
  TEST(call(Animal.get_snacks, &pa) == 3, "Puppy get_snacks == 3");

  DynPet pp = to_trait(Puppy, Pet, &pw);
  call(Pet.play, &pp);            // "Puppy plays with ball!"
  TEST(1, "Pet.play works");

  DynSuperPet sp = to_trait(Puppy, SuperPet, &pw);
  call(SuperPet.super_play, &sp); // "Puppy does a backflip!"
  TEST(1, "SuperPet.super_play works");

  // Static dispatch via call() on concrete type (no vtable)
  int ss = call(Animal.get_snacks, &pw);
  TEST(ss == 3, "call(Animal.get_snacks) on Puppy");

  // --- Multi-base: Greetable + Describable → Introducible ---
  printf("\n=== Multi-base: Greetable + Describable → Introducible ===\n");
  DynGreetable dg = to_trait(Person, Greetable, &p);
  call(Greetable.greet, &dg);     // "Hi, I'm Alice."
  TEST(1, "Greetable.greet works");

  DynDescribable dd = to_trait(Person, Describable, &p);
  call(Describable.describe, &dd); // "Alice, age 30."
  TEST(1, "Describable.describe works");
  TEST(call(Describable.priority, &dd) == 0, "Describable.priority == 0");

  DynIntroducible di = to_trait(Person, Introducible, &p);
  call(Introducible.introduce, &di, "Bob"); // introduces + cross-trait calls
  TEST(1, "Introducible.introduce works");

  // Static dispatch for cross-trait methods via call()
  call(Greetable.greet, &p);
  call(Describable.describe, &p);
  TEST(1, "call(Greetable.greet, Describable.describe) static dispatch");

  printf("\n=== Results: %d/%d tests passed ===\n", passed, tests);
  return tests == passed ? 0 : 1;
}
