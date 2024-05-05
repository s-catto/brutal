#ifndef __SQUARE__
#define __SQUARE__

#include "joystick.h"

#define MANO_STEP 10

typedef struct {
    int width;
    int height;
    int x;
    int y;
    joystick *control;
} mano;

mano* mano_create(int width, int height, 
                  int x, int y, 
                  int max_x, int max_y);
                  
void mano_move(mano *element, int steps, int trajectory, 
               int max_x, int max_y);
               
void mano_destroy(mano *element);

#endif
