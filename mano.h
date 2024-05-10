#ifndef __MANO__
#define __MANO__

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "box.h"
#include "joystick.h"

#define MANO_STEP 10

#define STAND       0
#define CROUCH      2
#define JUMP        3
#define AIRBORNE    4
#define WALKL       5
#define WALKR       6
#define PUNCH       7
#define KICK        8

#define S_MAGAL_S "./sprites/sMagal/sprite_0.bmp"
#define S_MAGAL_W "./sprites/sMagal/sprite_1.bmp"
#define S_MAGAL_J "./sprites/sMagal/sprite_2.bmp"
#define S_MAGAL_C "./sprites/sMagal/sprite_3.bmp"

typedef struct {
    int width;
    int height;
    int x;
    int y;
    
    box *coli;
    ALLEGRO_BITMAP *sprite;
    
    int state;
    int vy;
    
    joystick *control;
} mano;

mano* mano_create(int width, int height, 
                  int x, int y, 
                  int max_x, int max_y);
                  
void mano_move(mano *element, int steps, int trajectory, int max_x, int max_y);

void mano_crouch (mano *mano); 
void mano_uncrouch(mano *mano);
void mano_jump(mano* mano);
  
void mano_destroy(mano *element);

#endif
