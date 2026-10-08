// clang-format off
#define TraitCustomDispatch
#define tcall trait_dispatch_call
#include "../trait.h"
#include <assert.h>

typedef struct { int value; } Meter;

#define Trait MeterOps
#define MeterOpsSignature(Self) \
  required(Self, int, get) \
  required(Self, void, add, int)
#include "../trait.h"

#define For Meter
#define Impl MeterOps
int def(get) { return self->value; }
void def(add, int amount) { self->value += amount; }
#include "../trait.h"

int main(void) {
  Meter m = { .value = 5 };
  assert(tcall(MeterOps.get, &m) == 5);
  tcall(MeterOps.add, &m, 3);
  assert(tcall(MeterOps.get, &m) == 8);
  return 0;
}
