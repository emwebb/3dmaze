#include "vera.h"
#include "math.h"
#include "map.h"
int main() {
    uint8_t x;
    uint8_t y;
    // Setup Vera
    vpoke(0b11000001, 0xF2000); // Layer 0 Mode 5 Enable
    // We want 320*240
    vpoke(0b00000000, 0xF2001); // TILEW=320
    vpoke(64, 0xF0001); // DC_HSCALE
    vpoke(64, 0xF0002); // DC_VSCALE
    // Set up Memory
    vpoke(0, 0xF2004); // Layer 0 mem starts at 0;
    vpoke(0, 0xF2005);
    
    
    vpoke(0b00100001, 0xF3000); // Layer 1 Mode 2 Enable
    vpoke(0x00, 0xF3002); // Layer 1 mem starts at 0x12C00;
    vpoke(0x4B, 0xF3003);
    vpoke(0b00000101, 0xF3001);

    rand_set_seed(98);


    map_init();
    for(y = 0; y < 128; y++) {
        VERA.address = y * 160;
        VERA.address_hi = 0x10;
        for(x = 0; x < 64; x++) {
            VERA.data0 = game_map[x + y*64];
        }
    }
    generate_maze();
    for(y = 0; y < 128; y++) {
        VERA.address = y * 160;
        VERA.address_hi = 0x10;
        for(x = 0; x < 64; x++) {
            VERA.data0 = game_map[x + y*64];
        }
    }
    while(1) {

    }

    return 0;
}