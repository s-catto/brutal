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

#define S_MAGAL_STD "./sprites/sMagal/sprite_STD.png"
#define S_MAGAL_WLK "./sprites/sMagal/sprite_WLK.png"
#define S_MAGAL_JMP "./sprites/sMagal/sprite_JMP.png"
#define S_MAGAL_CRH "./sprites/sMagal/sprite_CRH.png"
#define S_MAGAL_PUN "./sprites/sMagal/sprite_PUN.png"
#define S_MAGAL_KIK "./sprites/sMagal/sprite_KIK.png"


mano* create_s_magal (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite);
void load_s_magal (ALLEGRO_BITMAP **p_sprites);

/* JACK THOMPSON */

#define J_THOMP_H           320
#define J_THOMP_CR_H        255
#define J_THOMP_W           140
#define J_THOMP_SPRX_L      240
#define J_THOMP_SPRX_R      -120  

#define J_THOMP_STD "./sprites/jThomp/sprite_STD.png"
#define J_THOMP_WLK "./sprites/jThomp/sprite_WLK.png"
#define J_THOMP_JMP "./sprites/jThomp/sprite_JMP.png"
#define J_THOMP_CRH "./sprites/jThomp/sprite_CRH.png"
#define J_THOMP_PUN "./sprites/jThomp/sprite_PUN.png"
#define J_THOMP_KIK "./sprites/jThomp/sprite_KIK.png"

mano* create_j_thomp (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite);
void load_j_thompson (ALLEGRO_BITMAP **p_sprites);

/* MICROWAVE TOSTEX */

#define M_TOSTX_H           320
#define M_TOSTX_CR_H        255
#define M_TOSTX_W           120
#define M_TOSTX_SPRX_L      260
#define M_TOSTX_SPRX_R      -140

#define M_TOSTX_STD "./sprites/mwvTostex/sprite_STD.png"
#define M_TOSTX_WLK "./sprites/mwvTostex/sprite_WLK.png"
#define M_TOSTX_JMP "./sprites/mwvTostex/sprite_JMP.png"
#define M_TOSTX_CRH "./sprites/mwvTostex/sprite_CRH.png"
#define M_TOSTX_PUN "./sprites/mwvTostex/sprite_PUN.png"
#define M_TOSTX_KIK "./sprites/mwvTostex/sprite_KIK.png"

mano* create_m_tostx (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite);
void load_mwv_tostex (ALLEGRO_BITMAP **p_sprites);

/* PALHAÇO RAMBOZO */

#define P_RAMBO_H           320
#define P_RAMBO_CR_H        255
#define P_RAMBO_W           120
#define P_RAMBO_SPRX_L      260
#define P_RAMBO_SPRX_R      -140

#define P_RAMBO_STD "./sprites/pRambozo/sprite_STD.png"
#define P_RAMBO_WLK "./sprites/pRambozo/sprite_WLK.png"
#define P_RAMBO_JMP "./sprites/pRambozo/sprite_JMP.png"
#define P_RAMBO_CRH "./sprites/pRambozo/sprite_CRH.png"
#define P_RAMBO_PUN "./sprites/pRambozo/sprite_PUN.png"
#define P_RAMBO_KIK "./sprites/pRambozo/sprite_KIK.png"

mano* create_p_rambo (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite);
void load_p_rambozo (ALLEGRO_BITMAP **p_sprites);

/* STEVE MAGAL DO FUTURO */

/* medidas são as mesmas do Steve normal*/

#define S_FTURO_STD "./sprites/sFuturo/sprite_STD.png"
#define S_FTURO_WLK "./sprites/sFuturo/sprite_WLK.png"
#define S_FTURO_JMP "./sprites/sFuturo/sprite_JMP.png"
#define S_FTURO_CRH "./sprites/sFuturo/sprite_CRH.png"
#define S_FTURO_PUN "./sprites/sFuturo/sprite_PUN.png"
#define S_FTURO_KIK "./sprites/sFuturo/sprite_KIK.png"


mano* create_s_fturo (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite);
void load_s_futuro (ALLEGRO_BITMAP **p_sprites);

/* geral */

#define STD 0
#define WLK 1
#define JMP 2
#define CRH 3
#define PUN 4
#define KIK 5

void destroy_sprites(ALLEGRO_BITMAP** p_sprites);

#endif
