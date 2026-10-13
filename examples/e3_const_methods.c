// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Reader -----------------------------------------------------------
// `immutable(Self)` marks a method as const (takes `const void *`).
// `required` = must be implemented; `default` = has a fallback.
// `def` derives the self parameter's constness from this declaration.
#define ReaderSignature(Self)               \
  dynamic(Self)                         \
  required(immutable(Self), int,  read)  \
  defaults(immutable(Self), void, describe)
#define Trait Reader
#include "../trait.h"

#define For Default
#define Impl Reader
  void def(describe) {
    printf("(default) value = %d\n", $(Reader.read, self));
  }
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int *ptr; } IntBox;


// ---- impl: Reader for IntBox -------------------------------------------------
#define For IntBox
#define Impl Reader
  int def(read) { return *self->ptr; }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
int main(void) {
  IntBox ib = { .ptr = &(int){42} };
  DynReader r = dyn(Reader, &ib);

  printf("=== const methods: Reader ===\n");
  printf("read: %d\n", $(Reader.read, &r));
  $(Reader.describe, &r);

  return 0;
}
