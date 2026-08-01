// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Animal -----------------------------------------------------------
#define AnimalSignature(Self)                    \
  required(Self, int,  get_snacks)            \
  defaults(immutable(Self), void, check)      \
  defaults(Self, void, eat_snack)             \
  defaults(Self, void, feed, int)
#define Dynamic
#define Trait Animal
#include "../trait.h"

#define For Default
#define Impl Animal
  void constdef(check) {
    (void)self;
    printf("(default) generic animal.\n");
  }
  void def(eat_snack) {
    if (call(Animal.get_snacks, self) > 0) call(Animal.feed, self, -1);
    else printf("(default) no snacks!\n");
  }
  void def(feed, int amount) {
    (void)self;
    printf("(default) fed %d.\n", amount);
  }
#include "../trait.h"


// ---- trait: Pet (extends Animal) ---------------------------------------------
// extends merges the base vtable into Pet's vtable by composition:
//   typedef struct { Animal_vtable Animal; void (*play)(void *); } Pet_vtable;
// Base methods are dispatched through the embedded field via call():
//   DynPet dp = dyn(Pet, &dog);  call(Animal.get_snacks, &dp);
//   dp.vt->Animal.get_snacks(dp.self);  // equivalent direct access
#define PetSignature(Self) \
  extends(Animal, Self) \
  required(Self, void, play)
#define Dynamic
#define Trait Pet
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int snacks; } BaseAnimal;
typedef struct { BaseAnimal animal; const char *breed; } Dog;


// ---- impl: Animal for Dog ----------------------------------------------------
#define For Dog
#define Impl Animal
  int def(get_snacks) { return self->animal.snacks; }
  void def(feed, int amount) { self->animal.snacks += amount; }
#define Override_Dog_Animal_feed 1
#include "../trait.h"

// ---- impl: Pet for Dog -------------------------------------------------------
// Only `play` — Pet's own method. The Animal vtable is merged by composition.
#define For Dog
#define Impl Pet
  void def(play) {
    (void)self;
    printf("Dog plays fetch!\n");
  }
#include "../trait.h"


// ==== Multi-extension tests ===================================================

// ---- trait: Greetable (standalone) --------------------------------------------
#define GreetableSignature(Self) \
  required(immutable(Self), void, greet)
#define Dynamic
#define Trait Greetable
#include "../trait.h"

#define For Default
#define Impl Greetable
#include "../trait.h"


// ---- trait: Describable (standalone) ------------------------------------------
#define DescribableSignature(Self) \
  required(immutable(Self), void, describe) \
  defaults(immutable(Self), int, priority)
#define Dynamic
#define Trait Describable
#include "../trait.h"

#define For Default
#define Impl Describable
  int constdef(priority) {
    (void)self;
    return 0;
  }
#include "../trait.h"


// ---- SuperPet: extends Pet ---------------------------------------------------
// Transitive composition: SuperPet's vtable nests Pet's, which nests Animal's.
#define SuperPetSignature(Self) \
  extends(Pet, Self) \
  required(Self, void, super_play)
#define Dynamic
#define Trait SuperPet
#include "../trait.h"


// ---- Introducible: multi-base extends ----------------------------------------
// Multiple inheritance by composition: nests Greetable_vtable and
// Describable_vtable side by side.
#define IntroducibleSignature(Self) \
  extends(Greetable, Self) \
  extends(Describable, Self) \
  required(immutable(Self), void, introduce, const char *)
#define Dynamic
#define Trait Introducible
#include "../trait.h"


// ---- type definitions for multi-extension ------------------------------------
typedef struct { BaseAnimal animal; const char *breed; } Puppy;
typedef struct { const char *name; int age; } Person;


// ---- impl: Animal for Puppy --------------------------------------------------
#define For Puppy
#define Impl Animal
  int def(get_snacks) { return self->animal.snacks; }
  void def(feed, int amount) { self->animal.snacks += amount; }
#define Override_Puppy_Animal_feed 1
#include "../trait.h"

// ---- impl: Pet for Puppy -----------------------------------------------------
#define For Puppy
#define Impl Pet
  void def(play) {
    (void)self;
    printf("Puppy plays with ball!\n");
  }
#include "../trait.h"

// ---- impl: SuperPet for Puppy ------------------------------------------------
#define For Puppy
#define Impl SuperPet
  void def(super_play) {
    (void)self;
    printf("Puppy does a backflip!\n");
  }
#include "../trait.h"


// ---- impl: Greetable for Person ----------------------------------------------
#define For Person
#define Impl Greetable
  void constdef(greet) {
    printf("Hi, I'm %s.\n", self->name);
  }
#include "../trait.h"

// ---- impl: Describable for Person --------------------------------------------
#define For Person
#define Impl Describable
  void constdef(describe) {
    printf("%s, age %d.\n", self->name, self->age);
  }
#include "../trait.h"

// ---- impl: Introducible for Person -------------------------------------------
// Only introduce — cross-trait calls via SD dispatch on concrete type.
#define For Person
#define Impl Introducible
  void constdef(introduce, const char *to) {
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
  DynAnimal da = dyn(Animal, &d);
  TEST(call(Animal.get_snacks, &da) == 2, "get_snacks == 2");
  call(Animal.feed, &da, 2);
  TEST(call(Animal.get_snacks, &da) == 4, "get_snacks == 4 after feed(2)");
  call(Animal.check, &da);        // default
  call(Animal.eat_snack, &da);    // default: get_snacks > 0, feed(-1)

  // --- Pet (own method + merged base vtable) ---
  printf("\n=== Pet (own method + merged base vtable) ===\n");
  DynPet dp = dyn(Pet, &d);
  call(Pet.play, &dp);            // "Dog plays fetch!"
  TEST(1, "Pet.play works");
  TEST(call(Animal.get_snacks, &dp) == 3, "call(Animal.get_snacks) via DynPet");
  call(Animal.check, &dp);        // default via merged vtable
  TEST(1, "default Animal.check via call()");
  call(Animal.feed, &dp, 2);      // default with args via merged vtable
  TEST(call(Animal.get_snacks, &dp) == 5, "call(Animal.feed) default with args via DynPet");
  TEST(dp.vt->Animal.get_snacks(dp.self) == 5, "direct: merged vtable Animal.get_snacks");

  // --- Chain: Animal → Pet → SuperPet ---
  printf("\n=== Chain: Animal → Pet → SuperPet ===\n");
  DynAnimal pa = dyn(Animal, &pw);
  TEST(call(Animal.get_snacks, &pa) == 3, "Puppy get_snacks == 3");

  DynPet pp = dyn(Pet, &pw);
  call(Pet.play, &pp);            // "Puppy plays with ball!"
  TEST(1, "Pet.play works");

  DynSuperPet sp = dyn(SuperPet, &pw);
  call(SuperPet.super_play, &sp); // "Puppy does a backflip!"
  TEST(1, "SuperPet.super_play works");
  call(Pet.play, &sp);            // Pet's method via the embedded Pet vtable
  TEST(1, "call(Pet.play) via DynSuperPet");
  TEST(sp.vt->Pet.Animal.get_snacks(sp.self) == 3, "transitive merge: Animal.get_snacks via SuperPet");
  sp.vt->Pet.Animal.check(sp.self); // default via nested merge
  sp.vt->Pet.play(sp.self);         // direct access (call() path covered above)
  TEST(1, "transitive merge: nested base methods work");

  // Static dispatch via call() on concrete type (no vtable)
  int ss = call(Animal.get_snacks, &pw);
  TEST(ss == 3, "call(Animal.get_snacks) on Puppy");

  // --- Multi-base: Greetable + Describable → Introducible ---
  printf("\n=== Multi-base: Greetable + Describable → Introducible ===\n");
  DynGreetable dg = dyn(Greetable, &p);
  call(Greetable.greet, &dg);     // "Hi, I'm Alice."
  TEST(1, "Greetable.greet works");

  DynDescribable dd = dyn(Describable, &p);
  call(Describable.describe, &dd); // "Alice, age 30."
  TEST(1, "Describable.describe works");
  TEST(call(Describable.priority, &dd) == 0, "Describable.priority == 0");

  DynIntroducible di = dyn(Introducible, &p);
  call(Introducible.introduce, &di, "Bob"); // introduces + cross-trait calls
  TEST(1, "Introducible.introduce works");
  call(Greetable.greet, &di);             // "Hi, I'm Alice." via embedded vtable
  call(Describable.describe, &di);        // "Alice, age 30."
  TEST(call(Describable.priority, &di) == 0, "multi-base merge: default Describable.priority via call()");
  TEST(di.vt->Describable.priority(di.self) == 0, "multi-base merge: direct default access");
  TEST(1, "multi-base merge: nested base methods work");

  // Static dispatch for cross-trait methods via call()
  call(Greetable.greet, &p);
  call(Describable.describe, &p);
  TEST(1, "call(Greetable.greet, Describable.describe) static dispatch");

  printf("\n=== Results: %d/%d tests passed ===\n", passed, tests);
  return tests == passed ? 0 : 1;
}
