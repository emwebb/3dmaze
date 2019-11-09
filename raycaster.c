#include "raycaster.h"
void castrays(uint32_t x, uint32_t y, uint16_t rotation) {
    uint16_t theta;
    for(theta = 0; theta <= 320; theta++) {
        castray(theta, x, y, (theta * FOV_INC) + FOV_MIN);
    }
}

void castray(uint16_t collumn, uint32_t x, uint32_t y, uint16_t rotation) {
    uint32_t tileStepX, tileStepY, xStep, yStep, deltaX, deltaY;
    //figure out which quadrant we are in
    if(rotation >= 0 && rotation < 0x4000){
        tileStepX = 1;
        tileStepY = 1;
    } else if(rotation >= 0x4000 && rotation < 0x8000){
        tileStepX = 1;
        tileStepY = -1;
    } else if(rotation >= 0x8000 && rotation < 0xC000){
        tileStepX = -1;
        tileStepY = -1;
    } else {
        tileStepX = -1;
        tileStepY = 1;
    }
}