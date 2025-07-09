#include "../trait.h"

// Define trait with a method
#define Trait_Testable(X) \
    method(X, void, test_method) \
    method(X, int, get_value, int)

define_type_from_trait(Testable, Trait_Testable)

// Test struct
struct TestStruct {
    int id;
    use(Trait_Testable)
};

// Implementation with ALL methods (should compile successfully)
#define STRUCT_IMPL TestStruct
impl {
    def(test_method, {
        printf("Testing...\n");
    });
    // TestStruct.get_value is UNDEFINED which should cause a validation error
}
// This automatically validates that all methods are implemented and creates the trait bridge
impl_traits(Testable)
#undef STRUCT_IMPL


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
