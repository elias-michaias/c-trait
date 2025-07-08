#include "../trait.h"
#include <stdio.h>

// Define two traits
#define Trait_A(X) \
    method(X, void, a_method)

#define Trait_B(X) \
    method(X, int, b_method, int)

define_type_from_trait(A, Trait_A)
define_type_from_trait(B, Trait_B)

// Struct 1
struct Foo {
    int value;
    use(Trait_A)
    use(Trait_B)
};

// Struct 2
struct Bar {
    int value;
    use(Trait_A)
    use(Trait_B)
};

// Implement Foo
#define STRUCT_IMPL Foo

impl {
    def(a_method, {
        printf("Foo::a_method (value=%d)\n", self->value);
    });
    def(b_method, (int x) {
        printf("Foo::b_method (x=%d, value=%d)\n", x, self->value);
        return self->value + x;
    });
}

struct_impl_trait_type(A)
struct_impl_trait_type(B)
#undef STRUCT_IMPL

// Implement Bar
#define STRUCT_IMPL Bar

impl {
    def(a_method, {
        printf("Bar::a_method (value=%d)\n", self->value);
    });
    def(b_method, (int x) {
        printf("Bar::b_method (x=%d, value=%d)\n", x, self->value);
        return self->value * x;
    });
}

struct_impl_trait_type(A)
struct_impl_trait_type(B)
#undef STRUCT_IMPL

int main() {
    struct Foo* foo = Foo_new();
    foo->value = 10;
    struct Bar* bar = Bar_new();
    bar->value = 7;

    // Ad-hoc polymorphism: use trait objects
    A* a1 = A_from_Foo(foo);
    A* a2 = A_from_Bar(bar);
    B* b1 = B_from_Foo(foo);
    B* b2 = B_from_Bar(bar);

    printf("Calling a_method via trait A* on Foo and Bar:\n");
    a1->a_method();
    a2->a_method();

    printf("\nCalling b_method via trait B* on Foo and Bar:\n");
    printf("Foo result: %d\n", b1->b_method(5));
    printf("Bar result: %d\n", b2->b_method(5));

    Foo_destroy(foo);
    Bar_destroy(bar);
    A_destroy(a1);
    A_destroy(a2);
    B_destroy(b1);
    B_destroy(b2);
    return 0;
}
