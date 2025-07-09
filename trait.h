#ifndef TRAIT_H
#define TRAIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Block.h>

// ==================== TRAIT SYSTEM: API MACROS ====================
//
// This header provides a trait/protocol/typeclass system for C using Clang blocks.
// Traits are defined as sets of required methods and/or fields, and structs can
// conform to traits by embedding the generated fields and providing implementations.
//
// - Traits support ad-hoc polymorphism and dynamic dispatch.
// - Compile-time validation ensures all required methods are implemented.
// - All macros are designed for clarity and IDE usability.
//
// See README.md for usage examples.

// --- TRAIT FIELD AND METHOD DECLARATION MACROS ---

// Declares a field in a trait or struct.
// Usage: field(X, type, name)
//   - X: macro to apply (usually internal)
//   - type: type of the field
//   - name: field name
#define field(X, type, name) X(type, name, field)

// Declares a method in a trait or struct.
// Usage: method(X, return_type, name, ...args)
//   - X: macro to apply (usually internal)
//   - return_type: return type of the method
//   - name: method name
//   - ...args: argument types (optional)
#define method(X, ret_type, name, ...) X(ret_type, name, method, ##__VA_ARGS__)

// --- TRAIT COMPOSITION MACROS ---

// Compose multiple traits into a single set of fields/methods.
// Usage: traits(X, TraitA, TraitB, ...)
//   - X: macro to apply
//   - TraitA, TraitB, ...: trait macros
#define traits(X, ...) \
    FOR_EACH_TRAIT(EXPAND_TRAIT, X, __VA_ARGS__)

#define EXPAND_TRAIT(X, trait_macro) trait_macro(X)

// Helper: Apply a macro to each argument in a variadic list.
#define FOR_EACH_TRAIT(macro, X, ...) \
    MAP_TRAITS(macro, X, __VA_ARGS__)

#define MAP_TRAITS(m, X, t, ...) \
    m(X, t) \
    __VA_OPT__(MAP_TRAITS_AGAIN PARENS (m, X, __VA_ARGS__))
#define MAP_TRAITS_AGAIN() MAP_TRAITS
#define PARENS ()

#define EXPAND(x) x
#define CONCAT(a, b) EXPAND(CONCAT_IMPL(a, b))
#define CONCAT_IMPL(a, b) a ## b
#define CONCAT3(a, b, c) EXPAND(CONCAT3_IMPL(a, b, c))
#define CONCAT3_IMPL(a, b, c) a ## b ## c
#define CONCAT4(a, b, c, d) EXPAND(CONCAT4_IMPL(a, b, c, d))
#define CONCAT4_IMPL(a, b, c, d) a ## b ## c ## d
#define CONCAT5(a, b, c, d, e) EXPAND(CONCAT5_IMPL(a, b, c, d, e))
#define CONCAT5_IMPL(a, b, c, d, e) a ## b ## c ## d ## e

// --- STRUCT IMPLEMENTATION MACROS ---

// Begins an implementation block for a struct.
// Usage: #define STRUCT_IMPL MyStruct ... impl { ... } ... #undef STRUCT_IMPL
#define impl \
    static void CONCAT3(STRUCT_IMPL, _init_methods, ) (struct STRUCT_IMPL *self); \
    static struct STRUCT_IMPL* CONCAT3(STRUCT_IMPL, _new, ) () { \
        struct STRUCT_IMPL *obj = malloc(sizeof(struct STRUCT_IMPL)); \
        if (!obj) return NULL; \
        memset(obj, 0, sizeof(struct STRUCT_IMPL)); \
        CONCAT3(STRUCT_IMPL, _init_methods, )(obj); \
        return obj; \
    } \
    static void CONCAT3(STRUCT_IMPL, _destroy, ) (struct STRUCT_IMPL* obj) { \
        if (obj) { free(obj); } \
    } \
    static void CONCAT3(STRUCT_IMPL, _init_methods, ) (struct STRUCT_IMPL *self)

// Register multiple trait conformances for STRUCT_IMPL
#define impl_traits(...) FOR_EACH_STRUCT_IMPL_TRAIT(STRUCT_IMPL, __VA_ARGS__)
#define FOR_EACH_STRUCT_IMPL_TRAIT_1(S, T1) struct_impl_trait_type(S, T1)
#define FOR_EACH_STRUCT_IMPL_TRAIT_2(S, T1, T2) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2)
#define FOR_EACH_STRUCT_IMPL_TRAIT_3(S, T1, T2, T3) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3)
#define FOR_EACH_STRUCT_IMPL_TRAIT_4(S, T1, T2, T3, T4) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4)
#define FOR_EACH_STRUCT_IMPL_TRAIT_5(S, T1, T2, T3, T4, T5) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4) struct_impl_trait_type(S, T5)
#define FOR_EACH_STRUCT_IMPL_TRAIT_6(S, T1, T2, T3, T4, T5, T6) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4) struct_impl_trait_type(S, T5) struct_impl_trait_type(S, T6)
#define FOR_EACH_STRUCT_IMPL_TRAIT_7(S, T1, T2, T3, T4, T5, T6, T7) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4) struct_impl_trait_type(S, T5) struct_impl_trait_type(S, T6) struct_impl_trait_type(S, T7)
#define FOR_EACH_STRUCT_IMPL_TRAIT_8(S, T1, T2, T3, T4, T5, T6, T7, T8) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4) struct_impl_trait_type(S, T5) struct_impl_trait_type(S, T6) struct_impl_trait_type(S, T7) struct_impl_trait_type(S, T8)
#define FOR_EACH_STRUCT_IMPL_TRAIT_9(S, T1, T2, T3, T4, T5, T6, T7, T8, T9) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4) struct_impl_trait_type(S, T5) struct_impl_trait_type(S, T6) struct_impl_trait_type(S, T7) struct_impl_trait_type(S, T8) struct_impl_trait_type(S, T9)
#define FOR_EACH_STRUCT_IMPL_TRAIT_10(S, T1, T2, T3, T4, T5, T6, T7, T8, T9, T10) struct_impl_trait_type(S, T1) struct_impl_trait_type(S, T2) struct_impl_trait_type(S, T3) struct_impl_trait_type(S, T4) struct_impl_trait_type(S, T5) struct_impl_trait_type(S, T6) struct_impl_trait_type(S, T7) struct_impl_trait_type(S, T8) struct_impl_trait_type(S, T9) struct_impl_trait_type(S, T10)
#define GET_FOR_EACH_STRUCT_IMPL_TRAIT_MACRO(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,NAME,...) NAME
#define FOR_EACH_STRUCT_IMPL_TRAIT(S, ...) \
  GET_FOR_EACH_STRUCT_IMPL_TRAIT_MACRO(__VA_ARGS__, \
    FOR_EACH_STRUCT_IMPL_TRAIT_10, FOR_EACH_STRUCT_IMPL_TRAIT_9, FOR_EACH_STRUCT_IMPL_TRAIT_8, \
    FOR_EACH_STRUCT_IMPL_TRAIT_7, FOR_EACH_STRUCT_IMPL_TRAIT_6, FOR_EACH_STRUCT_IMPL_TRAIT_5, \
    FOR_EACH_STRUCT_IMPL_TRAIT_4, FOR_EACH_STRUCT_IMPL_TRAIT_3, FOR_EACH_STRUCT_IMPL_TRAIT_2, \
    FOR_EACH_STRUCT_IMPL_TRAIT_1)(S, __VA_ARGS__)

// Defines a method implementation for a struct.
// Usage: def(method_name, { ... })
//   - method_name: name of the method field
//   - block: block/closure body (self is in scope)
#define def(method_name, block) \
    self->method_name = Block_copy(^block); \
    extern void CONCAT4(TRAIT_VALIDATION_, method_name, _IMPLEMENTED_for_, STRUCT_IMPL)(void)


// --- TRAIT FIELD GENERATION MACROS ---

// Internal: Expands to a struct field or method pointer.
#define TRAIT_FIELD(ret_type, name, kind, ...) \
    TRAIT_FIELD_##kind(ret_type, name, ##__VA_ARGS__)

// Expands all trait fields for use in a struct.
// Usage: use(Trait_MyTrait)
#define use(methods) \
    methods(TRAIT_FIELD)

// Compose a trait into a struct.
// Usage: trait(X, Trait_MyTrait)
#define trait(X, trait_macro) \
    trait_macro(X)

// Field expansion for struct fields.
#define TRAIT_FIELD_field(ret_type, name, ...) \
    ret_type name;
// Field expansion for struct methods (block pointer).
#define TRAIT_FIELD_method(ret_type, name, ...) \
    ret_type (^name)(__VA_ARGS__);

// --- TRAIT OBJECT FIELD MACROS ---

// Internal: Expands to a trait object field (pointer for fields, block for methods).
#define TRAIT_OBJ_FIELD(ret_type, name, kind, ...) \
    TRAIT_OBJ_FIELD_##kind(ret_type, name, ##__VA_ARGS__)
#define TRAIT_OBJ_FIELD_field(ret_type, name, ...) \
    ret_type* name;
#define TRAIT_OBJ_FIELD_method(ret_type, name, ...) \
    ret_type (^name)(__VA_ARGS__);

// --- TRAIT TYPE DECLARATION MACRO ---

// Defines a trait object type from a trait macro.
// Usage: define_type_from_trait(TraitName, Trait_MyTrait)
//   - TraitName: name of the trait object type
//   - Trait_MyTrait: trait macro
#define define_type_from_trait(trait_name, methods) \
    typedef struct trait_name { \
        void* _src; \
        methods(TRAIT_OBJ_FIELD) \
    } trait_name; \
    static void trait_name##_destroy(trait_name* trait_obj) { \
        if (trait_obj) { free(trait_obj); } \
    }

// --- TRAIT IMPLEMENTATION MACROS ---

// Internal: Copies a field or method from struct to trait object.
#define COPY_METHOD(ret_type, name, kind, ...) \
    COPY_METHOD_##kind(ret_type, name, ##__VA_ARGS__)
#define COPY_METHOD_field(ret_type, name, ...) \
    dst->name = &(src->name);
#define COPY_METHOD_method(ret_type, name, ...) \
    dst->name = src->name;

// --- TRAIT VALIDATION MACROS ---

// Compile-time validation: requires a method implementation token.
#define REQUIRE_METHOD_TOKEN(ret_type, name, kind, ...) \
    REQUIRE_METHOD_TOKEN_##kind(ret_type, name, ##__VA_ARGS__)
#define REQUIRE_METHOD_TOKEN_field(ret_type, name, ...) \
    /* No validation needed for fields */
#define REQUIRE_METHOD_TOKEN_method(ret_type, name, ...) \
    CONCAT4(TRAIT_VALIDATION_, name, _IMPLEMENTED_for_, STRUCT_IMPL)();

// Provides a weak validation function for each method.
#define PROVIDE_METHOD_VALIDATION(ret_type, name, kind, ...) \
    PROVIDE_METHOD_VALIDATION_##kind(ret_type, name, ##__VA_ARGS__)
#define PROVIDE_METHOD_VALIDATION_field(ret_type, name, ...) \
    /* No validation needed for fields */
#define PROVIDE_METHOD_VALIDATION_method(ret_type, name, ...) \
    __attribute__((weak)) void TRAIT_VALIDATION_##name##_IMPLEMENTED(void) {}

// --- TRAIT CONFORMANCE MACRO ---

// Registers a struct as implementing a trait and provides trait object conversion.
// Usage: struct_impl_trait_type(MyStruct, MyTrait)
//   - MyStruct: struct type
//   - MyTrait: trait object type
//
// This macro:
//   - Validates all required methods are implemented (compile-time error if not)
//   - Provides conversion functions between struct and trait object
//   - Provides a destroy function for the trait object
#define struct_impl_trait_type(struct_name, trait_type_name) \
    _Pragma("clang diagnostic push") \
    _Pragma("clang diagnostic ignored \"-Wout-of-scope-function\"") \
    static void struct_name##_defines_method_##trait_type_name(void) { \
        Trait_##trait_type_name(REQUIRE_METHOD_TOKEN) \
    } \
    _Pragma("clang diagnostic pop") \
    static trait_type_name* trait_type_name##_from_##struct_name(struct struct_name* obj) { \
        trait_type_name* result = malloc(sizeof(trait_type_name)); \
        if (!result) return NULL; \
        result->_src = obj; \
        struct struct_name* src = obj; \
        trait_type_name* dst = result; \
        Trait_##trait_type_name(COPY_METHOD) \
        return result; \
    } \
    static struct struct_name* struct_name##_from_##trait_type_name(trait_type_name* trait_obj) { \
        return (struct struct_name*)trait_obj->_src; \
    } \

#endif // TRAIT_H