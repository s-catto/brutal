#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>	

#include "joystick.h"
#include "mano.h"

/*definindo aspecto da tela 4:3*/
#define X_SCREEN 1000
#define Y_SCREEN ((X_SCREEN / 4) * 3)

/*define onde os personagens "pisam"*/
#define GROUND  20
#define GRAVITY -1

int collision (mano* player1, mano* player2) {
    if ((((player1->x + player1->width/2 > player2->x - player2->width/2) && 
         (player1->x - player1->width/2 <= player2->x - player2->width/2)) 
        || 
        ((player2->x + player2->width/2 > player1->x - player1->width/2) &&
         (player2->x - player2->width/2 <= player1->x - player1->width/2)))
        &&
        (((player1->y > player2->y - player2->height) &&
         (player1->y - player1->height <= player2->y - player2->height)) 
        || 
        ((player2->y > player1->y - player1->height) &&
         (player2->y - player2->height <= player1->y - player1->height))))
    {return 1;}
    
    return 0;
}


void update_state (mano* player) {
    switch (player->state)
    {
        case STAND:
            if (player->control->up) {
                player->state = JUMP;
            } else if (player->control->down) {
                player->height = player->height / 2;
                player->state = CROUCH;
            } else if (player->control->left) {
                if (!player->control->right)
                    player->state = WALKL;
            } else if (player->control->right) {
                player->state = WALKR;
            }
            break;
            
        case CROUCH:
            if (!player->control->down) {
                player->height = player->height * 2;
                player->state = STAND;
            }
            break;
            
        case JUMP:
            player->vy = 27;
            player->y--;
            player->state = AIRBORNE;
            break;
            
        case AIRBORNE:
            if (player->y == Y_SCREEN - GROUND) {
                player->state = STAND;
                player->vy = 0;
            }
            break;
            
        case WALKL:
            if (player->control->up) {
                player->state = JUMP;
            } else if (player->control->down) {
                player->height = player->height / 2;
                player->state = CROUCH;
            } else if (!player->control->left || player->control->right) {
                player->state = STAND;
            }
            break;
        
        case WALKR:
            if (player->control->up) {
                player->state = JUMP;
            } else if (player->control->down) {
                player->height = player->height / 2;
                player->state = CROUCH;
            } else if (!player->control->right || player->control->left) {
                player->state = STAND;
            }
            break; 
        
        default: break;
    }
    
    return;       
}

void update_position (mano* player1, mano* player2) {
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
    
    al_install_keyboard();
	
    ALLEGRO_TIMER* timer = al_create_timer(1.0 / 30.0);
    ALLEGRO_EVENT_QUEUE* queue = al_create_event_queue();
    ALLEGRO_FONT* font = al_create_builtin_font();
    ALLEGRO_DISPLAY* disp = al_create_display(X_SCREEN, Y_SCREEN);
	
    al_register_event_source(queue, al_get_keyboard_event_source());
    al_register_event_source(queue, al_get_display_event_source(disp));
    al_register_event_source(queue, al_get_timer_event_source(timer));
    
    mano* player1 = mano_create(100, 325, 50, Y_SCREEN -GROUND, 
                    X_SCREEN, Y_SCREEN);
    if (!player1)
        return 1;
    mano* player2 = mano_create(100, 325, X_SCREEN -50, Y_SCREEN -GROUND, 
                    X_SCREEN, Y_SCREEN);
    if (!player2)
        return 2;
    
    ALLEGRO_EVENT event;
    al_start_timer(timer);
    al_wait_for_event(queue, &event);

    while (event.type != 42) {	
        /*batida do clock*/
        if (event.type ==  30) {
            update_state(player1);
            update_state(player2);
            update_position(player1, player2);
            al_clear_to_color(al_map_rgb(0, 0, 0));
            al_draw_filled_rectangle(0, Y_SCREEN - GROUND, X_SCREEN, Y_SCREEN,
	                                 al_map_rgb(0, 255, 0));	
             
            /*posiscionando os elementos*/
	        al_draw_filled_rectangle(player1->x-player1->width/2, player1->y-player1->height, 
	                                 player1->x+player1->width/2, player1->y,
	                                 al_map_rgb(255, 0, 0));
            al_draw_filled_rectangle(player2->x-player2->width/2, player2->y-player2->height, 
	                                 player2->x+player2->width/2, player2->y,
	                                 al_map_rgb(0, 0, 255));
                
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
    mano_destroy(player2);
    
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return 0;
}
