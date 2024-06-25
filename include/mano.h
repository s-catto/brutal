#ifndef __MANO__
#define __MANO__

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "box.h"
#include "joystick.h"

#define MANO_STEP 10

/*para onde o personagem está virado*/
#define LEFT  0
#define RIGHT 1

#define STAND       0
#define CROUCH      2
#define JUMP        3
#define AIRBORNE    4
#define WALKL       5
#define WALKR       6

#define NONE        0
#define PUNCH       1
#define KICK        2

typedef struct {
    int face;
    int x_L;
    int x_R;
    int cr_H;
} spr_settings;

typedef struct {
    int width;
    int height;
    int x;
    int y;
    
    box *coli;
    
    ALLEGRO_BITMAP *sprite;
    spr_settings* spr_sett;
    
    int vy;
    int state;
    
    joystick *control;
} mano;

mano* mano_create(ALLEGRO_BITMAP* sprite, int width, int height, 
                  int x, int y, 
                  int max_x, int max_y,
                  int face, int x_L, int x_R, int cr_H);
                  
void mano_move(mano *element, int steps, int trajectory, int max_x, int max_y);

void mano_crouch (mano *mano); 
void mano_uncrouch(mano *mano);
void mano_jump(mano* mano);
  
void mano_destroy(mano *element);

#endif
