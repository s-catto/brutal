#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>

#include "../include/mano.h"
#include "../include/personagens.h"
#include "../include/chselect.h"

void load_chr_bitmaps(ALLEGRO_BITMAP **chrs) {
    chrs[0] = al_load_bitmap(CH_S_MAGAL); 
    chrs[1] = al_load_bitmap(CH_J_THOMP);  
    
    return;
}

int ch_select (ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, int max_x, int max_y,
               ALLEGRO_BITMAP** p1_sprites, ALLEGRO_BITMAP** p2_sprites,
               mano** player1, mano** player2) {
    
    character_square ch_sq;
    load_chr_bitmaps(ch_sq.chrs);
    
    ch_sq.cores[0] = COR_P1;
    ch_sq.cores[1] = COR_P2;
    ch_sq.cores[2] = COR_UNSEL;
    ch_sq.cores[3] = COR_UNSEL;
    
    ch_sq.p1 = 0;
    ch_sq.p2 = 1;
    
    while (event.type != 42 && (ch_sq.p1 < 10 || ch_sq.p2 < 10)) {
        if (event.type == 30) {
            al_clear_to_color(al_map_rgb(69, 75, 27));
            
            al_draw_filled_rectangle( GRID_X1, GRID_Y1, GRID_X2, GRID_Y2, al_map_rgb(0,0,0));
            al_draw_filled_rectangle( SQ1_X1, SQ1_Y1, SQ1_X2, SQ1_Y2, ch_sq.cores[0]);
            al_draw_scaled_bitmap(ch_sq.chrs[0], 0, 0, 24, 24, SQ1_X1, SQ1_Y1, 120, 120, 0);
            al_draw_filled_rectangle( SQ2_X1, SQ2_Y1, SQ2_X2, SQ2_Y2, ch_sq.cores[1]);
            al_draw_scaled_bitmap(ch_sq.chrs[1], 0, 0, 24, 24, SQ2_X1, SQ2_Y1, 120, 120, 0);
            al_draw_filled_rectangle( SQ3_X1, SQ3_Y1, SQ3_X2, SQ3_Y2, ch_sq.cores[2]);
            al_draw_filled_rectangle( SQ4_X1, SQ4_Y1, SQ4_X2, SQ4_Y2, ch_sq.cores[3]);
               
            al_flip_display();
        }
        if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
            switch (event.keyboard.keycode)
            {
                case ALLEGRO_KEY_A: 
                    if (ch_sq.p1 < 10)
                        if (ch_sq.p1 % 2 && ch_sq.p1 - 1 != ch_sq.p2 % 10) {
                            ch_sq.cores[ch_sq.p1] = COR_UNSEL;
                            ch_sq.p1--; 
                            ch_sq.cores[ch_sq.p1] = COR_P1;
                        }
                break;
                case ALLEGRO_KEY_D: 
                    if (ch_sq.p1 < 10)
                        if (!(ch_sq.p1 % 2) && ch_sq.p1 + 1 != ch_sq.p2 % 10) {    
                            ch_sq.cores[ch_sq.p1] = COR_UNSEL;
                            ch_sq.p1++; 
                            ch_sq.cores[ch_sq.p1] = COR_P1;
                        }
                break;
                case ALLEGRO_KEY_W: 
                    if (ch_sq.p1 < 10)
                        if ((ch_sq.p1 > 1) && ch_sq.p1 - 2 != ch_sq.p2 % 10) { 
                            ch_sq.cores[ch_sq.p1] = COR_UNSEL;
                            ch_sq.p1 = ch_sq.p1 - 2; 
                            ch_sq.cores[ch_sq.p1] = COR_P1;
                        }
                break;
                case ALLEGRO_KEY_S:
                    if (ch_sq.p1 < 10)
                        if ((ch_sq.p1 <= 1) && ch_sq.p1 + 2 != ch_sq.p2 % 10) { 
                            ch_sq.cores[ch_sq.p1] = COR_UNSEL;
                            ch_sq.p1 = ch_sq.p1 + 2; 
                            ch_sq.cores[ch_sq.p1] = COR_P1;
                        }
                break;
                
                case ALLEGRO_KEY_U:
                    if (ch_sq.p1 < 10)
                        ch_sq.p1 = ch_sq.p1 + 10;   
                break;
                case ALLEGRO_KEY_I:
                    if (ch_sq.p1 >= 10)
                        ch_sq.p1 = ch_sq.p1 - 10;   
                break;
                
                
                case ALLEGRO_KEY_LEFT: 
                    if (ch_sq.p2 < 10)
                        if (ch_sq.p2 % 2 && ch_sq.p2 - 1 != ch_sq.p1 % 10) {
                            ch_sq.cores[ch_sq.p2] = COR_UNSEL;
                            ch_sq.p2--; 
                            ch_sq.cores[ch_sq.p2] = COR_P2;
                        }
                break;
                case ALLEGRO_KEY_RIGHT: 
                    if (ch_sq.p2 < 10)
                        if (!(ch_sq.p2 % 2) && ch_sq.p2 + 1 != ch_sq.p1 % 10) {    
                            ch_sq.cores[ch_sq.p2] = COR_UNSEL;
                            ch_sq.p2++; 
                            ch_sq.cores[ch_sq.p2] = COR_P2;
                        }
                break;
                case ALLEGRO_KEY_UP:
                    if (ch_sq.p2 < 10)
                        if ((ch_sq.p2 > 1) && ch_sq.p2 - 2 != ch_sq.p1 % 10) { 
                            ch_sq.cores[ch_sq.p2] = COR_UNSEL;
                            ch_sq.p2 = ch_sq.p2 - 2; 
                            ch_sq.cores[ch_sq.p2] = COR_P2;
                        }
                break;
                case ALLEGRO_KEY_DOWN:
                    if (ch_sq.p2 < 10)
                        if ((ch_sq.p2 <= 1) && ch_sq.p2 + 2 != ch_sq.p1 % 10) { 
                            ch_sq.cores[ch_sq.p2] = COR_UNSEL;
                            ch_sq.p2 = ch_sq.p2 + 2; 
                            ch_sq.cores[ch_sq.p2] = COR_P2;
                        }
                break;
                
                case ALLEGRO_KEY_PAD_4:
                    if (ch_sq.p2 < 10)
                        ch_sq.p2 = ch_sq.p2 + 10;   
                break;
                case ALLEGRO_KEY_PAD_5:
                    if (ch_sq.p2 >= 10)
                        ch_sq.p2 = ch_sq.p2 - 10;   
                break;
                
                default: break;
            }    
        } 
        
        al_wait_for_event(queue, &event);
    }
    
     /*load dos personagens*/
    if (ch_sq.p1 % 10 == 0) {
        load_s_magal(p1_sprites);
        
        *player1 = create_s_magal(0, max_x, max_y, p1_sprites[0]);
    } else if (ch_sq.p1 % 10 == 1) {
        load_j_thompson(p1_sprites);
        
        *player1 = create_j_thomp(0, max_x, max_y, p1_sprites[0]);
    }
        
    if (ch_sq.p2 % 10 == 0) {
        load_s_magal(p2_sprites);
        
        *player2 = create_s_magal(1, max_x, max_y, p2_sprites[0]);
    } else if (ch_sq.p2 % 10 == 1) {
        load_j_thompson(p2_sprites);
        
        *player2 = create_j_thomp(1, max_x, max_y, p2_sprites[0]);
    } 
    
    return 0;
}

void destroy_chr_bitmaps(ALLEGRO_BITMAP **chrs) {
    for (int i = 0; i < 2; i++)
        al_destroy_bitmap(chrs[i]);
    
    return;
}
