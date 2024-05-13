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
#define PUNCH       7
#define KICK        8

#define S_MAGAL_STD "./sprites/sMagal/sprite_0.png"
#define S_MAGAL_WLK "./sprites/sMagal/sprite_1.png"
#define S_MAGAL_JMP "./sprites/sMagal/sprite_2.png"
#define S_MAGAL_CRH "./sprites/sMagal/sprite_3.png"

#define J_THOMP_STD "./sprites/jThomp/sprite_0.png"
#define J_THOMP_WLK "./sprites/jThomp/sprite_1.png"
#define J_THOMP_JMP "./sprites/jThomp/sprite_2.png"
#define J_THOMP_CRH "./sprites/jThomp/sprite_3.png"

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
    int state;
    int vy;
    
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
