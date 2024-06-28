#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "personagens.h"
#include "mano.h"

/* Steve Magal */
mano* create_s_magal (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite) {
    if (isplayer2) {
        mano* player = mano_create(sq_sprite, sprite, "STEVE MAGAL", 
                       S_MAGAL_W, S_MAGAL_H,
                       max_x - S_MAGAL_SPRX_L, max_y, 
                       max_x, max_y, 
                       LEFT, S_MAGAL_SPRX_L, S_MAGAL_SPRX_R, S_MAGAL_CR_H);
        return player;
    }
    mano* player = mano_create(sq_sprite, sprite, "STEVE MAGAL",
                   S_MAGAL_W, S_MAGAL_H, 
                   - S_MAGAL_SPRX_R, max_y, 
                   max_x, max_y, 
                   RIGHT, S_MAGAL_SPRX_L, S_MAGAL_SPRX_R, S_MAGAL_CR_H);
   
   return player;   
}

void load_s_magal (ALLEGRO_BITMAP **p_sprites) {
    p_sprites[0] = al_load_bitmap(S_MAGAL_STD);
    p_sprites[1] = al_load_bitmap(S_MAGAL_WLK);
    p_sprites[2] = al_load_bitmap(S_MAGAL_JMP);
    p_sprites[3] = al_load_bitmap(S_MAGAL_CRH);
    p_sprites[4] = al_load_bitmap(S_MAGAL_PUN);
    p_sprites[5] = al_load_bitmap(S_MAGAL_KIK);
    
    return;       
}

/* Jack Thompson */

mano* create_j_thomp (int isplayer2, int max_x, int max_y, 
                      ALLEGRO_BITMAP* sprite, ALLEGRO_BITMAP* sq_sprite) {
    if (isplayer2) {
        mano* player = mano_create(sq_sprite, sprite, "JACK THOMPSON",
                       J_THOMP_W, J_THOMP_H, 
                       max_x - J_THOMP_SPRX_L, max_y, 
                       max_x, max_y, 
                       LEFT, J_THOMP_SPRX_L, J_THOMP_SPRX_R, J_THOMP_CR_H);
        return player;
    }
    mano* player = mano_create(sq_sprite, sprite, "JACK THOMPSON", 
                   J_THOMP_W, J_THOMP_H, 
                   - J_THOMP_SPRX_R, max_y, 
                   max_x, max_y, 
                   RIGHT, J_THOMP_SPRX_L, J_THOMP_SPRX_R, J_THOMP_CR_H);
    
    return player;
}

void load_j_thompson (ALLEGRO_BITMAP **p_sprites) {
    p_sprites[0] = al_load_bitmap(J_THOMP_STD);
    p_sprites[1] = al_load_bitmap(J_THOMP_WLK);
    p_sprites[2] = al_load_bitmap(J_THOMP_JMP);
    p_sprites[3] = al_load_bitmap(J_THOMP_CRH); 
    p_sprites[4] = al_load_bitmap(J_THOMP_PUN); 
    p_sprites[5] = al_load_bitmap(J_THOMP_KIK);    
    
    return;
}

/* geral */
void destroy_sprites(ALLEGRO_BITMAP** p_sprites) {
    for (int i = 0; i < 4; i++)
        al_destroy_bitmap(p_sprites[i]);
}
