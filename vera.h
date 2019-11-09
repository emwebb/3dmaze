#ifndef H_VERA
#define H_VERA 

#include <stdint.h>
#include <stddef.h>
#include <6502.h>
#include <cx16.h>



void vera_memCopyTo(uint8_t* addr, size_t size, uint32_t to);

#endif