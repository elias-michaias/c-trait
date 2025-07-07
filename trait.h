#ifndef TRAIT_H
#define TRAIT_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <Block.h>

// ==================== SIMPLE TRAIT SYSTEM ====================
//
// Clean trait system without deduplication complexity.
// Users handle composition conflicts through careful design.

// ==================== HELPER MACROS ====================

// Helper macros for cleaner syntax
#define field(X, type, name) X(type, name, field)

// Simple variadic method macro - handles any number of arguments
#define method(X, ret_type, name, ...) X(ret_type, name, method, ##__VA_ARGS__)

// Multi-trait composition
#define traits(X, ...) \
    FOR_EACH_TRAIT(EXPAND_TRAIT, X, __VA_ARGS__)

#define EXPAND_TRAIT(X, trait_macro) trait_macro(X)

// Helper macro for applying a macro to each argument  
#define FOR_EACH_TRAIT(macro, X, ...) \
    MAP_TRAITS(macro, X, __VA_ARGS__)

#define MAP_TRAITS(m, X, t, ...) \
    m(X, t) \
    __VA_OPT__(MAP_TRAITS_AGAIN PARENS (m, X, __VA_ARGS__))

#define MAP_TRAITS_AGAIN() MAP_TRAITS
#define PARENS ()

// ==================== CORE MACROS ====================

// Enhanced implementation block
#define impl(struct_name) \
    static void struct_name##_init_methods(struct struct_name *self); \
    \
    static struct struct_name* struct_name##_new() { \
        struct struct_name *obj = malloc(sizeof(struct struct_name)); \
        if (!obj) return NULL; \
        memset(obj, 0, sizeof(struct struct_name)); \
        struct_name##_init_methods(obj); \
        return obj; \
    } \
    \
    static void struct_name##_destroy(struct struct_name* obj) { \
        if (obj) { \
            free(obj); \
        } \
    } \
    \
    static void struct_name##_init_methods(struct struct_name *self)

// Define a method implementation
#define def(method_name, block) \
    self->method_name = Block_copy(^block); \
    extern void TRAIT_VALIDATION_##method_name##_IMPLEMENTED(void)

// ==================== TRAIT SYSTEM ====================

// Generate trait fields - handles both regular fields and function pointers
#define TRAIT_FIELD(ret_type, name, kind, ...) \
    TRAIT_FIELD_##kind(ret_type, name, ##__VA_ARGS__)

// Generate trait struct fields
#define use(methods) \
    methods(TRAIT_FIELD)

// Simple trait composition - just expand the trait macro
#define trait(X, trait_macro) \
    trait_macro(X)

// Helper macros for different field types in struct definitions
#define TRAIT_FIELD_field(ret_type, name, ...) \
    ret_type name;

#define TRAIT_FIELD_method(ret_type, name, ...) \
    ret_type (^name)(__VA_ARGS__);

// Helper macros for different field types in trait object definitions (use pointers for reference-based access)
#define TRAIT_OBJ_FIELD_field(ret_type, name, ...) \
    ret_type* name;

#define TRAIT_OBJ_FIELD_method(ret_type, name, ...) \
    ret_type (^name)(__VA_ARGS__);

// ==================== TRAIT DECLARATION ====================

// Generate trait object fields - handles both regular fields and function pointers
#define TRAIT_OBJ_FIELD(ret_type, name, kind, ...) \
    TRAIT_OBJ_FIELD_##kind(ret_type, name, ##__VA_ARGS__)

// Declare a trait type with back-reference to source struct
#define define_type_from_trait(trait_name, methods) \
    typedef struct trait_name { \
        void* _src; \
        methods(TRAIT_OBJ_FIELD) \
    } trait_name;

// ==================== TRAIT IMPLEMENTATION ====================

// X-macro to copy a single method or field
#define COPY_METHOD(ret_type, name, kind, ...) \
    COPY_METHOD_##kind(ret_type, name, ##__VA_ARGS__)

// Copy methods - fields get pointer references, methods get copied
#define COPY_METHOD_field(ret_type, name, ...) \
    dst->name = &(src->name);

#define COPY_METHOD_method(ret_type, name, ...) \
    dst->name = src->name;

// Compile-time validation macros that require implementation tokens
#define REQUIRE_METHOD_TOKEN(ret_type, name, kind, ...) \
    REQUIRE_METHOD_TOKEN_##kind(ret_type, name, ##__VA_ARGS__)

#define REQUIRE_METHOD_TOKEN_field(ret_type, name, ...) \
    /* Fields don't need validation tokens */

#define REQUIRE_METHOD_TOKEN_method(ret_type, name, ...) \
    TRAIT_VALIDATION_##name##_IMPLEMENTED();

// Provide validation implementations for methods
#define PROVIDE_METHOD_VALIDATION(ret_type, name, kind, ...) \
    PROVIDE_METHOD_VALIDATION_##kind(ret_type, name, ##__VA_ARGS__)

#define PROVIDE_METHOD_VALIDATION_field(ret_type, name, ...) \
    /* Fields don't need validation implementations */

#define PROVIDE_METHOD_VALIDATION_method(ret_type, name, ...) \
    /* Use weak linkage to allow multiple definitions */ \
    __attribute__((weak)) void TRAIT_VALIDATION_##name##_IMPLEMENTED(void) {}

// Register a struct as implementing a trait (automatically derives trait macro name)
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
    static void trait_type_name##_destroy(trait_type_name* trait_obj) { \
        if (trait_obj) { \
            free(trait_obj); \
        } \
    }

#endif // TRAIT_H