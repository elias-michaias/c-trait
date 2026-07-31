// clang-format off
#include "../trait.h"
#include <stdio.h>

// A trait extending 7 traits directly. Each base method dispatches through the
// embedded base vtable field via call():
//   DynDevice dd = dyn(Device, &r);
//   call(Sensor.read, &dd);   // dd.vt->Sensor.read(dd.self)
// One-hop replay (DMLIST) registers each direct base for the Dyn pair, so the
// full 7-base merge works with the selector-based call() API.

// ---- trait: Sensor -----------------------------------------------------------
#define SensorSignature(Self) \
  required(Self, int, read)
#define Dynamic
#define Trait Sensor
#include "../trait.h"

#define For Default
#define Impl Sensor
#include "../trait.h"


// ---- trait: Display ----------------------------------------------------------
#define DisplaySignature(Self) \
  required(Self, void, render)
#define Dynamic
#define Trait Display
#include "../trait.h"

#define For Default
#define Impl Display
#include "../trait.h"


// ---- trait: Speaker ----------------------------------------------------------
#define SpeakerSignature(Self) \
  required(Self, void, beep)
#define Dynamic
#define Trait Speaker
#include "../trait.h"

#define For Default
#define Impl Speaker
#include "../trait.h"


// ---- trait: Led --------------------------------------------------------------
#define LedSignature(Self) \
  required(Self, void, blink)
#define Dynamic
#define Trait Led
#include "../trait.h"

#define For Default
#define Impl Led
#include "../trait.h"


// ---- trait: Button -----------------------------------------------------------
#define ButtonSignature(Self) \
  required(Self, void, press)
#define Dynamic
#define Trait Button
#include "../trait.h"

#define For Default
#define Impl Button
#include "../trait.h"


// ---- trait: Timer (default method) --------------------------------------------
#define TimerSignature(Self) \
  defaults(Self, void, tick)
#define Dynamic
#define Trait Timer
#include "../trait.h"

#define For Default
#define Impl Timer
  void def(tick) {
    (void)self;
    printf("(default) tick.\n");
  }
#include "../trait.h"


// ---- trait: Comm --------------------------------------------------------------
#define CommSignature(Self) \
  required(Self, void, send)
#define Dynamic
#define Trait Comm
#include "../trait.h"

#define For Default
#define Impl Comm
#include "../trait.h"


// ---- trait: Device (extends all 7) -------------------------------------------
#define DeviceSignature(Self) \
  extends(Sensor, Self)   \
  extends(Display, Self)  \
  extends(Speaker, Self)  \
  extends(Led, Self)      \
  extends(Button, Self)   \
  extends(Timer, Self)    \
  extends(Comm, Self)     \
  required(Self, void, power_cycle)
#define Dynamic
#define Trait Device
#include "../trait.h"


// ---- type definitions --------------------------------------------------------
typedef struct {
  int reading;
  int beeps;
  int blinks;
  int presses;
  int ticks;
  int sent;
} Robot;


// ---- impl: base traits for Robot ---------------------------------------------
#define For Robot
#define Impl Sensor
  int def(read) { return self->reading; }
#include "../trait.h"

#define For Robot
#define Impl Display
  void def(render) {
    (void)self;
    printf("rendering.\n");
  }
#include "../trait.h"

#define For Robot
#define Impl Speaker
  void def(beep) {
    (void)self;
    self->beeps++;
    printf("beep!\n");
  }
#include "../trait.h"

#define For Robot
#define Impl Led
  void def(blink) {
    (void)self;
    self->blinks++;
  }
#include "../trait.h"

#define For Robot
#define Impl Button
  void def(press) {
    (void)self;
    self->presses++;
  }
#include "../trait.h"

#define For Robot
#define Impl Timer
#include "../trait.h"

#define For Robot
#define Impl Comm
  void def(send) {
    (void)self;
    self->sent++;
  }
#include "../trait.h"


// ---- impl: Device for Robot --------------------------------------------------
// Only power_cycle — the 7 base vtables are merged by composition.
#define For Robot
#define Impl Device
  void def(power_cycle) {
    printf("power cycle: ");
    call(Sensor.read, self);   // cross-trait static dispatch on the concrete type
    call(Speaker.beep, self);
  }
#include "../trait.h"


// ---- main --------------------------------------------------------------------
static int tests = 0, passed = 0;
#define TEST(cond, msg) do { tests++; if (cond) { passed++; } \
  else { printf("  FAIL: %s\n", msg); } } while(0)

int main(void) {
  Robot r = {
    .reading = 42, .beeps = 0, .blinks = 0, .presses = 0, .ticks = 0, .sent = 0,
  };

  printf("=== Device: 7 direct bases via call() ===\n");
  DynDevice dd = dyn(Device, &r);

  TEST(call(Sensor.read, &dd) == 42, "Sensor.read via DynDevice");
  call(Display.render, &dd);            // "rendering."
  TEST(1, "Display.render via DynDevice");
  call(Speaker.beep, &dd);              // "beep!"
  TEST(r.beeps == 1, "Speaker.beep via DynDevice");
  call(Led.blink, &dd);
  TEST(r.blinks == 1, "Led.blink via DynDevice");
  call(Button.press, &dd);
  TEST(r.presses == 1, "Button.press via DynDevice");
  call(Timer.tick, &dd);                // "(default) tick." (not overridden)
  TEST(1, "Timer.tick default via DynDevice");
  call(Comm.send, &dd);
  TEST(r.sent == 1, "Comm.send via DynDevice");
  call(Device.power_cycle, &dd);        // "power cycle: " + cross-trait calls
  TEST(r.beeps == 2, "Device.power_cycle own method via DynDevice");

  // Direct embedded-vtable access (equivalent, no selector dispatch)
  TEST(dd.vt->Sensor.read(dd.self) == 42, "direct: merged Sensor.read");
  dd.vt->Timer.tick(dd.self);
  dd.vt->power_cycle(dd.self);
  TEST(1, "direct: merged base + own methods");

  // Standalone use of one base trait is unaffected by the wide merge
  DynSensor ds = dyn(Sensor, &r);
  TEST(call(Sensor.read, &ds) == 42, "Sensor standalone via call()");

  printf("\n=== Results: %d/%d tests passed ===\n", passed, tests);
  return tests == passed ? 0 : 1;
}
