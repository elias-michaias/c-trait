#include "trait.h"

// Define trait with a method
#define Trait_Testable(X) \
    method(X, void, test_method) \
    method(X, int, get_value, int)

Declare_Trait_Type(Testable, Trait_Testable)

// Test struct
struct TestStruct {
    int id;
    use(Trait_Testable)
};

// Implementation with ALL methods (should compile successfully)
Impl(TestStruct) {
    def(test_method, {
        printf("Testing...\n");
    });
    def(get_value, int(int input) {
        printf("Getting value with input: %d\n", input);
        return input * 2;
    });
}

// This automatically validates that all methods are implemented and creates the trait bridge
Struct_Impl_Trait(TestStruct, Testable)

int main() {
    struct TestStruct* test = TestStruct_new();
    test->id = 1;
    
    // Test direct method calls
    printf("=== Direct Method Calls ===\n");
    test->test_method();
    int result = test->get_value(42);
    printf("Result: %d\n", result);
    
    // Test trait bridge
    printf("\n=== Trait Bridge ===\n");
    Testable* t = Testable_from_TestStruct(test);
    t->test_method();
    int trait_result = t->get_value(99);
    printf("Trait result: %d\n", trait_result);
    
    free(t);
    TestStruct_destroy(test);
    return 0;
}
