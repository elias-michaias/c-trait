// clang-format off
#include "../trait.h"
#include <stdio.h>

// ---- trait: Reader -----------------------------------------------------------
#define ReaderSignature(Self)               \
  dynamic(Self)                         \
  required(immutable(Self), int,  read)  \
  defaults(immutable(Self), void, describe)
#define Trait Reader
#include "../trait.h"

#define For Default
#define Impl Reader
  void constdef(describe) {
    printf("(default) value = %d\n", $(Reader.read, self));
  }
#include "../trait.h"


// ---- trait: LoggedReader (extends Reader) ------------------------------------
// Purely declarative: LoggedReader requires Reader, adds its own methods.
#define LoggedReaderSignature(Self) \
  dynamic(Self) \
  extends(Reader, Self)         \
  required(immutable(Self), int,  count) \
  defaults(immutable(Self), void, summary)
#define Trait LoggedReader
#include "../trait.h"

#define For Default
#define Impl LoggedReader
  void def(summary) {
    printf("(default) summary: ");
    printf("accessed %d time(s)\n", $(LoggedReader.count, self));
  }
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct { int *ptr; } IntBox;


// ---- impl: Reader for IntBox -------------------------------------------------
static int _IntBox_read_count;

#define For IntBox
#define Impl Reader
  int constdef(read) { ++_IntBox_read_count; return *self->ptr; }
#include "../trait.h"

// ---- impl: LoggedReader for IntBox -------------------------------------------
// Only count — LoggedReader's own method. No inherited methods.
#define For IntBox
#define Impl LoggedReader
  int constdef(count) { (void)self; return _IntBox_read_count; }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
int main(void) {
  IntBox ib = { .ptr = &(int){42} };

  printf("=== const extends: LoggedReader extends Reader ===\n");

  // Reader: own methods
  DynReader r = dyn(Reader, &ib);
  printf("read: %d\n", $(Reader.read, &r));
  $(Reader.describe, &r);

  // LoggedReader: own methods (uses Reader internally via SD dispatch)
  DynLoggedReader lr = dyn(LoggedReader, &ib);
  printf("count: %d\n", $(LoggedReader.count, &lr));
  $(LoggedReader.summary, &lr);

  return 0;
}
