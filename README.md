# Trait Composition/Conformance + Ad-Hoc Polymorphism in C

This project implements a robust, ergonomic trait (a.k.a. protocol/typeclass) system for C, inspired by Rust traits and Swift protocols, using a closure/block-based approach. It enables ad-hoc polymorphism, dynamic dispatch, and compile-time validation of trait conformance. It depends on [blocks](https://en.wikipedia.org/wiki/Blocks_(C_language_extension)), which come out of the box for `clang`.

## How It Works

- **Traits** are defined as sets of required methods using macros and the naming convention `Trait_...` (see `Trait_Testable` in `examples/complete_test.c`).
- **Structs** use traits by embedding the trait's method fields (function pointers/blocks) via a macro.
- **Implementations** are provided using the `impl()` and `def()` macros, which generate per-instance closures/blocks for each method.
- **Trait objects** (e.g., `Testable*`) can be created from any conforming struct, enabling dynamic dispatch.
- **Compile-time validation**: The system generates validation functions for each method, so missing implementations cause a compile-time error when you call `struct_impl_trait_type()`.
- **No inheritance**: only ad-hoc polymorphism and subtyping via trait composition.
- **No default implementations**: all logic is immediately visible in every struct's `impl()` block.

## Example

See `examples/complete_test.c`:

```c
#define Trait_Testable(X) \
    method(X, void, test_method) \
    method(X, int, get_value, int)

define_type_from_trait(Testable, Trait_Testable)

struct TestStruct {
    int id;
    use(Trait_Testable)
};

impl(TestStruct) {
    def(test_method, {
        printf("Testing...\n");
    });
    def(get_value, (int input) {
        return input * 2;
    });
}

struct_impl_trait_type(TestStruct, Testable)

int main() {
    struct TestStruct* test = TestStruct_new();
    Testable* t = Testable_from_TestStruct(test);
    t->test_method();
    TestStruct_destroy(test);
}
```

## Pros & Cons 

### Pros
- **Ergonomic 'method' syntax**: `obj->method()` and `trait_obj->method()` both work.
- **`self` is in scope of methods by default**: No need to manually pass and handle the struct instance in methods.
- **Dynamic dispatch**: Trait objects enable runtime polymorphism.
- **Reassignable implementations**: Methods can be re-bound at runtime (per instance).
- **Compile-time safety**: Missing method implementations are caught at compile time.
- **No inheritance required**: Works with plain C structs.
- **Doesn't work in MSVC**: Now you have an excuse to switch off.

### Cons
- **Requires Clang (blocks runtime)**: Relies on Clang's block/closure extensions (not portable to all compilers).
- **Per-instance method storage**: Each instance stores its own function pointers/blocks (slightly higher memory usage).
- **Traits with identical method signatures conflict**: If two traits have methods with the same name and signature, you must restructure your code (e.g., use unique method names or wrapper traits).
- **No true vtable sharing**: Each instance has its own set of function pointers, not a shared vtable.

## Limitations & Future Improvements

- **Trait field conflicts**: If two traits have methods with the same name and signature, the generated struct fields will conflict. This forces you to restructure your traits or use wrapper types. A future improvement could namespace trait fields or use a more advanced macro system.
- **Clang-only**: The system depends on Clang's block/closure support. Portability to GCC or MSVC would require a different approach (e.g., hand-written function pointers or trampolines). All other alternative solutions I have explored so far run into memory-safety issues or boiler-plate that reduces composability and reusability.

## Safety Nets

- The `def()` macro generates validation functions for each method.
- When you call `struct_impl_trait_type()`, the compiler checks that all required methods are implemented. If any are missing, you get a compile-time error.

## Directory Structure

- `trait.h` — The trait system header (core macros and logic)
- `examples/` — Example usage and tests

## Building & Running

```sh
cd examples
clang -o complete_test complete_test.c -Wall -Wextra
./complete_test
```

## License
MIT
