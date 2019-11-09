#ifndef H_MATH
#define H_MATH 
#include <stdint.h>
#include <stddef.h>
#include "matharrays.h"

typedef struct fixed_point {
    int16_t integer;
    uint16_t fraction;
} fixed_point;


typedef union fixed_point_u
{
    int32_t index;
    fixed_point value;
} fixed_point_u;

// Angles are measured between 0 and 1 in fixedpoint ie grad/100

#define tan(theta) tan_a[(theta % 0x10000) >> 6]
#define cot(theta) cot_a[(theta % 0x10000) >> 6]
#define sin(theta) sin_a[(theta % 0x10000) >> 6]
#define cos(theta) cos_a[(theta % 0x10000) >> 6]

uint8_t rand8();
uint16_t rand16();
uint32_t rand32();

void rand_set_seed(uint16_t seed);


#endif