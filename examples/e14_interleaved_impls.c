// clang-format off
#include "../trait.h"
#include <assert.h>
#include <stdio.h>

typedef struct { int value; } Box;
typedef struct { const char *name; } Person;

#define Trait Greet
#define GreetSignature(Self) \
  dynamic(Self) \
  required(Self, void, greet)
#include "../trait.h"

#define Trait Label
#define LabelSignature(Self) required(Self, int, label)
#include "../trait.h"

#define Trait Describe
#define DescribeSignature(Self) \
  required(Self, void, describe) \
  dynamic(Self)
#include "../trait.h"

// Interleave dynamic and static trait impls. The dynamic(Self) directives live
// in the trait signatures; no per-impl mode marker is needed.
#define For Box
#define Impl Greet
void def(greet) { printf("box:%d\n", self->value); }
#include "../trait.h"

#define For Box
#define Impl Label
int def(label) { return self->value; }
#include "../trait.h"

#define For Box
#define Impl Describe
void def(describe) { printf("description:%d\n", self->value); }
#include "../trait.h"

#define For Person
#define Impl Greet
void def(greet) { printf("person:%s\n", self->name); }
#include "../trait.h"

#define For Person
#define Impl Label
int def(label) { return (int)self->name[0]; }
#include "../trait.h"

#define For Person
#define Impl Describe
void def(describe) { printf("description:%s\n", self->name); }
#include "../trait.h"

int main(void) {
  Box box = {42};
  Person person = {"Ada"};
  assert($(Label.label, &box) == 42);
  assert($(Label.label, &person) == 'A');

  DynGreet box_greet = dyn(Greet, &box);
  DynGreet person_greet = dyn(Greet, &person);
  DynDescribe person_description = dyn(Describe, &person);
  $(Greet.greet, &box_greet);
  $(Greet.greet, &person_greet);
  $(Describe.describe, &person_description);
  return 0;
}
