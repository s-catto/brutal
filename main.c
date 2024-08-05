#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include <stdio.h>
#include <stdlib.h>	
#include <time.h>

#include "include/joystick.h"
#include "include/box.h"

#include "include/mano.h"
#include "include/personagens.h"

#include "include/menu.h"
#include "include/chselect.h"
#include "include/game.h"

#define MENU    0
#define CHSEL   1
#define GAME    2

/*definindo aspecto da tela 4:3*/
#define X_SCREEN 1000
#define Y_SCREEN ((X_SCREEN / 4) * 3)

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
    srand(time(0));
    
    int close_display = 0;
    int tela = MENU;
    ALLEGRO_BITMAP *cenario;
    
    mano* player1 = NULL;
    ALLEGRO_BITMAP* p1_sprites[6];
    mano* player2 = NULL;
    ALLEGRO_BITMAP* p2_sprites[6];
    int bot = 0;

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
                close_display = ch_select(font, queue, X_SCREEN, Y_SCREEN, 
                          p1_sprites, p2_sprites, &player1, &player2, &bot, &cenario);
                
                if(close_display)
                    break;
       
                if (!player1)
                    return 1;
                if (!player2)
                    return 2;    
                    
                tela = GAME;  
            break;
            case GAME:
                close_display = game(font, queue, X_SCREEN, Y_SCREEN, 
                                p1_sprites, p2_sprites, player1, player2, 
                                bot, cenario);
                                
                tela = MENU;    
            break;
            default: return 3;
        }
        if (close_display) break;
        
        al_wait_for_event(queue, &event);  
    }
    
    al_destroy_bitmap(cenario);
    al_destroy_font(font);
    al_destroy_display(disp);
    al_destroy_timer(timer);
    al_destroy_event_queue(queue);
    
    return 0;
}
