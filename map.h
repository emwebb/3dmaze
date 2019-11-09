#ifndef MAP_H
#define MAP_H
#include <stdint.h>
#include <stddef.h>
#include <cx16.h>
#include <stdbool.h>
#include "math.h"
static uint8_t* game_map = (uint8_t*)0xA000;


#define map_load() VIA1.pra = 0x01
#define map_get(x,y) (((game_map[(x + (y * 128))/2] << (((x + (y * 128)) % 2)*4)) & 0xF) >> 4)

typedef struct map_coordinate {
    int8_t x;
    int8_t y;
} map_coordinate;

void map_init();
void generate_maze();
void map_set(uint8_t val, uint8_t x, uint8_t y);
#endif