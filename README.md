# Traits + Methods + Ad-Hoc Polymorphism in C

This project implements a robust, ergonomic trait (a.k.a. protocol/typeclass) system for C, inspired by Rust traits and Swift protocols, using a closure/block-based approach. It enables ad-hoc polymorphism, dynamic dispatch, and compile-time validation of trait conformance. It depends on [blocks](https://en.wikipedia.org/wiki/Blocks_(C_language_extension)), which come out of the box for `clang`. When it comes to `gcc` or `msvc`, your mileage may vary.

## How It Works

- **Traits** are defined as sets of required fields and methods using macros and the naming convention `Trait_...`. 
- **Structs** use traits by embedding the trait's method fields (function pointers/blocks) via a macro.
- **Implementations** are provided using the `impl()` and `def()` macros, which generate per-instance closures/blocks for each method.
- **Trait objects** (e.g., `Testable*`) can be created from any conforming struct, enabling dynamic dispatch.
- **Compile-time validation**: The system generates validation functions for each method, so missing implementations cause a compile-time error when you call `impl_traits()`.
- **No inheritance**: only ad-hoc polymorphism and subtyping via trait composition.
- **No default implementations**: all logic is immediately visible in every struct's `impl()` block.

## Example

```c
// all traits start with `Trait_`
// define your traits as an X-macro of field() and method()
#define Trait_Testable(X) \
    field(X, int, is_special)
    method(X, void, test_method) \
    method(X, int, get_value, int)

// generates the struct for the trait
// generates constructor and destructor
define_type_from_trait(Testable, Trait_Testable)

struct TestStruct {
    int id;
    // expands the fields of a trait
    use(Trait_Testable)
};

// set an implementation block
#define STRUCT_IMPL TestStruct

// define the implementation of methods
impl {
    def(test_method, {
        printf("Testing...\n");
    });
    def(get_value, (int input) {
        return input * 2;
    });
}

// create TestStruct -> Testable conversion function
// create Testable -> TestStruct conversion function
// validate all Testable methods are implemented
impl_traits(Testable)

// end of implementation block
#undef STRUCT_IMPL

int main() {
    // use generated constructor
    struct TestStruct* test = TestStruct_new();

    // automatic conversion to trait type
    Testable* t = Testable_from_TestStruct(test);

    // all fields on Testable actually go back to TestStruct 
    t->test_method();
    TestStruct_destroy(test);
}
```

## Pros & Cons 

### Pros
- **True method calls**: `obj->method()` doesn't require passing `&obj`.
- **`self` is in scope of methods by default**: No need to manually pass and handle the struct instance in methods.
- **Dynamic dispatch**: Trait objects enable runtime polymorphism.
- **Reassignable implementations**: Methods can be re-bound at runtime (per instance).
- **Compile-time safety**: Missing method implementations are caught at compile time.
- **No inheritance**: Enforces composition.
- **Doesn't work in MSVC**: Now you have an excuse to switch off.

### Cons
- **Requires Clang (blocks runtime)**: Relies on Clang's block/closure extensions (not portable to all compilers).
- **Per-instance method storage**: Each instance stores its own blocks (slightly higher memory usage).
- **Traits with identical method signatures conflict**: If two traits have methods with the same name and signature, you must restructure your code (e.g., use unique method names or wrapper traits).
- **No true vtable sharing**: Each instance has its own set of function pointers, not a shared vtable.

## Limitations & Future Improvements

- **Trait field conflicts**: If two traits have methods with the same name and signature, the generated struct fields will conflict. This forces you to restructure your traits or use wrapper types. A future improvement could namespace trait fields or use a more advanced macro system, with helper macros like `exclude()` or `namespace()`.
- **Clang-only**: The system depends on Clang's block/closure support. Portability to GCC or MSVC would require a different approach (e.g., hand-written function pointers or trampolines). All other alternative solutions I have explored so far run into memory-safety issues or boiler-plate that reduces composability and reusability. I use Clang exclusively, so this was the kind of thing that I needed for myself. There are other good object systems for pure C that exist if you want to give them a look - they might suit you better.

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
