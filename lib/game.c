#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>	
#include <time.h>

#include "../include/joystick.h"
#include "../include/box.h"

#include "../include/mano.h"
#include "../include/personagens.h"

#include "../include/game.h"

int collision (mano* player1, mano* player2, int tipo) {
    if (tipo == NORMAL) {
        if ((((player1->x + player1->hit->x + player1->hit->width/2 >   /*colisão horizontal*/
               player2->x + player2->hit->x - player2->hit->width/2) && /*p1 na esquerda*/
              (player1->x + player1->hit->x - player1->hit->width/2 <= 
               player2->x + player2->hit->x - player2->hit->width/2)) 
            || 
            ((player2->x + player2->hit->x + player2->hit->width/2 > 
              player1->x + player2->hit->x - player1->hit->width/2) &&  /*p1 na direita*/
             (player2->x + player2->hit->x - player2->hit->width/2 <= 
              player1->x + player1->hit->x - player1->hit->width/2)))
            &&
            (((player1->y + player1->hit->y >                           /*colisão vertical*/
               player2->y + player2->hit->y - player2->hit->height) &&  /*p1 em cima*/
             (player1->y + player1->hit->y - player1->hit->height <= 
              player2->y + player2->hit->y - player2->hit->height)) 
            || 
            ((player2->y + player2->hit->y > 
              player1->y + player1->hit->y - player1->hit->height) &&   /*p1 em baixo*/
             (player2->y + player2->hit->y - player2->hit->height <= 
              player1->y + player1->hit->y - player1->hit->height))))
        {return 1;}
    } else if (tipo == HIT_P1) {
        if ((((player1->x + player1->hit->x + player1->hit->width/2 >       /*segue o padrão*/
               player2->x + player2->hurt->x - player2->hurt->width/2) &&   /*com a hurtbox do p2*/
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
        if ((((player1->x + player1->hurt->x + player1->hurt->width/2 >     /*segue o padrão*/
               player2->x + player2->hit->x - player2->hit->width/2) &&     /*com a hurtbox do p1*/
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
    } else {
        if ((((player1->x + player1->hit->x + player1->hit->width/2 >   /*só testa colisão horizontal*/
               player2->x + player2->hit->x - player2->hit->width/2) && 
              (player1->x + player1->hit->x - player1->hit->width/2 <= 
               player2->x + player2->hit->x - player2->hit->width/2)) 
            || 
            ((player2->x + player2->hit->x + player2->hit->width/2 > 
              player1->x + player2->hit->x - player1->hit->width/2) &&
             (player2->x + player2->hit->x - player2->hit->width/2 <= 
              player1->x + player1->hit->x - player1->hit->width/2))))
        {return 1;}
    }
    
    return 0;
}

void update_facing_dir (mano* p1, mano* p2) {
    if (p1->x > p2->x) {
        p1->face = LEFT;
        p2->face = RIGHT;
        return;
    }
    
    p1->face = RIGHT;
    p2->face = LEFT;
    
    return;
}

void update_state (mano* player, ALLEGRO_BITMAP* sprites[6], int max_y) {
    if (player->cont < 0)
        player->cont++;
    switch (player->state)
    {
        case STAND:
            if (player->control->up) {
                player->sprite = sprites[JMP];
                player->state = JUMP;
            } else if (player->control->down) {
                player->sprite = sprites[CRH];
                mano_crouch(player);
                player->state = CROUCH;
            } else if (player->control->punch) {
                if (player->cont == 0) {
                    player->sprite = sprites[PUN];
                    mano_punch(player);
                    player->cont = 7;
                    player->state = ATTACK;
                    player->attk_state = PUNCH;
                }
            } else if (player->control->kick) {
                 if (player->cont == 0) {
                    player->sprite = sprites[KIK];
                    mano_kick(player);
                    player->cont = 7;
                    player->state = ATTACK;
                    player->attk_state = KICK; 
                 }   
            } else if (player->control->left) {
                if (!player->control->right) {
                    player->sprite = sprites[WLK];
                    player->state = WALKL;
                }
            } else if (player->control->right) {
                player->sprite = sprites[WLK];
                player->state = WALKR;
            }
            break;
            
        case CROUCH:
            if (!player->control->down) {    
                player->sprite = sprites[STD];
                mano_uncrouch(player);
                player->state = STAND;
            }
            break;
            
        case JUMP:
            mano_jump(player);
            player->state = AIRBORNE;
            break;
            
        case AIRBORNE:
            if (player->y + player->hit->y == max_y - GROUND) {
                player->sprite = sprites[STD];
                player->state = STAND;
                player->vy = 0;
            }
            break;
            
        case WALKL:
            if (player->control->punch) {
                if (player->cont == 0) {
                    player->sprite = sprites[PUN];
                    mano_punch(player);
                    player->cont = 7;
                    player->state = ATTACK;
                    player->attk_state = PUNCH;
                }
            } else if (player->control->kick) {
                if (player->cont == 0) {
                    player->sprite = sprites[KIK];
                    mano_kick(player);
                    player->cont = 7;
                    player->state = ATTACK;
                    player->attk_state = KICK;   
                } 
            } else if (player->control->up) {
                player->sprite = sprites[JMP];
                player->state = JUMP;
            } else if (player->control->down) {
                player->sprite = sprites[CRH];
                mano_crouch(player);
                player->state = CROUCH;
            } else if (!player->control->left || player->control->right) {
                player->sprite = sprites[STD];
                player->state = STAND;
            } 
            break;
        
        case WALKR:
            if (player->control->punch) {
                if (player->cont == 0) {
                    player->sprite = sprites[PUN];
                    mano_punch(player);
                    player->cont = 7;
                    player->state = ATTACK;
                    player->attk_state = PUNCH;
                }
            } else if (player->control->kick) {
                if (player->cont == 0) {
                    player->sprite = sprites[KIK];
                    mano_kick(player);
                    player->cont = 7;
                    player->state = ATTACK;
                    player->attk_state = KICK; 
                }   
            } else if (player->control->up) {
                player->sprite = sprites[JMP];
                player->state = JUMP;
            } else if (player->control->down) {
                player->sprite = sprites[CRH];
                mano_crouch(player);
                player->state = CROUCH;
            } else if (!player->control->right || player->control->left) {
                player->sprite = sprites[STD];
                player->state = STAND;
            }
            break; 
            
        case ATTACK:
            if (player->cont < 1) {
                player->cont = -10;
             
                player->attk_state = NONE;
                mano_peace(player);
                 
                if (player->control->up) {
                    player->sprite = sprites[JMP];
                    player->state = JUMP;
                } else if (player->control->down) {
                    player->sprite = sprites[CRH];
                    mano_crouch(player);
                    player->state = CROUCH;
                } else {
                    player->sprite = sprites[STD];
                    player->state = STAND;
                }
            }
            player->cont--;
            break;
        
        
        default: break;
    }
    
    return;       
}

void update_position (mano* player1, mano* player2, int max_x, int max_y) {
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
            mano_move(player1, 1, 0, max_x, max_y-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player1, -1, 0, max_x, max_y-GROUND);
            break;
            
        case WALKR:
            mano_move(player1, 1, 1, max_x, max_y-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player1, -1, 1, max_x, max_y-GROUND);
            break;
            
        case AIRBORNE:
            mano_move(player1, 1, 2, max_x, max_y-GROUND);
            if (collision(player1, player2, NORMAL)) {
                mano_move(player1, -1, 2, max_x, max_y-GROUND);
                player1->vy = 0;
            } else
                player1->vy = player1->vy + GRAVITY;
                
            if (player1->control->left && !player1->control->right) {
                mano_move(player1, 1, 0, max_x, max_y-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player1, -1, 0, max_x, max_y-GROUND); 
            } else if (player1->control->right) {
                mano_move(player1, 1, 1, max_x, max_y-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player1, -1, 1, max_x, max_y-GROUND);
            }
            
            break;
            
        default: break;
    }
    
    switch (player2->state)
    {
        case WALKL:
            mano_move(player2, 1, 0, max_x, max_y-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player2, -1, 0, max_x, max_y-GROUND);
            break;
            
        case WALKR:
            mano_move(player2, 1, 1, max_x, max_y-GROUND);
            if (collision(player1, player2, NORMAL))
                mano_move(player2, -1, 1, max_x, max_y-GROUND);
            break;
            
        case AIRBORNE:
            mano_move(player2, 1, 2, max_x, max_y-GROUND);
            if (collision(player1, player2, NORMAL)) {
                mano_move(player2, -1, 2, max_x, max_y-GROUND);
                player2->vy = 0;
            } else {
                player2->vy = player2->vy + GRAVITY;
            }
            
            if (player2->control->left && !player2->control->right) {
                mano_move(player2, 1, 0, max_x, max_y-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player2, -1, 0, max_x, max_y-GROUND); 
            } else if (player2->control->right) {
                mano_move(player2, 1, 1, max_x, max_y-GROUND);
                if (collision(player1, player2, NORMAL))
                    mano_move(player2, -1, 1, max_x, max_y-GROUND);
            }
                
            break;
            
        default: break;
    }
    
    return;
}

void update_health (mano* player1, mano* player2) {
    if (collision(player1, player2, HIT_P1)) {
        player1->health = player1->health - 1;
    }
    
    if (collision(player1, player2, HIT_P2)) {
        player2->health = player2->health - 1;
    }
    
    return;
}

void update_keys (ALLEGRO_EVENT event, mano* player1, mano* player2, int bot, int* pause) {
    if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
        switch (event.keyboard.keycode)
        {
            case ALLEGRO_KEY_A: joystick_left(player1->control); break;
            case ALLEGRO_KEY_D: joystick_right(player1->control); break;
            case ALLEGRO_KEY_W: joystick_up(player1->control); break;
            case ALLEGRO_KEY_S: joystick_down(player1->control); break;
            
            case ALLEGRO_KEY_U: joystick_punch(player1->control); break;
            case ALLEGRO_KEY_I: joystick_kick(player1->control); break;
            
            default: break;
        }
        
        if (!bot) { 
            switch (event.keyboard.keycode)
            {   
                case ALLEGRO_KEY_LEFT: joystick_left(player2->control); break;
                case ALLEGRO_KEY_RIGHT: joystick_right(player2->control); break;
                case ALLEGRO_KEY_UP: joystick_up(player2->control); break;
                case ALLEGRO_KEY_DOWN: joystick_down(player2->control); break;
                
                case ALLEGRO_KEY_PAD_4: joystick_punch(player2->control); break;
                case ALLEGRO_KEY_PAD_5: joystick_kick(player2->control); break;
                
                default: break;
            }  
        }  
        
        if (event.keyboard.keycode == ALLEGRO_KEY_P) 
            *pause = 1;
            
    } else if (event.type == ALLEGRO_EVENT_KEY_UP) {
        switch (event.keyboard.keycode)
        {
            case ALLEGRO_KEY_A: joystick_unleft(player1->control); break;
            case ALLEGRO_KEY_D: joystick_unright(player1->control); break;
            case ALLEGRO_KEY_W: joystick_unup(player1->control); break;
            case ALLEGRO_KEY_S: joystick_undown(player1->control); break;
            
            case ALLEGRO_KEY_U: joystick_unpunch(player1->control); break;
            case ALLEGRO_KEY_I: joystick_unkick(player1->control); break;
            
            default: break;
        }
        
        if (!bot) { 
            switch (event.keyboard.keycode)
            {   
                case ALLEGRO_KEY_LEFT: joystick_unleft(player2->control); break;
                case ALLEGRO_KEY_RIGHT: joystick_unright(player2->control); break;
                case ALLEGRO_KEY_UP: joystick_unup(player2->control); break;
                case ALLEGRO_KEY_DOWN: joystick_undown(player2->control); break;
                
                case ALLEGRO_KEY_PAD_4: joystick_unpunch(player2->control); break;
                case ALLEGRO_KEY_PAD_5: joystick_unkick(player2->control); break;
                
                default: break;
            }  
        }
    }
    
    return;
}

void update_bot (mano* player1, mano* player2, int max_x) {
    if (collision(player1, player2, -1)) {
        if (player2->x - 0 < max_x - player2->x && player2->x >= player1->x) {
            if (player2->control->left)
                joystick_unleft(player2->control); 
            if (!player2->control->right)
                joystick_right(player2->control);
        } else {
            if (!player2->control->left)
                joystick_left(player2->control); 
            if (player2->control->right)
                joystick_unright(player2->control);
        } 
    } else {
        if (player2->face == LEFT) {
            if (player2->control->right)
                joystick_unright(player2->control);   
            if (!player2->control->left && player2->y >= player1->y - player1->height)
                joystick_left(player2->control);    
        } else {
            if (player2->control->left)
                joystick_unleft(player2->control); 
            if (!player2->control->right && player2->y >= player1->y - player1->height)
                joystick_right(player2->control);
        }
    }
    
    if (!player2->control->punch && !player2->control->kick && !player2->control->up && !player2->control->down) {
        switch (rand() % 4) {
            case 0:
                if (!(rand() % 17)) 
                    joystick_punch(player2->control);
            break;
            case 1:
                if (!(rand() % 17)) 
                    joystick_kick(player2->control);
            break;
            case 2:
                if (!(rand() % 23)) 
                    joystick_up(player2->control);
            break;
            case 3:
                if (!(rand() % 23)) 
                    joystick_down(player2->control);
            break;
            
            default: break;
        }
    } else {  
        if (player2->control->punch) {
            if (!(rand() % 11))
                joystick_unpunch(player2->control);
        } else if (player2->control->kick){
            if (!(rand() % 11))
                joystick_unkick(player2->control);
        } else if (player2->control->up){
            if (!(rand() % 7))
                joystick_unup(player2->control);
        } else {
            if (!(rand() % 11))
                joystick_undown(player2->control);   
        }
    }
    
    return;
}

void reset (mano* player1, ALLEGRO_BITMAP* sprite1, mano* player2, ALLEGRO_BITMAP* sprite2, int max_y) {
    /*reset health*/
    player1->health = 100;
    player2->health = 100;
    
    /*reset position and facing direction*/
    player1->x = player1->ini_x;
    player1->y = max_y;
    player2->x = player2->ini_x;
    player2->y = max_y;
    update_facing_dir(player1, player2);
    
    /*reset hurtbox*/ 
    mano_peace(player1);
    mano_peace(player2);
    
    /*reset hitbox height*/ 
    mano_uncrouch(player1);
    mano_uncrouch(player2);
    
    /*reset state*/
    player1->state = STAND;
    player2->state = STAND;
    player1->attk_state = NONE;
    player2->attk_state = NONE;
    player1->sprite = sprite1;
    player2->sprite = sprite2;
    player1->vy = 0;
    player2->vy = 0;
    player1->cont = 0;
    player2->cont = 0;
    
    joystick_reset(player1->control);
    joystick_reset(player2->control);
    
    return;
}

void showGame (ALLEGRO_FONT *font, mano* player1, mano* player2, ALLEGRO_BITMAP *sprok_pt, ALLEGRO_BITMAP* cenario, int max_x, int max_y) {
    
    /*cenario*/
    al_draw_scaled_bitmap(cenario, 0, 0, 832, 624, 0,0, 1000, 750, 0);
     
    /*posiscionando os elementos*/
    
    /*player1*/
    if (player1->face == RIGHT) {
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
                            
    
                             
    /*player 2*/
    if (player2->face == RIGHT) {
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
    
    /* pontos */
    if (player1->wins > 0) {
        al_draw_scaled_bitmap(sprok_pt, 0, 0, 4, 6, 160, 100, 24, 36, 0);
        if (player1->wins > 1)
            al_draw_scaled_bitmap(sprok_pt, 0, 0, 4, 6, 190, 100, 24, 36, 0);   
    }    
    /*PLAYER 2 ===============*/
    /*nome*/
    al_draw_text(font, al_map_rgb(0, 0, 0), max_x -160, 75, ALLEGRO_ALIGN_RIGHT, player2->name); 
    
    /*barra saude*/
    al_draw_filled_rectangle(max_x -160 - player2->health*33/10, 20, max_x -160, 70, al_map_rgb(0, 255, 0));
    /*barra borda*/
    al_draw_rectangle(max_x -490, 20, max_x -160, 70, al_map_rgb(204, 204, 0), 6);
    
    
    /*borda foto*/
    al_draw_filled_rectangle(max_x -155, 5, max_x -45, 115, al_map_rgb(204, 204, 0));
    /*fundo foto p2*/
    al_draw_filled_rectangle(max_x -148, 12, max_x -52, 108, al_map_rgb(0, 0, 255));
    /*foto p2*/
    al_draw_scaled_bitmap(player2->sq_sprite, 0, 0, 24, 24, max_x -52, 12, -96, 96, 0);    
    /* pontos */
    if (player2->wins > 0) {
        al_draw_scaled_bitmap(sprok_pt, 0, 0, 4, 6, max_x -184, 100, 24, 36, 0);
        if (player2->wins > 1)
            al_draw_scaled_bitmap(sprok_pt, 0, 0, 4, 6, max_x -154, 100, 24, 36, 0);    
    }    
       
        
    /*update do display*/
    al_flip_display();
    
    return;
}

void showOver(ALLEGRO_FONT *font, ALLEGRO_BITMAP *game_over, char* winner, int max_x, int max_y) {    
    al_clear_to_color(al_map_rgb(0, 0, 0));
    
    al_draw_scaled_bitmap(game_over, 0, 0, 230, 89, 155, 0, 690, 267, 0);
    
    al_draw_text(font, al_map_rgb(255, 219, 0), 500, 350, ALLEGRO_ALIGN_CENTER, winner);
    al_draw_text(font, al_map_rgb(255, 219, 0), 500, 370, ALLEGRO_ALIGN_CENTER, "GANHOU");
       
    al_draw_text(font, al_map_rgb(255, 96, 0), 500, max_y - 84, ALLEGRO_ALIGN_CENTER, "APERTE ENTER");  
    
    /*update do display*/
    al_flip_display();
    
    return;
}

int game (ALLEGRO_FONT* font, ALLEGRO_EVENT_QUEUE* queue, int max_x, int max_y, 
          ALLEGRO_BITMAP** p1_sprites, ALLEGRO_BITMAP** p2_sprites, 
          mano* player1, mano* player2, int bot, ALLEGRO_BITMAP* cenario) {
    ALLEGRO_EVENT event;
    
    int round_over = 0;
    int pause = 0;
    int tela = MAIN;
    char* winner;
    
    ALLEGRO_BITMAP *sprok_pt = al_load_bitmap("./sprites/sprok_pt.png");
    ALLEGRO_BITMAP *pause_text = al_load_bitmap("./sprites/pause.png");
    ALLEGRO_BITMAP *game_over = al_load_bitmap("./sprites/game_over.png");
    
    while (1) {
        switch (tela) {
            case MAIN:
                round_over = 0;
                pause = 0;
                while (event.type != 42 && !round_over && !pause) {  
                    if (event.type ==  30) {
                    /*batida do clock*/
                        if (bot) 
                            update_bot(player1, player2, max_x);
                        
                        update_facing_dir(player1, player2);
                        update_state(player1, p1_sprites, max_y);
                        update_state(player2, p2_sprites, max_y);
                        update_position(player1, player2, max_x, max_y);
                        update_health(player1, player2);
                        
                        showGame(font, player1, player2, sprok_pt, cenario, max_x, max_y);
                        
                        if (player1->health <= 0) {
                            player2->wins++;
                            round_over = 1;
                        } else if (player2->health <= 0) {
                            player1->wins++;
                            round_over = 1;
                            
                        }
                    }
                    else if (event.type == ALLEGRO_EVENT_KEY_DOWN ||event.type == ALLEGRO_EVENT_KEY_UP) {
                        /*tecla pressionada ou solta*/
                        update_keys(event, player1, player2, bot, &pause);        
                        if (pause)
                            tela = PAUSE;
                    }
                    al_wait_for_event(queue, &event); 
                }
                
                if (round_over) {
                    al_flush_event_queue(queue);
                    reset(player1, p1_sprites[STD], player2, p2_sprites[STD], max_y);
                }
                
                if (player1->wins > 1 || player2->wins > 1 || event.type == 42) {
                    if (player1->wins > 1) {
                        winner = strdup(player1->name);
                    } else {
                        winner = strdup(player2->name);
                    }
                    
                    tela = OVER;
                    
                    if (event.type == 42) {
                        free(winner);
                        return 1;
                    }
                }
            break;
            case PAUSE:
                al_draw_scaled_bitmap(pause_text, 0, 0, 113, 34, 161, 273, 678, 204, 0);
                al_flip_display();
                while (pause && event.type != 42) {
                    al_wait_for_event(queue, &event); 
                    if (event.type == ALLEGRO_EVENT_KEY_DOWN) 
                        if (event.keyboard.keycode == ALLEGRO_KEY_P) 
                            pause = 0;  
                }
                if (event.type == 42)
                    return 1;   
                
                al_flush_event_queue(queue);
                
                tela = MAIN;
            break;
            case OVER:
                /*destruindo os personagens e seus bitmaps*/
                mano_destroy(player1);
                mano_destroy(player2);
                for (int i = 0; i < 6; i++) {
                    al_destroy_bitmap(p1_sprites[i]);
                    al_destroy_bitmap(p2_sprites[i]);    
                }
                /*destruindo sprites do jogo*/
                al_destroy_bitmap(sprok_pt);
                al_destroy_bitmap(pause_text);
                
                /*mostrando a tela over e esperando enter*/
                while (event.type != 42 && tela == OVER) {
                    if (event.type == 30) {
                        showOver(font, game_over, winner, max_x, max_y);
                    } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) {
                        if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) {
                            al_destroy_bitmap(game_over);
                            return 0;
                        }
                    }
                    al_wait_for_event(queue, &event); 
                }
                
                free(winner);
                
                if (event.type == 42) 
                    return 1;
            break;
            default: break;
        }
        al_wait_for_event(queue, &event);
    }
}       
