#ifndef __SQUARE__
#define __SQUARE__

#include "joystick.h"

#define MANO_STEP 10

#define STAND       0
#define CROUCH      1
#define WALKL       2
#define WALKR       3
#define JUMP        4
#define AIRBORNE    5

typedef struct {
    int width;
    int height;
    int x;
    int y;
    int state;
    int vy;
    joystick *control;
} mano;

mano* mano_create(int width, int height, 
                  int x, int y, 
                  int max_x, int max_y);
                  
void mano_move(mano *element, int steps, int trajectory, int max_x, int max_y);
             
void mano_jump(mano *element, int max_x, int max_y);
  
void mano_destroy(mano *element);

#endif
