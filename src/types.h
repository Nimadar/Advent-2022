#pragma once

#include <cstdint>

#define MOD_MUL2(n, m) ((n) & ((m) - 1))
#define MAX(x1, x2) ((x1) > (x2) ? (x1) : (x2))
#define MIN(x1, x2) ((x1) < (x2) ? (x1) : (x2))
#define CLAMP(x, min, max) MIN(MAX(x, min), max) //Inclusive
#define KB(x)((x) * 1024)
#define MB(x)(KB(x) * 1024)
#define GB(x)(MB(x) * 1024)
#define TB(x)(GB(x) * 1024)
#define ARRAY_COUNT(Array) (sizeof(Array) / sizeof((Array)[0]))
#define BIT(pos) (1 << (pos))

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uintptr_t uptr;
typedef intptr_t sptr; 

typedef float f32;
typedef double f64;

typedef s8 b8;
typedef s32 b32;