#ifndef GEM_DEFINES_H
#define GEM_DEFINES_H

// -------------------------------------------
// Primitive Types
// -------------------------------------------

// Unsigned integer types
typedef uint8_t u8;   // unsigned char
typedef uint16_t u16; // unsigned short
typedef uint32_t u32; // unsigned long
typedef uint64_t u64; // unsigned long long

#define U8_MAX UINT8_MAX
#define U16_MAX UINT16_MAX
#define U32_MAX UINT32_MAX
#define U64_MAX UINT64_MAX

// Signed integer types
typedef int8_t i8;   // signed char
typedef int16_t i16; // signed short
typedef int32_t i32; // signed long
typedef int64_t i64; // signed long long

#define I8_MAX INT8_MAX
#define I16_MAX INT16_MAX
#define I32_MAX INT32_MAX
#define I64_MAX INT64_MAX

// Floating point types
typedef float f32;
typedef double f64;

#define F32_MIN FLT_MIN
#define F32_MAX FLT_MAX
#define F64_MIN DBL_MIN
#define F64_MAX DBL_MAX

// Boolean types
#ifndef __bool_true_false_are_defined
    typedef _Bool bool;
    #define false 0
    #define true 1
    #define __bool_true_false_are_defined 1
#endif

// Range of memory
typedef struct {
    u64 offset;
    u64 size;
} range;

typedef struct {
    i32 offset;
    i32 size;
} range32;

// -------------------------------------------
// Utility
// -------------------------------------------

// Number of bytes
#define KiB(amount) ((amount) * 1024ULL)
#define MiB(amount) ((amount) * 1024ULL * 1024ULL)
#define GiB(amount) ((amount) * 1024ULL * 1024ULL * 1024ULL)

#define KB(amount) ((amount) * 1000ULL)
#define MB(amount) ((amount) * 1000ULL * 1000ULL)
#define GB(amount) ((amount) * 1000ULL * 1000ULL * 1000ULL)

// Static array
#define array_get_count(arr) (sizeof(arr) / sizeof(arr[0]))

// Strings
#define GEM_MAX_STRING_LENGTH 512
#define string_is_valid(str) ((str != NULL) && (str[0] != '\0'))

// Function keywords
#define GAPI __declspec(dllexport)
#define inl __attribute__((unused)) __attribute__((always_inline)) inline

#endif // GEM_DEFINES_H
