#include "math.h"

uint16_t seed;

uint8_t rand8() {
    uint16_t value = (seed * 65521) + 65371;
    seed = value;
    return value;
}

uint16_t rand16() {
    uint16_t value = (seed * 65521) + 65371;
    seed = value;
    return value;
}

uint32_t rand32() {
    return (uint32_t)rand16() & ((uint32_t) rand16() << 16);
}

void rand_set_seed(uint16_t input_seed) {
    seed = input_seed;
}