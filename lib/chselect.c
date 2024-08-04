#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>

#include "../include/mano.h"
#include "../include/personagens.h"
#include "../include/chselect.h"

void load_chr_bitmaps(ALLEGRO_BITMAP **chrs) {
    chrs[0] = al_load_bitmap(CH_S_MAGAL); 
    chrs[1] = al_load_bitmap(CH_J_THOMP); 
    chrs[3] = al_load_bitmap(CH_M_TOSTX);  
    
    return;
}

int ch_select (ALLEGRO_FONT* font, ALLEGRO_EVENT_QUEUE* queue, int max_x, int max_y,
               ALLEGRO_BITMAP** p1_sprites, ALLEGRO_BITMAP** p2_sprites,
               mano** player1, mano** player2, int bot, ALLEGRO_BITMAP** cenario) {
    
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    
    character_square ch_sq;
    load_chr_bitmaps(ch_sq.chrs);
    
    ch_sq.cores[0] = COR_P1;
    ch_sq.cores[1] = COR_P2;
    ch_sq.cores[2] = COR_UNSEL;
    ch_sq.cores[3] = COR_UNSEL;
    
    ch_sq.p1 = 0;
    ch_sq.p2 = 1;
    
    int selected = 0;
    int sel_cen = 0;
    
    while (event.type != 42 && !selected) {
        if (event.type == 30) {
            al_clear_to_color(al_map_rgb(69, 75, 27));
            
            al_draw_filled_rectangle( GRID_X1, GRID_Y1, GRID_X2, GRID_Y2, al_map_rgb(0,0,0));
            al_draw_filled_rectangle( SQ1_X1, SQ1_Y1, SQ1_X2, SQ1_Y2, ch_sq.cores[0]);
            al_draw_scaled_bitmap(ch_sq.chrs[0], 0, 0, 24, 24, SQ1_X1, SQ1_Y1, 120, 120, 0);
            al_draw_filled_rectangle( SQ2_X1, SQ2_Y1, SQ2_X2, SQ2_Y2, ch_sq.cores[1]);
            al_draw_scaled_bitmap(ch_sq.chrs[1], 0, 0, 24, 24, SQ2_X1, SQ2_Y1, 120, 120, 0);
            al_draw_filled_rectangle( SQ3_X1, SQ3_Y1, SQ3_X2, SQ3_Y2, ch_sq.cores[2]);
            al_draw_filled_rectangle( SQ4_X1, SQ4_Y1, SQ4_X2, SQ4_Y2, ch_sq.cores[3]);
            al_draw_scaled_bitmap(ch_sq.chrs[3], 0, 0, 24, 24, SQ4_X1, SQ4_Y1, 120, 120, 0);
            
            if (sel_cen == S_CASA) {
                al_draw_text(font, al_map_rgb(0, 0, 0), 500, max_y - 164, ALLEGRO_ALIGN_CENTER, "CASA DO JOREL");   
            } else if (sel_cen == S_LOCA) {
                al_draw_text(font, al_map_rgb(0, 0, 0), 500, max_y - 164, ALLEGRO_ALIGN_CENTER, "ULTIMA VIDEOLOCADORA DO MUNDO");
            } else {
                al_draw_text(font, al_map_rgb(0, 0, 0), 500, max_y - 164, ALLEGRO_ALIGN_CENTER, "LOJA DE DISCOS DO REGINALDO");
            }
            
            
            if (bot) {
                al_draw_text(font, al_map_rgb(0, 255, 0), 500, max_y - 124, ALLEGRO_ALIGN_CENTER, "STEVE MAGAL DO FUTURO");
            } else {
                al_draw_text(font, al_map_rgb(0, 0, 0), 500, max_y - 124, ALLEGRO_ALIGN_CENTER, "STEVE MAGAL DO FUTURO");
            }   
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
                
                case ALLEGRO_KEY_B: 
                    bot = bot ^ 1;
                break;
                
                case ALLEGRO_KEY_C:
                    sel_cen = (sel_cen + 1) % 3;
                break; 
                
                case ALLEGRO_KEY_ENTER: 
                    selected = 1;
                break;
                
                default: break;
            }    
        } 
        
        al_wait_for_event(queue, &event);
    }
    
     /*load dos personagens*/
    if (ch_sq.p1 == 0) {
        load_s_magal(p1_sprites);
        
        *player1 = create_s_magal(0, max_x, max_y, p1_sprites[0], ch_sq.chrs[0]);
    } else if (ch_sq.p1 == 1) {
        load_j_thompson(p1_sprites);
        
        *player1 = create_j_thomp(0, max_x, max_y, p1_sprites[0], ch_sq.chrs[1]);
    } else if (ch_sq.p1 == 3) {
        load_mwv_tostex(p1_sprites);
        
        *player1 = create_m_tostx(0, max_x, max_y, p1_sprites[0], ch_sq.chrs[3]);
    }
        
    if (ch_sq.p2 == 0) {
        load_s_magal(p2_sprites);
        
        *player2 = create_s_magal(1, max_x, max_y, p2_sprites[0], ch_sq.chrs[0]);
    } else if (ch_sq.p2 == 1) {
        load_j_thompson(p2_sprites);
        
        *player2 = create_j_thomp(1, max_x, max_y, p2_sprites[0], ch_sq.chrs[1]);
    } else if (ch_sq.p2 == 3) {
        load_mwv_tostex(p2_sprites);
        
        *player2 = create_m_tostx(1, max_x, max_y, p2_sprites[0], ch_sq.chrs[3]);
    }
    
    /*load do cenário*/
    
    if (sel_cen == S_CASA) {
        *cenario = al_load_bitmap(CASA);
    } else if (sel_cen == S_LOCA) {
        *cenario = al_load_bitmap(LOCA);
    } else {
        *cenario = al_load_bitmap(LOJA);
    }
    
    if (event.type == 42)
        return 1;
    
    return 0;
}

void destroy_chr_bitmaps(ALLEGRO_BITMAP **chrs) {
    for (int i = 0; i < 4; i++)
        al_destroy_bitmap(chrs[i]);
    
    return;
}
