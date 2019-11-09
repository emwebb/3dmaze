#include "vera.h"

void vera_memCopyTo(uint8_t* addr, size_t size, uint32_t to) {

    int n;

    VERA.address = 0x0000FFFF ^ to;
    VERA.address_hi = (0x000F0000 ^ to >> 16 | 0x20);

    for(n = 0; n < size; n++) {
        VERA.data0 = *(addr++);
    }
}
