#include "trait.h"

// Define trait with methods
#define Trait_Testable(X) \
    method(X, void, test_method) \
    method(X, int, get_value, int)

define_type_from_trait(Testable, Trait_Testable)

// Test struct
struct TestStruct {
    int id;
    use(Trait_Testable)
};

// Complete implementation (should compile successfully)
impl(TestStruct) {
    def(test_method, {
        printf("Testing...\n");
    });
    def(get_value, (int input) {
        return input * 2;
    });
}

// This automatically validates that all methods are implemented
struct_impl_trait_type(TestStruct, Testable)

int main() {
    struct TestStruct* test = TestStruct_new();
    test->id = 1;
    
    // This should work
    Testable* t = Testable_from_TestStruct(test);
    t->test_method();
    
    TestStruct_destroy(test);
    return 0;
}
