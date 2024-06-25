#ifndef __PERSO__
#define __PERSO__

#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "mano.h"

/* STEVE MAGAL */

#define S_MAGAL_H           320
#define S_MAGAL_CR_H        255
#define S_MAGAL_W           120
#define S_MAGAL_SPRX_L      230
#define S_MAGAL_SPRX_R      -120       

#define S_MAGAL_STD "./sprites/sMagal/sprite_0.png"
#define S_MAGAL_WLK "./sprites/sMagal/sprite_1.png"
#define S_MAGAL_JMP "./sprites/sMagal/sprite_2.png"
#define S_MAGAL_CRH "./sprites/sMagal/sprite_3.png"

mano* create_s_magal (int isplayer2, int max_x, int max_y, ALLEGRO_BITMAP* sprite);
void load_s_magal (ALLEGRO_BITMAP **p_sprites);

/* JACK THOMPSON */

#define J_THOMP_H           320
#define J_THOMP_CR_H        255
#define J_THOMP_W           140
#define J_THOMP_SPRX_L      240
#define J_THOMP_SPRX_R      -120  

#define J_THOMP_STD "./sprites/jThomp/sprite_0.png"
#define J_THOMP_WLK "./sprites/jThomp/sprite_1.png"
#define J_THOMP_JMP "./sprites/jThomp/sprite_2.png"
#define J_THOMP_CRH "./sprites/jThomp/sprite_3.png"

mano* create_j_thomp (int isplayer2, int max_x, int max_y, ALLEGRO_BITMAP* sprite);
void load_j_thompson (ALLEGRO_BITMAP **p_sprites);


/* geral */

void destroy_sprites(ALLEGRO_BITMAP** p_sprites);

#endif