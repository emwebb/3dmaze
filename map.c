#include "map.h"

bool visited_cells[63][63];
uint16_t num_unvisited_cells = 3969;
map_coordinate stack[1296];
uint16_t stack_pointer = 0;

void map_set(uint8_t val, uint8_t x, uint8_t y) {
    uint16_t index = ((uint16_t)x + ((uint16_t)y * 128))/2;
    uint8_t remainder =  ((uint16_t)x + ((uint16_t)y * 128))%2;
    game_map[index] &= 0x0F << (remainder * 4);
    if(val) {
        if(remainder) {
            remainder = 0;
        } else {
            remainder = 1;
        }
        game_map[index] |= val << (remainder * 4);
    } 
}
void map_init() {
    uint8_t x, y;
    map_load();
    for(x = 0; x < 128; x++) {
        for(y = 0; y < 128; y++) {
            if(!(x & y & 1) && x < 127 && y < 127) {
               map_set(0xF,x,y);
            }
        }
    }
}

void generate_maze() {
    map_coordinate current_cell;
    current_cell.x = rand8() % 63;
    current_cell.y = rand8() % 63;
    visited_cells[current_cell.x][current_cell.y] = true;
    num_unvisited_cells--;
    while(num_unvisited_cells > 0) {
        bool left_visited = true;
        bool right_visited = true;
        bool top_visited = true;
        bool bottom_visited = true;

        if(current_cell.x > 0) {
            left_visited = visited_cells[current_cell.x - 1][current_cell.y];
        }

        if(current_cell.x < 62) {
            right_visited = visited_cells[current_cell.x + 1][current_cell.y];
        }

        if(current_cell.y > 0) {
            top_visited = visited_cells[current_cell.x][current_cell.y - 1];
        }

        if(current_cell.y < 62) {
            bottom_visited = visited_cells[current_cell.x][current_cell.y + 1];
        }

        if(!(left_visited && right_visited && top_visited && bottom_visited)){
            map_coordinate choices[4];
            uint16_t num_choices;
            map_coordinate wall;
            map_coordinate new_cell;
            num_choices = 0;
            if(!left_visited) {
                choices[num_choices].x = current_cell.x - 1;
                choices[num_choices].y = current_cell.y;
                num_choices++;
            }

            if(!right_visited) {
                choices[num_choices].x = current_cell.x + 1;
                choices[num_choices].y = current_cell.y;
                num_choices++;
            }

            if(!top_visited) {
                choices[num_choices].x = current_cell.x;
                choices[num_choices].y = current_cell.y - 1;
                num_choices++;
            }

            if(!bottom_visited) {
                choices[num_choices].x = current_cell.x;
                choices[num_choices].y = current_cell.y + 1;
                num_choices++;
            }

            new_cell = choices[rand8() % (num_choices)];
            wall.x = (((new_cell.x * 2) + 1) + ((current_cell.x * 2) + 1))/2;
            wall.y = (((new_cell.y * 2) + 1) + ((current_cell.y * 2) + 1))/2;

            map_set(0x0, wall.x, wall.y);
            
            VERA.address = wall.x/2 + wall.y*160;
            VERA.address_hi = 0x10;
            VERA.data0 = game_map[wall.x/2 + wall.y*64];
            if(num_choices > 1) {
                stack[stack_pointer++] = current_cell;
            }


            visited_cells[new_cell.x][new_cell.y] = true;
            num_unvisited_cells--;
            current_cell = new_cell;


        } else if (stack != 0) {
            while(1) {
                current_cell = stack[--stack_pointer];
                if(stack == 0) {
                    break;
                }
                left_visited = true;
                if(current_cell.x > 0) {
                    left_visited = visited_cells[current_cell.x - 1][ current_cell.y];
                }

                right_visited = true;
                if(current_cell.x < 62) {
                    right_visited = visited_cells[current_cell.x + 1][ current_cell.y];
                }

                top_visited = true;
                if(current_cell.y > 0) {
                    top_visited = visited_cells[current_cell.x][current_cell.y - 1];
                }
                
                bottom_visited = true;
                if(current_cell.y < 62) {
                    bottom_visited = visited_cells[current_cell.x][current_cell.y + 1];
                }

                if(!(left_visited && right_visited && top_visited && bottom_visited)) {
                    break;
                }
            }
        }
    }
}