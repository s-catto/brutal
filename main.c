#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>	

#include "include/joystick.h"
#include "include/box.h"

#include "include/mano.h"
#include "include/personagens.h"

#include "include/menu.h"
#include "include/chselect.h"

#define MENU    0
#define CHSEL   1
#define GAME    2
#define OVER    3

/*definindo aspecto da tela 4:3*/
#define X_SCREEN 1000
#define Y_SCREEN ((X_SCREEN / 4) * 3)

/*define onde os personagens "pisam"*/
#define GROUND  20
#define GRAVITY -4

/*definindo tipos de colisão*/
#define NORMAL  0
#define HIT_P1  1
#define HIT_P2  2

int collision (mano* player1, mano* player2, int tipo) {
    if (tipo == NORMAL) {
        if ((((player1->x + player1->hit->x + player1->hit->width/2 > 
               player2->x + player2->hit->x - player2->hit->width/2) && 
              (player1->x + player1->hit->x - player1->hit->width/2 <= 
               player2->x + player2->hit->x - player2->hit->width/2)) 
            || 
            ((player2->x + player2->hit->x + player2->hit->width/2 > 
              player1->x + player2->hit->x - player1->hit->width/2) &&
             (player2->x + player2->hit->x - player2->hit->width/2 <= 
              player1->x + player1->hit->x - player1->hit->width/2)))
            &&
            (((player1->y + player1->hit->y > 
               player2->y + player2->hit->y - player2->hit->height) &&
             (player1->y + player1->hit->y - player1->hit->height <= 
              player2->y + player2->hit->y - player2->hit->height)) 
            || 
            ((player2->y + player2->hit->y > 
              player1->y + player1->hit->y - player1->hit->height) &&
             (player2->y + player2->hit->y - player2->hit->height <= 
              player1->y + player1->hit->y - player1->hit->height))))
        {return 1;}
    } else if (tipo == HIT_P1) {
        if ((((player1->x + player1->hit->x + player1->hit->width/2 > 
               player2->x + player2->hurt->x - player2->hurt->width/2) && 
              (player1->x + player1->hit->x - player1->hit->width/2 <= 
               player2->x + player2->hurt->x - player2->hurt->width/2)) 
            || 
            ((player2->x + player2->hurt->x + player2->hurt->width/2 > 
              player1->x + player2->hurt->x - player1->hit->width/2) &&
             (player2->x + player2->hurt->x - player2->hurt->width/2 <= 
              player1->x + player1->hit->x - player1->hit->width/2)))
            &&
            (((player1->y + player1->hit->y > 
               player2->y + player2->hurt->y - player2->hurt->height) &&
             (player1->y + player1->hit->y - player1->hit->height <= 
              player2->y + player2->hurt->y - player2->hurt->height)) 
            || 
            ((player2->y + player2->hurt->y > 
              player1->y + player1->hit->y - player1->hit->height) &&
             (player2->y + player2->hurt->y - player2->hurt->height <= 
              player1->y + player1->hit->y - player1->hit->height))))
        {return 1;}          
    } else if (tipo == HIT_P2) {
        if ((((player1->x + player1->hurt->x + player1->hurt->width/2 > 
               player2->x + player2->hit->x - player2->hit->width/2) && 
              (player1->x + player1->hurt->x - player1->hurt->width/2 <= 
               player2->x + player2->hit->x - player2->hit->width/2)) 
            || 
            ((player2->x + player2->hit->x + player2->hit->width/2 > 
              player1->x + player2->hit->x - player1->hurt->width/2) &&
             (player2->x + player2->hit->x - player2->hit->width/2 <= 
              player1->x + player1->hurt->x - player1->hurt->width/2)))
            &&
            (((player1->y + player1->hurt->y > 
               player2->y + player2->hit->y - player2->hit->height) &&
             (player1->y + player1->hurt->y - player1->hurt->height <= 
              player2->y + player2->hit->y - player2->hit->height)) 
            || 
            ((player2->y + player2->hit->y > 
              player1->y + player1->hurt->y - player1->hurt->height) &&
             (player2->y + player2->hit->y - player2->hit->height <= 
              player1->y + player1->hurt->y - player1->hurt->height))))
        {return 1;}
    }
    
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
            if (player->y + player->hit->y == Y_SCREEN - GROUND) {
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
    if (collision(player1, player2, NORMAL)) {
        if (player1->y + player1->hit->y < player2->y + player2->hit->y) {
            player1->y = player2->y + player2->hit->y - player2->hit->height 
                         - player1->hit->y;
        } else {
            player2->y = player1->y + player1->hit->y - player1->hit->height 
                         - player2->hit->y; 
        }
    }
    
    switch (player1->state)
    {
        case WALKL:
            mano_move(player1, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player1, -1, 0, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case WALKR:
            mano_move(player1, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player1, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case AIRBORNE:
            mano_move(player1, 1, 2, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2, NORMAL)) {
                mano_move(player1, -1, 2, X_SCREEN, Y_SCREEN-GROUND);
                player1->vy = 0;
            } else
                player1->vy = player1->vy + GRAVITY;
                
            if (player1->control->left && !player1->control->right) {
                mano_move(player1, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player1, -1, 0, X_SCREEN, Y_SCREEN-GROUND); 
            } else if (player1->control->right) {
                mano_move(player1, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player1, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            }
            
            break;
            
        default: break;
    }
    
    switch (player2->state)
    {
        case WALKL:
            mano_move(player2, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player2, -1, 0, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case WALKR:
            mano_move(player2, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player2, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            break;
            
        case AIRBORNE:
            mano_move(player2, 1, 2, X_SCREEN, Y_SCREEN-GROUND);
            if (collision(player1, player2, NORMAL)) {
                mano_move(player2, -1, 2, X_SCREEN, Y_SCREEN-GROUND);
                player2->vy = 0;
            } else {
                player2->vy = player2->vy + GRAVITY;
            }
            
            if (player2->control->left && !player2->control->right) {
                mano_move(player2, 1, 0, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player2, -1, 0, X_SCREEN, Y_SCREEN-GROUND); 
            } else if (player2->control->right) {
                mano_move(player2, 1, 1, X_SCREEN, Y_SCREEN-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player2, -1, 1, X_SCREEN, Y_SCREEN-GROUND);
            }
                
            break;
            
        default: break;
    }
    
    return;
}

void showGame (ALLEGRO_FONT *font, mano* player1, mano* player2) {
    /*provisorio, ceu e chao*/
    al_clear_to_color(al_map_rgb(135, 206, 250));
    al_draw_filled_rectangle(0, Y_SCREEN - GROUND, X_SCREEN, Y_SCREEN,
                             al_map_rgb(0, 255, 0));	
     
    /*posiscionando os elementos*/
    /*hitbox p1*/
    al_draw_filled_rectangle(player1->x + player1->hit->x - player1->hit->width/2, 
                             player1->y + player1->hit->y - player1->hit->height, 
                             player1->x + player1->hit->x + player1->hit->width/2, 
                             player1->y + player1->hit->y,
                             al_map_rgb(255, 0, 0));
    /*player1*/
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
    
    /*hitbox player2*/
    al_draw_filled_rectangle(player2->x + player2->hit->x - player2->hit->width/2, 
                             player2->y + player2->hit->y - player2->hit->height, 
                             player2->x + player2->hit->x + player2->hit->width/2, 
                             player2->y + player2->hit->y,
                             al_map_rgb(0, 0, 255));
                             
    /*player 2*/
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
    
    /*barras de saude =============================== */
    /*PLAYER 1 ===============*/
    /*nome*/
    al_draw_text(font, al_map_rgb(0, 0, 0), 160, 75, ALLEGRO_ALIGN_LEFT, player1->name); 
    
    /*barra saude*/
    al_draw_filled_rectangle(160, 20, 160 + player1->health*33/10, 70, al_map_rgb(0, 255, 0));
    /*barra borda*/
    al_draw_rectangle(160, 20, 490, 70, al_map_rgb(204, 204, 0), 6);
    
    
    /*borda foto*/
    al_draw_filled_rectangle(45, 5, 155, 115, al_map_rgb(204, 204, 0));
    /*fundo foto*/
    al_draw_filled_rectangle(52, 12, 148, 108, al_map_rgb(255, 0, 0));
    /*foto*/
    al_draw_scaled_bitmap(player1->sq_sprite, 0, 0, 24, 24, 52, 12, 96, 96, 0);
    
    
    /*PLAYER 2 ===============*/
    /*nome*/
    al_draw_text(font, al_map_rgb(0, 0, 0), X_SCREEN -160, 75, ALLEGRO_ALIGN_RIGHT, player2->name); 
    
    /*barra saude*/
    al_draw_filled_rectangle(X_SCREEN -160 - player2->health*33/10, 20, X_SCREEN -160, 70, al_map_rgb(0, 255, 0));
    /*barra borda*/
    al_draw_rectangle(X_SCREEN -490, 20, X_SCREEN -160, 70, al_map_rgb(204, 204, 0), 6);
    
    /*borda foto*/
    al_draw_filled_rectangle(X_SCREEN -155, 5, X_SCREEN -45, 115, al_map_rgb(204, 204, 0));
    /*fundo foto p2*/
    al_draw_filled_rectangle(X_SCREEN -148, 12, X_SCREEN -52, 108, al_map_rgb(0, 0, 255));
    /*foto p2*/
    al_draw_scaled_bitmap(player2->sq_sprite, 0, 0, 24, 24, X_SCREEN -52, 12, -96, 96, 0);    
        
    /*update do display*/
    al_flip_display();
    
    return;
}

int main(){
    al_init();	
    al_init_primitives_addon();
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_image_addon();
    
    al_install_keyboard();
	
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN);
    
    ALLEGRO_FONT* font = al_load_font("./fonts/gameboy.ttf", 20, 0);
    if (!font) {
      printf("Error loading ./fonts/gameboy.ttf\n");
      return 2;
    }
	
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    ALLEGRO_EVENT event;
    al_start_timer(timer);
    al_wait_for_event(queue, &event);
    
    int close_display = 0;
    int tela = MENU;
    
    mano* player1 = NULL;
    ALLEGRO_BITMAP* p1_sprites[6];
    mano* player2 = NULL;
    ALLEGRO_BITMAP* p2_sprites[6];

    while (1) {	
        switch (tela)
        {
            case MENU:
                close_display = menu(queue, X_SCREEN, Y_SCREEN); 
                if (close_display)
                    break;
                tela = CHSEL;
            break;
            case CHSEL:
                close_display = ch_select(queue, X_SCREEN, Y_SCREEN, 
                          p1_sprites, p2_sprites, &player1, &player2);
                if(close_display)
                    break;
       
                if (!player1)
                    return 1;
                if (!player2)
                    return 2;    
                    
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
                        
                        showGame(font, player1, player2);
                    }
                    /*tecla pressionada ou solta*/
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
                
                if (event.type == 42)
                    close_display = 1;
            
            break;
            default: return 3;
        }
        if (close_display) break;
        
        al_wait_for_event(queue, &event);              	
    }
    
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return 0;
}
