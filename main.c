#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>	

#include "joystick.h"
#include "box.h"

#include "mano.h"
#include "personagens.h"

#include "menu.h"
#include "chselect.h"

#define MENU    0
#define CHSEL   1
#define GAME    2
#define OVER    3

/*definindo aspecto da tela 4:3*/
#define X_SCREEN 1000
#define Y_SCREEN ((X_SCREEN / 4) * 3)


/*define onde os personagens "pisam"*/
#define GROUND  20
#define GRAVITY -1

int collision (mano* player1, mano* player2) {
    if ((((player1->x + player1->coli->x + player1->coli->width/2 > 
           player2->x + player2->coli->x - player2->coli->width/2) && 
          (player1->x + player1->coli->x - player1->coli->width/2 <= 
           player2->x + player2->coli->x - player2->coli->width/2)) 
        || 
        ((player2->x + player2->coli->x + player2->coli->width/2 > 
          player1->x + player2->coli->x - player1->coli->width/2) &&
         (player2->x + player2->coli->x - player2->coli->width/2 <= 
          player1->x + player1->coli->x - player1->coli->width/2)))
        &&
        (((player1->y + player1->coli->y > 
           player2->y + player2->coli->y - player2->coli->height) &&
         (player1->y + player1->coli->y - player1->coli->height <= 
          player2->y + player2->coli->y - player2->coli->height)) 
        || 
        ((player2->y + player2->coli->y > 
          player1->y + player1->coli->y - player1->coli->height) &&
         (player2->y + player2->coli->y - player2->coli->height <= 
          player1->y + player1->coli->y - player1->coli->height))))
    {return 1;}
    
    return 0;
}

void update_facing_dir (mano* p1, mano* p2) {
    if (p1->x > p2->x) {
        p1->spr_sett->face = LEFT;
        p2->spr_sett->face = RIGHT;
        return;
    }
    
    p1->spr_sett->face = RIGHT;
    p2->spr_sett->face = LEFT;
    
    return;
}

void update_state (mano* player, ALLEGRO_BITMAP* sprites[4]) {
    switch (player->state)
    {
        case STAND:
            if (player->control->up) {
                player->sprite = sprites[2];
                player->state = JUMP;
            } else if (player->control->down) {
                player->sprite = sprites[3];
                mano_crouch(player);
                player->state = CROUCH;
            } else if (player->control->left) {
                if (!player->control->right) {
                    player->sprite = sprites[1];
                    player->state = WALKL;
                }
            } else if (player->control->right) {
                player->sprite = sprites[1];
                player->state = WALKR;
            }
            break;
            
        case CROUCH:
            if (!player->control->down) {    
                player->sprite = sprites[0];
                mano_uncrouch(player);
                player->state = STAND;
            }
            break;
            
        case JUMP:
            mano_jump(player);
            player->state = AIRBORNE;
            break;
            
        case AIRBORNE:
            if (player->y + player->coli->y == Y_SCREEN - GROUND) {
                player->sprite = sprites[0];
                player->state = STAND;
                player->vy = 0;
            }
            break;
            
        case WALKL:
            if (player->control->up) {
                player->sprite = sprites[2];
                player->state = JUMP;
            } else if (player->control->down) {
                player->sprite = sprites[3];
                mano_crouch(player);
                player->state = CROUCH;
            } else if (!player->control->left || player->control->right) {
                player->sprite = sprites[0];
                player->state = STAND;
            }
            break;
        
        case WALKR:
            if (player->control->up) {
                player->sprite = sprites[2];
                player->state = JUMP;
            } else if (player->control->down) {
                player->sprite = sprites[3];
                mano_crouch(player);
                player->state = CROUCH;
            } else if (!player->control->right || player->control->left) {
                player->sprite = sprites[0];
                player->state = STAND;
            }
            break; 
        
        default: break;
    }
    
    return;       
}

void update_position (mano* player1, mano* player2) {
    if (collision(player1, player2)) {
        if (player1->y + player1->coli->y < player2->y + player2->coli->y) {
            player1->y = player2->y + player2->coli->y - player2->coli->height 
                         - player1->coli->y;
        } else {
            player2->y = player1->y + player1->coli->y - player1->coli->height 
                         - player2->coli->y; 
        }
    }
    
    switch (player1->state)
    {
        case WALKL:
            mano_move(player1, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2))
                mano_move(player1, -1, 0, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case WALKR:
            mano_move(player1, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2))
                mano_move(player1, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case AIRBORNE:
            mano_move(player1, 1, 2, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2)) {
                mano_move(player1, -1, 2, X_SCREEN, Y_SCREEN-GROUND);
                player1->vy = 0;
            } else
                player1->vy = player1->vy -1;
                
            if (player1->control->left && !player1->control->right) {
                mano_move(player1, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2))
                    mano_move(player1, -1, 0, X_SCREEN, Y_SCREEN-GROUND); 
            } else if (player1->control->right) {
                mano_move(player1, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2))
                    mano_move(player1, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            }
            
            break;
            
        default: break;
    }
    
    switch (player2->state)
    {
        case WALKL:
            mano_move(player2, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2))
                mano_move(player2, -1, 0, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case WALKR:
            mano_move(player2, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2))
                mano_move(player2, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case AIRBORNE:
            mano_move(player2, 1, 2, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2)) {
                mano_move(player2, -1, 2, X_SCREEN, Y_SCREEN-GROUND);
                player2->vy = 0;
            } else {
                player2->vy = player2->vy -1;
            }
            
            if (player2->control->left && !player2->control->right) {
                mano_move(player2, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2))
                    mano_move(player2, -1, 0, X_SCREEN, Y_SCREEN-GROUND); 
            } else if (player2->control->right) {
                mano_move(player2, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2))
                    mano_move(player2, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            }
                
            break;
            
        default: break;
    }
    
    return;
}

int main(){
    al_init();	
    al_init_primitives_addon();
    al_init_image_addon();
    
    al_install_keyboard();
	
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN);
	
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    ALLEGRO_EVENT event;
    al_start_timer(timer);
    al_wait_for_event(queue, &event);
    
    int i;
    int trans = 0;
    
    int tela = MENU;
    ALLEGRO_BITMAP* menu[22];
    
    character_square ch_sq;
    
    mano* player1 = NULL;
    ALLEGRO_BITMAP* p1_sprites[4];
    mano* player2 = NULL;
    ALLEGRO_BITMAP* p2_sprites[4];

    while (1) {	
        switch (tela)
        {
            case MENU: 
                load_menu(menu);
                i = 0;
                while (event.type != 42 && !trans) {
                    if (event.type == 30) {    
                        al_clear_to_color(al_map_rgb(69, 75, 27));
                        i = animate_menu(menu, 0, 9, i);
                        al_draw_scaled_bitmap(menu[21], 0, 0, 80, 7, 
	                                              340, Y_SCREEN - 84, 
	                                              320, 28, 0);
                        al_flip_display(); 
                    }
                    else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                        switch (event.keyboard.keycode)
                        {
                            case ALLEGRO_KEY_ENTER:
                                trans = 1;
                                tela = CHSEL;
                            break;
                            
                            default: break;
                        }
                    }
                    al_wait_for_event(queue, &event); 
                }
                while (trans && event.type != 42) {
                    if (event.type == 30) {
                        al_clear_to_color(al_map_rgb(69, 75, 27));
                        trans = animate_menu(menu, 10, 20, trans);
                        al_flip_display(); 
                    }      
                    al_wait_for_event(queue, &event);
                } 
                destroy_menu(menu);
            break;
            case CHSEL:
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
                    
                    player1 = create_s_magal(0, X_SCREEN, Y_SCREEN, p1_sprites[0]);
                    if (!player1)
                        return 1;
                } else if (ch_sq.p1 % 10 == 1) {
                    load_j_thompson(p1_sprites);
                    
                    player1 = create_j_thomp(0, X_SCREEN, Y_SCREEN, p1_sprites[0]);
                    if (!player1)
                        return 2;    
                }
                    
                if (ch_sq.p2 % 10 == 0) {
                    load_s_magal(p2_sprites);
                    
                    player2 = create_s_magal(1, X_SCREEN, Y_SCREEN, p2_sprites[0]);
                    if (!player2)
                        return 1;
                } else if (ch_sq.p2 % 10 == 1) {
                    load_j_thompson(p2_sprites);
                    
                    player2 = create_j_thomp(1, X_SCREEN, Y_SCREEN, p2_sprites[0]);
                    if (!player2)
                        return 2;    
                }  
                    
                tela = GAME;  
            break;
            case GAME:
                while (event.type != 42) {        
                    /*batida do clock*/
                    if (event.type ==  30) {
                        update_facing_dir(player1, player2);
                        update_state(player1, p1_sprites);
                        update_state(player2, p2_sprites);
                        update_position(player1, player2);
                        
                        al_clear_to_color(al_map_rgb(135, 206, 250));
                        al_draw_filled_rectangle(0, Y_SCREEN - GROUND, X_SCREEN, Y_SCREEN,
	                                             al_map_rgb(0, 255, 0));	
                         
                        /*posiscionando os elementos*/
	                    al_draw_filled_rectangle(player1->x + player1->coli->x - player1->coli->width/2, 
	                                             player1->y + player1->coli->y - player1->coli->height, 
	                                             player1->x + player1->coli->x + player1->coli->width/2, 
	                                             player1->y + player1->coli->y,
	                                             al_map_rgb(255, 0, 0));
	                    if (player1->spr_sett->face == RIGHT) {
	                        al_draw_scaled_bitmap(player1->sprite, 0, 0, 64, 64, 
	                                              player1->x + player1->spr_sett->x_R, 
	                                              player1->y-player1->height -64, 
	                                              384, 384, 0);
	                    } else {
	                        al_draw_scaled_bitmap(player1->sprite, 0, 0, 64, 64, 
	                                              player1->x + player1->spr_sett->x_L, 
	                                              player1->y-player1->height -64, 
	                                              -384, 384, 0);
	                    }
                        al_draw_filled_rectangle(player2->x + player2->coli->x - player2->coli->width/2, 
                                                 player2->y + player2->coli->y - player2->coli->height, 
	                                             player2->x + player2->coli->x + player2->coli->width/2, 
	                                             player2->y + player2->coli->y,
	                                             al_map_rgb(0, 0, 255));
	                                             
	                    if (player2->spr_sett->face == RIGHT) {
	                        al_draw_scaled_bitmap(player2->sprite, 0, 0, 64, 64, 
	                                              player2->x + player2->spr_sett->x_R, 
	                                              player2->y-player2->height -64, 
	                                              384, 384, 0);
	                    } else {
	                        al_draw_scaled_bitmap(player2->sprite, 0, 0, 64, 64, 
	                                              player2->x + player2->spr_sett->x_L, 
	                                              player2->y-player2->height -64, 
	                                              -384, 384, 0);
	                    }
                            
                        /*update do display*/
                        al_flip_display();
                    }
                    /*tecla pressionada/solta*/
                    else if (event.type == ALLEGRO_EVENT_KEY_DOWN || event.type == ALLEGRO_EVENT_KEY_UP) {
                        switch (event.keyboard.keycode)
                        {
                            case ALLEGRO_KEY_A: joystick_left(player1->control); break;
                            case ALLEGRO_KEY_D: joystick_right(player1->control); break;
                            case ALLEGRO_KEY_W: joystick_up(player1->control); break;
                            case ALLEGRO_KEY_S: joystick_down(player1->control); break;
                            
                            case ALLEGRO_KEY_LEFT: joystick_left(player2->control); break;
                            case ALLEGRO_KEY_RIGHT: joystick_right(player2->control); break;
                            case ALLEGRO_KEY_UP: joystick_up(player2->control); break;
                            case ALLEGRO_KEY_DOWN: joystick_down(player2->control); break;
                            
                            default: break;
                        }    
                    } 
                    al_wait_for_event(queue, &event); 
                }
                
                mano_destroy(player1);
                destroy_sprites(p1_sprites);
                mano_destroy(player2);
                destroy_sprites(p2_sprites);
            
            break;
            default: return 3;
        }
        if (event.type == 42) break;
        
        al_wait_for_event(queue, &event);              	
    }
    
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return 0;
}
