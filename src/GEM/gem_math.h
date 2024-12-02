#ifndef GEM_MATH_H
#define GEM_MATH_H

// -------------------------------------------
// Constants
// -------------------------------------------

// TODO: These should all be pre-calculated!
// PI
#define G_PI    3.14159265358979323846f
// PI / 2
#define G_PI_2  1.57079632679489661923f
// PI / 4
#define G_PI_4  0.78539816339744830961f
// 2 * PI
#define G_TAU   6.28318530717958647692f
// Euler's number
#define G_EULER 2.71828182845904523536f

#define G_DEG_TO_RAD (G_PI / 180.0f)
#define G_RAD_TO_DEG (180.0f / G_PI)

// defaults to 1e-5
#ifndef G_EPSILON_32
#define G_EPSILON_32 FLT_EPSILON
#endif

// defaults to 1e-9
#ifndef G_EPSILON_64
#define G_EPSILON_64 DBL_EPSILON
#endif

// sqrt(2)
#define G_SQRT2  1.41421356237309504880f
// sqrt(3)
#define G_SQRT3  1.73205080756887729352f
// 1 / sqrt(2)
#define G_RSQRT2 0.70710678118654752440f
// 1 / sqrt(3)
#define G_RSQRT3 0.57735026918962576450f

// Factorial
#define G_FACTORIAL32_MAX 12
#define G_FACTORIAL64_MAX 20

// Origin
#define ORIGIN_TOP_LEFT      ((vec2){-0.5f,  0.5f})
#define ORIGIN_TOP_MIDDLE    ((vec2){ 0.0f,  0.5f})
#define ORIGIN_TOP_RIGHT     ((vec2){ 0.5f,  0.5f})

#define ORIGIN_CENTER_LEFT   ((vec2){-0.5f,  0.0f})
#define ORIGIN_CENTER        ((vec2){ 0.0f,  0.0f})
#define ORIGIN_CENTER_RIGHT  ((vec2){ 0.5f,  0.0f})

#define ORIGIN_BOTTOM_LEFT   ((vec2){-0.5f, -0.5f})
#define ORIGIN_BOTTOM_MIDDLE ((vec2){ 0.0f, -0.5f})
#define ORIGIN_BOTTOM_RIGHT  ((vec2){ 0.5f, -0.5f})

// -------------------------------------------
// Data Types
// -------------------------------------------

// -- Vector 2
typedef struct {
    union {
        struct {
            f32 x, y;
        };
        struct {
            f32 w, h;
        };
        struct {
            f32 width, height;
        };
        struct {
            f32 u, v;
        };
        f32 values[2];
    };
} vec2;

typedef struct {
    union {
        struct {
            i32 x, y;
        };
        struct {
            i32 w, h;
        };
        struct {
            i32 width, height;
        };
        struct {
            i32 u, v;
        };
        i32 values[2];
    };
} vec2i;

// -- Vector 3
typedef struct {
    union {
        struct {
            f32 x, y, z;
        };
        struct {
            f32 r, g, b;
        };
        f32 values[3];
    };
} vec3;

typedef struct {
    union {
        struct {
            i32 x, y, z;
        };
        struct {
            i32 r, g, b;
        };
        i32 values[3];
    };
} vec3i;

// -- Vector 4
typedef struct {
    union {
        struct {
            f32 x, y, z, w;
        };
        struct {
            f32 r, g, b, a;
        };
        f32 values[4];
    };
} vec4;

typedef struct {
    union {
        struct {
            i32 x, y, z, w;
        };
        struct {
            i32 r, g, b, a;
        };
        i32 values[4];
    };
} vec4i;

// -- Matrix 3x3 (Column-Major)
typedef struct {
    union {
        struct {
            f32 m0, m3, m6; // First row
            f32 m1, m4, m7; // Second row
            f32 m2, m5, m8; // Third row
        };
        f32 values[9];
    };
} mat3;

// Float array containing 9 elements
typedef struct {
    f32 values[9];
} f32_9;

// -- Matrix 4x4 (Column-Major)
typedef struct {
    union {
        struct {
            f32 m0, m4, m8 , m12; // First row
            f32 m1, m5, m9 , m13; // Second row
            f32 m2, m6, m10, m14; // Third row
            f32 m3, m7, m11, m15; // Fourth row
        };
        f32 values[16];
    };
} mat4;

// Float array containing 16 elements
typedef struct {
    f32 values[16];
} f32_16;

// -- Shapes
// typedef struct {
//     i32 x;
//     i32 y;
//     i32 width;
//     i32 height;
// } region_t;

typedef struct {
    i32 x;
    i32 y;
    i32 width;
    i32 height;
} rectangle_t;

// TODO: Do I need this?
typedef struct {
    i16 x;
    i16 y;
    i16 width;
    i16 height;
} rectangle_short_t;

// -- Compound
typedef struct {
    vec2 position;
    vec2 origin;
    f32 rotation;
    f32 scale;
} transform_t;

// -------------------------------------------
// Functions
// -------------------------------------------

// -- Core
inl f32 math_minf(f32 a, f32 b) { return fminf(a, b); }
inl f32 math_maxf(f32 a, f32 b) { return fmaxf(a, b); }
inl i32 math_mini(i32 a, i32 b) { return a < b ? a : b; }
inl i32 math_maxi(i32 a, i32 b) { return a > b ? a : b; }

inl f32 math_sin(f32 x) { return sinf(x); }
inl f32 math_cos(f32 x) { return cosf(x); }
inl f32 math_tan(f32 x) { return tanf(x); }

inl f32 math_arcsin(f32 x) { return asinf(x); }
inl f32 math_arccos(f32 x) { return acosf(x); }
inl f32 math_arctan(f32 x) { return atanf(x); }
inl f32 math_arctan2(f32 y, f32 x) { return atan2f(y, x); }

inl f32 math_square(f32 x) { return x * x; }
inl f32 math_sqrt(f32 x) { return sqrtf(x); }
inl f32 math_abs(f32 x) { return fabsf(x); }
inl f32 math_pow(f32 x, f32 p) { return powf(x, p); }
inl f32 math_exp(f32 x) { return powf(G_EULER, x); }
inl f32 math_log(f32 x) { return logf(x); }
inl f32 math_log10(f32 x) { return log10f(x); }
inl f32 math_logB(f32 b, f32 x) { return logf(x) / logf(b); }

inl f32 math_ceil(f32 x) { return ceilf(x); }
inl f32 math_floor(f32 x) { return floorf(x); }
inl f32 math_round(f32 x) { return roundf(x); }
inl f32 math_fract(f32 x) { return x - floorf(x); }

inl i32 math_ceil_to_int(f32 x) { return (i32)ceilf(x); }
inl i32 math_floor_to_int(f32 x) { return (i32)floorf(x); }
inl i32 math_round_to_int(f32 x) { return (i32)roundf(x); }

inl f32 math_sign(f32 x) {
    return x == 0.0f ? 0.0f : (x > 0.0f ? 1.0f : -1.0f);
}

inl f32 math_clamp(f32 val, f32 min, f32 max) {
    f32 out = (val < min) ? min : val; // min bounds
    return (out > max) ? max : out;    // max bounds
}

inl f32 math_clamp01(f32 val) {
    f32 out = (val < 0.0f) ? 0.0f : val; // min bounds
    return (out > 1.0f) ? 1.0f : out;    // max bounds
}

inl f32 math_lerp(f32 a, f32 b, f32 t) {
    return a + (b - a) * t;
}

inl f32 math_lerp01(f32 a, f32 b, f32 t) {
    return a + (b - a) * math_clamp01(t);
}

inl f32 math_normalize(f32 val, f32 min, f32 max) {
    return (val - min) / (max - min);
}

inl f32 math_remap(f32 val, f32 min0, f32 max0, f32 min1, f32 max1) {
    return ((max1 - min1) / (max0 - min0)) * (val - min0) + min1;
}

inl f32 math_wrap(f32 val, f32 min, f32 max) {
    if (min == max) return 0.0f;
    return val - (max - min) * floorf((val - min) / (max - min));
}

inl bool math_is_power_of_2(u64 x) {
    return (x != 0) && ((x & (x - 1)) == 0);
}

inl bool math_compare_float(f32 f0, f32 f1) {
    return fabsf(f0 - f1) < G_EPSILON_32;
}

inl bool math_compare_float64(f64 f0, f64 f1) {
    return fabs(f0 - f1) < G_EPSILON_64;
}

// -- Vector 2 (Integer)
// Base values
inl vec2i vec2i_ctor(i32 x, i32 y) { return (vec2i){x, y}; }
#define make_vec2i(...) vec2i_ctor(__VA_ARGS__)

inl vec2i vec2i_zero (void) { return vec2i_ctor( 0,  0); }
inl vec2i vec2i_one  (void) { return vec2i_ctor( 1,  1); }
inl vec2i vec2i_up   (void) { return vec2i_ctor( 0,  1); }
inl vec2i vec2i_down (void) { return vec2i_ctor( 0, -1); }
inl vec2i vec2i_left (void) { return vec2i_ctor(-1,  0); }
inl vec2i vec2i_right(void) { return vec2i_ctor( 1,  0); }

#define VEC2I_XAXIS vec2_ctor(1, 0)
#define VEC2I_YAXIS vec2_ctor(0, 1)

// Operations
inl vec2i vec2i_add(vec2i v0, vec2i v1) {
    return vec2i_ctor(v0.x + v1.x, v0.y + v1.y);
}

inl vec2i vec2i_add_value(vec2i v0, i32 val) {
    return vec2i_ctor(v0.x + val, v0.y + val);
}

inl vec2i vec2i_sub(vec2i v0, vec2i v1) {
    return vec2i_ctor(v0.x - v1.x, v0.y - v1.y);
}

inl vec2i vec2i_sub_value(vec2i v0, i32 val) {
    return vec2i_ctor(v0.x - val, v0.y - val);
}

inl vec2i vec2i_mul(vec2i v0, vec2i v1) {
    return vec2i_ctor(v0.x * v1.x, v0.y * v1.y);
}

inl vec2i vec2i_mul_value(vec2i v0, i32 val) {
    return vec2i_ctor(v0.x * val, v0.y * val);
}

// TODO: Should division return a floating point vector?
inl vec2i vec2i_div(vec2i v0, vec2i v1) {
    return vec2i_ctor(v0.x / v1.x, v0.y / v1.y);
}

inl vec2i vec2i_div_value(vec2i v0, i32 val) {
    return vec2i_ctor(v0.x / val, v0.y / val);
}

// -- Vector 2 (Float)
// Base values
inl vec2 vec2_ctor(f32 x, f32 y) { return (vec2){x, y}; }
#define make_vec2(...) vec2_ctor(__VA_ARGS__)

inl vec2 vec2_zero (void) { return vec2_ctor( 0.0f,  0.0f); }
inl vec2 vec2_one  (void) { return vec2_ctor( 1.0f,  1.0f); }
inl vec2 vec2_up   (void) { return vec2_ctor( 0.0f,  1.0f); }
inl vec2 vec2_down (void) { return vec2_ctor( 0.0f, -1.0f); }
inl vec2 vec2_left (void) { return vec2_ctor(-1.0f,  0.0f); }
inl vec2 vec2_right(void) { return vec2_ctor( 1.0f,  0.0f); }

#define VEC2_XAXIS vec2_ctor(1.0f, 0.0f)
#define VEC2_YAXIS vec2_ctor(0.0f, 1.0f)

// Operations
inl vec2 vec2_add(vec2 v0, vec2 v1) {
    return vec2_ctor(v0.x + v1.x, v0.y + v1.y);
}

inl vec2 vec2_add_value(vec2 v0, f32 val) {
    return vec2_ctor(v0.x + val, v0.y + val);
}

inl vec2 vec2_sub(vec2 v0, vec2 v1) {
    return vec2_ctor(v0.x - v1.x, v0.y - v1.y);
}

inl vec2 vec2_sub_value(vec2 v0, f32 val) {
    return vec2_ctor(v0.x - val, v0.y - val);
}

inl vec2 vec2_mul(vec2 v0, vec2 v1) {
    return vec2_ctor(v0.x * v1.x, v0.y * v1.y);
}

inl vec2 vec2_mul_value(vec2 v0, f32 val) {
    return vec2_ctor(v0.x * val, v0.y * val);
}

inl vec2 vec2_div(vec2 v0, vec2 v1) {
    return vec2_ctor(v0.x / v1.x, v0.y / v1.y);
}

inl vec2 vec2_div_value(vec2 v0, f32 val) {
    return vec2_ctor(v0.x / val, v0.y / val);
}

// Functions
inl f32 vec2_length(vec2 v0) {
    return math_sqrt(v0.x * v0.x + v0.y * v0.y);
}

inl f32 vec2_length_squared(vec2 v0) {
    return v0.x * v0.x + v0.y * v0.y;
}

inl f32 vec2_distance(vec2 v0, vec2 v1) {
    return math_sqrt((v0.x - v1.x) * (v0.x - v1.x) + (v0.y - v1.y) * (v0.y - v1.y));
}

inl f32 vec2_distance_squared(vec2 v0, vec2 v1) {
    return (v0.x - v1.x) * (v0.x - v1.x) + (v0.y - v1.y) * (v0.y - v1.y);
}

inl f32 vec2_dot(vec2 v0, vec2 v1) {
    return v0.x * v1.x + v0.y * v1.y;
}

inl f32 vec2_cross(vec2 v0, vec2 v1) {
    return v0.x * v1.y - v0.y * v1.x;
}

inl vec2 vec2_normalize(vec2 v0) {
    f32 len = vec2_length(v0);
    if (len > 0) return vec2_div_value(v0, len);

    return vec2_ctor(0.0f, 0.0f);
}

inl vec2 vec2_invert(vec2 v0) {
    return vec2_ctor(1.0f / v0.x, 1.0f / v0.y);
}

inl vec2 vec2_clamp(vec2 v0, vec2 min, vec2 max) {
    f32 x = math_clamp(v0.x, min.x, max.x);
    f32 y = math_clamp(v0.y, min.y, max.y);

    return vec2_ctor(x, y);
}

inl f32 vec2_angle_direction(vec2 origin, vec2 v0) {
    v0 = vec2_sub(v0, origin);
    return math_arctan2(v0.y, v0.x);
}

inl f32 vec2_angle_between(vec2 v0, vec2 v1, vec2 origin) {
    v0 = vec2_sub(v0, origin);
    v1 = vec2_sub(v1, origin);

    f32 angle = math_arctan2(vec2_cross(v0, v1), vec2_dot(v0, v1));
    return math_abs(angle);
}

inl vec2 vec2_rotate(vec2 v0, vec2 origin, f32 angle) {
    f32 cosVal = math_cos(angle);
    f32 sinVal = math_sin(angle);

    v0 = vec2_sub(v0, origin);

    f32 x = v0.x * cosVal - v0.y * sinVal;
    f32 y = v0.x * sinVal + v0.y * cosVal;

    return vec2_ctor(x + origin.x, y + origin.y);
}

inl bool vec2_compare(vec2 v0, vec2 v1) {
    return math_compare_float(v0.x, v1.x) && math_compare_float(v0.y, v1.y);
}

// -- Vector 3 (Integer)
// Base values
inl vec3i vec3i_ctor(i32 x, i32 y, i32 z) { return (vec3i){x, y, z}; }
#define make_vec3i(...) vec3i_ctor(__VA_ARGS__)

inl vec3i vec3i_zero (void) { return vec3i_ctor( 0,  0,  0); }
inl vec3i vec3i_one  (void) { return vec3i_ctor( 1,  1,  1); }
inl vec3i vec3i_up   (void) { return vec3i_ctor( 0,  1,  0); }
inl vec3i vec3i_down (void) { return vec3i_ctor( 0, -1,  0); }
inl vec3i vec3i_left (void) { return vec3i_ctor(-1,  0,  0); }
inl vec3i vec3i_right(void) { return vec3i_ctor( 1,  0,  0); }
inl vec3i vec3i_front(void) { return vec3i_ctor( 0,  0,  1); }
inl vec3i vec3i_back (void) { return vec3i_ctor( 0,  0, -1); }

#define VEC3I_XAXIS vec3_ctor(1, 0, 0)
#define VEC3I_YAXIS vec3_ctor(0, 1, 0)
#define VEC3I_ZAXIS vec3_ctor(0, 0, 1)

// Operations
inl vec3i vec3i_add(vec3i v0, vec3i v1) {
    return vec3i_ctor(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

inl vec3i vec3i_add_value(vec3i v0, i32 val) {
    return vec3i_ctor(v0.x + val, v0.y + val, v0.z + val);
}

inl vec3i vec3i_sub(vec3i v0, vec3i v1) {
    return vec3i_ctor(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

inl vec3i vec3i_sub_value(vec3i v0, i32 val) {
    return vec3i_ctor(v0.x - val, v0.y - val, v0.z - val);
}

inl vec3i vec3i_mul(vec3i v0, vec3i v1) {
    return vec3i_ctor(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

inl vec3i vec3i_mul_value(vec3i v0, i32 val) {
    return vec3i_ctor(v0.x * val, v0.y * val, v0.z * val);
}

inl vec3i vec3i_div(vec3i v0, vec3i v1) {
    return vec3i_ctor(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}

inl vec3i vec3i_div_value(vec3i v0, i32 val) {
    return vec3i_ctor(v0.x / val, v0.y / val, v0.z / val);
}

// -- Vector 3 (Float)
// Base values
inl vec3 vec3_ctor(f32 x, f32 y, f32 z) { return (vec3){x, y, z}; }
#define make_vec3(...) vec3_ctor(__VA_ARGS__)

inl vec3 vec3_zero (void) { return vec3_ctor( 0.0f,  0.0f,  0.0f); }
inl vec3 vec3_one  (void) { return vec3_ctor( 1.0f,  1.0f,  1.0f); }
inl vec3 vec3_up   (void) { return vec3_ctor( 0.0f,  1.0f,  0.0f); }
inl vec3 vec3_down (void) { return vec3_ctor( 0.0f, -1.0f,  0.0f); }
inl vec3 vec3_left (void) { return vec3_ctor(-1.0f,  0.0f,  0.0f); }
inl vec3 vec3_right(void) { return vec3_ctor( 1.0f,  0.0f,  0.0f); }
inl vec3 vec3_front(void) { return vec3_ctor( 0.0f,  0.0f,  1.0f); }
inl vec3 vec3_back (void) { return vec3_ctor( 0.0f,  0.0f, -1.0f); }

#define VEC3_XAXIS vec3_ctor(1.0f, 0.0f, 0.0f)
#define VEC3_YAXIS vec3_ctor(0.0f, 1.0f, 0.0f)
#define VEC3_ZAXIS vec3_ctor(0.0f, 0.0f, 1.0f)

// Operations
inl vec3 vec3_add(vec3 v0, vec3 v1) {
    return vec3_ctor(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z);
}

inl vec3 vec3_add_value(vec3 v0, f32 val) {
    return vec3_ctor(v0.x + val, v0.y + val, v0.z + val);
}

inl vec3 vec3_sub(vec3 v0, vec3 v1) {
    return vec3_ctor(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z);
}

inl vec3 vec3_sub_value(vec3 v0, f32 val) {
    return vec3_ctor(v0.x - val, v0.y - val, v0.z - val);
}

inl vec3 vec3_mul(vec3 v0, vec3 v1) {
    return vec3_ctor(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z);
}

inl vec3 vec3_mul_value(vec3 v0, f32 val) {
    return vec3_ctor(v0.x * val, v0.y * val, v0.z * val);
}

inl vec3 vec3_div(vec3 v0, vec3 v1) {
    return vec3_ctor(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z);
}

inl vec3 vec3_div_value(vec3 v0, f32 val) {
    return vec3_ctor(v0.x / val, v0.y / val, v0.z / val);
}

// -- Vector 4 (Integer)
// Base values
inl vec4i vec4i_ctor(i32 x, i32 y, i32 z, i32 w) { return (vec4i){x, y, z, w}; }
#define make_vec4i(...) vec4i_ctor(__VA_ARGS__)

inl vec4i vec4i_zero (void) { return vec4i_ctor(0, 0, 0, 0); }
inl vec4i vec4i_one  (void) { return vec4i_ctor(1, 1, 1, 1); }

#define VEC4I_XAXIS vec4i_ctor(1, 0, 0, 0)
#define VEC4I_YAXIS vec4i_ctor(0, 1, 0, 0)
#define VEC4I_ZAXIS vec4i_ctor(0, 0, 1, 0)
#define VEC4I_WAXIS vec4i_ctor(0, 0, 0, 1)

// Operations
inl vec4i vec4i_add(vec4i v0, vec4i v1) {
    return vec4i_ctor(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
}

inl vec4i vec4i_add_value(vec4i v0, i32 val) {
    return vec4i_ctor(v0.x + val, v0.y + val, v0.z + val, v0.w + val);
}

inl vec4i vec4i_sub(vec4i v0, vec4i v1) {
    return vec4i_ctor(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}

inl vec4i vec4i_sub_value(vec4i v0, i32 val) {
    return vec4i_ctor(v0.x - val, v0.y - val, v0.z - val, v0.w - val);
}

inl vec4i vec4i_mul(vec4i v0, vec4i v1) {
    return vec4i_ctor(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
}

inl vec4i vec4i_mul_value(vec4i v0, i32 val) {
    return vec4i_ctor(v0.x * val, v0.y * val, v0.z * val, v0.w * val);
}

inl vec4i vec4i_div(vec4i v0, vec4i v1) {
    return vec4i_ctor(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
}

inl vec4i vec4i_div_value(vec4i v0, i32 val) {
    return vec4i_ctor(v0.x / val, v0.y / val, v0.z / val, v0.w / val);
}

// -- Vector 4 (Float)
// Base values
inl vec4 vec4_ctor(f32 x, f32 y, f32 z, f32 w) { return (vec4){x, y, z, w}; }
#define make_vec4(...) vec4_ctor(__VA_ARGS__)

inl vec4 vec4_zero (void) { return vec4_ctor(0.0f, 0.0f, 0.0f, 0.0f); }
inl vec4 vec4_one  (void) { return vec4_ctor(1.0f, 1.0f, 1.0f, 1.0f); }

#define VEC4_XAXIS vec4_ctor(1.0f, 0.0f, 0.0f, 0.0f)
#define VEC4_YAXIS vec4_ctor(0.0f, 1.0f, 0.0f, 0.0f)
#define VEC4_ZAXIS vec4_ctor(0.0f, 0.0f, 1.0f, 0.0f)
#define VEC4_WAXIS vec4_ctor(0.0f, 0.0f, 0.0f, 1.0f)

// Operations
inl vec4 vec4_add(vec4 v0, vec4 v1) {
    return vec4_ctor(v0.x + v1.x, v0.y + v1.y, v0.z + v1.z, v0.w + v1.w);
}

inl vec4 vec4_add_value(vec4 v0, f32 val) {
    return vec4_ctor(v0.x + val, v0.y + val, v0.z + val, v0.w + val);
}

inl vec4 vec4_sub(vec4 v0, vec4 v1) {
    return vec4_ctor(v0.x - v1.x, v0.y - v1.y, v0.z - v1.z, v0.w - v1.w);
}

inl vec4 vec4_sub_value(vec4 v0, f32 val) {
    return vec4_ctor(v0.x - val, v0.y - val, v0.z - val, v0.w - val);
}

inl vec4 vec4_mul(vec4 v0, vec4 v1) {
    return vec4_ctor(v0.x * v1.x, v0.y * v1.y, v0.z * v1.z, v0.w * v1.w);
}

inl vec4 vec4_mul_value(vec4 v0, f32 val) {
    return vec4_ctor(v0.x * val, v0.y * val, v0.z * val, v0.w * val);
}

inl vec4 vec4_div(vec4 v0, vec4 v1) {
    return vec4_ctor(v0.x / v1.x, v0.y / v1.y, v0.z / v1.z, v0.w / v1.w);
}

inl vec4 vec4_div_value(vec4 v0, f32 val) {
    return vec4_ctor(v0.x / val, v0.y / val, v0.z / val, v0.w / val);
}

// -- Matrix 3x3
// Base values
inl mat3 mat3_zero(void) {
    mat3 result = {
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f};

    return result;
}

inl mat3 mat3_identity(void) {
    mat3 result = {
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f};

    return result;
}

// Operations
inl f32_9 mat3_as_ordered_array(mat3 mat) {
    f32_9 result = {0};

    result.values[0] = mat.m0;
    result.values[1] = mat.m1;
    result.values[2] = mat.m2;
    result.values[3] = mat.m3;
    result.values[4] = mat.m4;
    result.values[5] = mat.m5;
    result.values[6] = mat.m6;
    result.values[7] = mat.m7;
    result.values[8] = mat.m8;

    return result;
}

inl mat3 mat3_mul(mat3 left, mat3 right) {
    mat3 result = {0};

    result.m0 = (left.m0 * right.m0) + (left.m3 * right.m1) + (left.m6 * right.m2);
    result.m3 = (left.m0 * right.m3) + (left.m3 * right.m4) + (left.m6 * right.m5);
    result.m6 = (left.m0 * right.m6) + (left.m3 * right.m7) + (left.m6 * right.m8);

    result.m1 = (left.m1 * right.m0) + (left.m4 * right.m1) + (left.m7 * right.m2);
    result.m4 = (left.m1 * right.m3) + (left.m4 * right.m4) + (left.m7 * right.m5);
    result.m7 = (left.m1 * right.m6) + (left.m4 * right.m7) + (left.m7 * right.m8);

    result.m2 = (left.m2 * right.m0) + (left.m5 * right.m1) + (left.m8 * right.m2);
    result.m5 = (left.m2 * right.m3) + (left.m5 * right.m4) + (left.m8 * right.m5);
    result.m8 = (left.m2 * right.m6) + (left.m5 * right.m7) + (left.m8 * right.m8);

    return result;
}

// -- Matrix 4x4
// Base values
inl mat4 mat4_zero(void) {
    mat4 result = {
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f};

    return result;
}

inl mat4 mat4_identity(void) {
    mat4 result = {
        1.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f};

    return result;
}

// Operations
inl f32_16 mat4_as_ordered_array(mat4 mat) {
    f32_16 result = {0};

    result.values[0] = mat.m0;
    result.values[1] = mat.m1;
    result.values[2] = mat.m2;
    result.values[3] = mat.m3;
    result.values[4] = mat.m4;
    result.values[5] = mat.m5;
    result.values[6] = mat.m6;
    result.values[7] = mat.m7;
    result.values[8] = mat.m8;
    result.values[9] = mat.m9;
    result.values[10] = mat.m10;
    result.values[11] = mat.m11;
    result.values[12] = mat.m12;
    result.values[13] = mat.m13;
    result.values[14] = mat.m14;
    result.values[15] = mat.m15;

    return result;
}

inl mat4 mat4_mul(mat4 left, mat4 right) {
    mat4 result = {0};

    result.m0  = (left.m0 * right.m0 ) + (left.m4 * right.m1 ) + (left.m8  * right.m2 ) + (left.m12 * right.m3 );
    result.m4  = (left.m0 * right.m4 ) + (left.m4 * right.m5 ) + (left.m8  * right.m6 ) + (left.m12 * right.m7 );
    result.m8  = (left.m0 * right.m8 ) + (left.m4 * right.m9 ) + (left.m8  * right.m10) + (left.m12 * right.m11);
    result.m12 = (left.m0 * right.m12) + (left.m4 * right.m13) + (left.m8  * right.m14) + (left.m12 * right.m15);

    result.m1  = (left.m1 * right.m0 ) + (left.m5 * right.m1 ) + (left.m9  * right.m2 ) + (left.m13 * right.m3 );
    result.m5  = (left.m1 * right.m4 ) + (left.m5 * right.m5 ) + (left.m9  * right.m6 ) + (left.m13 * right.m7 );
    result.m9  = (left.m1 * right.m8 ) + (left.m5 * right.m9 ) + (left.m9  * right.m10) + (left.m13 * right.m11);
    result.m13 = (left.m1 * right.m12) + (left.m5 * right.m13) + (left.m9  * right.m14) + (left.m13 * right.m15);

    result.m2  = (left.m2 * right.m0 ) + (left.m6 * right.m1 ) + (left.m10 * right.m2 ) + (left.m14 * right.m3 );
    result.m6  = (left.m2 * right.m4 ) + (left.m6 * right.m5 ) + (left.m10 * right.m6 ) + (left.m14 * right.m7 );
    result.m10 = (left.m2 * right.m8 ) + (left.m6 * right.m9 ) + (left.m10 * right.m10) + (left.m14 * right.m11);
    result.m14 = (left.m2 * right.m12) + (left.m6 * right.m13) + (left.m10 * right.m14) + (left.m14 * right.m15);

    result.m3  = (left.m3 * right.m0 ) + (left.m7 * right.m1 ) + (left.m11 * right.m2 ) + (left.m15 * right.m3 );
    result.m7  = (left.m3 * right.m4 ) + (left.m7 * right.m5 ) + (left.m11 * right.m6 ) + (left.m15 * right.m7 );
    result.m11 = (left.m3 * right.m8 ) + (left.m7 * right.m9 ) + (left.m11 * right.m10) + (left.m15 * right.m11);
    result.m15 = (left.m3 * right.m12) + (left.m7 * right.m13) + (left.m11 * right.m14) + (left.m15 * right.m15);

    return result;
}

// Functions
// TODO Check if I need a near/far plane calculations
inl mat4 mat4_ortho(f32 left, f32 right, f32 bottom, f32 top, f32 zNear, f32 zFar) {
    mat4 result = {0};

    f32 rl = right - left;
    f32 tb = top - bottom;
    f32 fn = zFar - zNear;

    result.m0  = 2.0f / rl;
    result.m1  = 0.0f;
    result.m2  = 0.0f;
    result.m3  = 0.0f;
    result.m4  = 0.0f;
    result.m5  = 2.0f / tb;
    result.m6  = 0.0f;
    result.m7  = 0.0f;
    result.m8  = 0.0f;
    result.m9  = 0.0f;
    result.m10 = 2.0f / fn;
    result.m11 = 0.0f;
    result.m12 = -(left + right) / rl;
    result.m13 = -(top + bottom) / tb;
    result.m14 = -(zFar + zNear) / fn;
    result.m15 = 1.0f;

    return result;
}

// -- Transform
// Base values
inl transform_t transform_ctor(vec2 position, vec2 origin, f32 rotation, f32 scale) { return (transform_t){position, origin, rotation, scale}; }
#define make_transform(...) transform_ctor(__VA_ARGS__)

inl transform_t transform_zero(void) { return (transform_t){0}; }

#endif // GEM_MATH_H
