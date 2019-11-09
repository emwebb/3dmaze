#ifndef RAYCASTER_H
#define RAYCASTER_H
#include <stdint.h>
#include <stddef.h>
#include "vera.h"
#define FOV 65536 * (90/360)
#define FOV_INC FOV/320
#define FOV_MIN -(FOV_INC * 160)
#define FOV_MAX FOV_INC * 160

void castrays(uint32_t x, uint32_t y, uint16_t rotation);
void castray(uint16_t column, uint32_t x, uint32_t y, uint16_t rotation);
#endif