#include <allegro5/allegro5.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "../include/menu.h"

void load_menu (ALLEGRO_BITMAP** menu) {
    menu[0] = al_load_bitmap(MENU0);
    menu[1] = al_load_bitmap(MENU1);
    menu[2] = al_load_bitmap(MENU2);
    menu[3] = al_load_bitmap(MENU3);
    menu[4] = al_load_bitmap(MENU4);
    menu[5] = al_load_bitmap(MENU5);
    menu[6] = al_load_bitmap(MENU4);
    menu[7] = al_load_bitmap(MENU3);
    menu[8] = al_load_bitmap(MENU2);
    menu[9] = al_load_bitmap(MENU1);
    
    menu[10] = al_load_bitmap(MENU_T0);
    menu[11] = al_load_bitmap(MENU_T1);
    menu[12] = al_load_bitmap(MENU_T2);
    menu[13] = al_load_bitmap(MENU_T3);
    menu[14] = al_load_bitmap(MENU_T4);
    menu[15] = al_load_bitmap(MENU_T5);
    menu[16] = al_load_bitmap(MENU_T6);
    menu[17] = al_load_bitmap(MENU_T7);
    menu[18] = al_load_bitmap(MENU_T8);
    menu[19] = al_load_bitmap(MENU_T9);
    menu[20] = al_load_bitmap(MENU_T10);
    
    return;
}

int animate_menu (ALLEGRO_BITMAP** menu, int ini, int fim, int i) {
    
    if (fim < ini || ini + i/3 > fim)
        return -1;
    
    int p = ini + i/3; 
    
    al_draw_scaled_bitmap(menu[p], 0, 0, 174, 132, 
                         152 , -66, 
                         696, 528, 0);
                                   
    if (p == fim)
        return 0;
        
    return i + 1;
}

int menu (ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_FONT* font, int max_x, int max_y) {
    ALLEGRO_EVENT event;
    al_wait_for_event(queue, &event);
    
    ALLEGRO_BITMAP* menu[21];
    load_menu(menu);
    
    /*se é pra transicionar*/
    int trans = 0;
    int i = 0;
    while (event.type != 42 && !trans) {
        if(event.type == 30) {    
            /*desenha o menu*/
            al_clear_to_color(al_map_rgb(69, 75, 27));
            i = animate_menu(menu, 0, 9, i);
            al_draw_text(font, al_map_rgb(0, 0, 0), 500, max_y - 84, 
	        ALLEGRO_ALIGN_CENTER, "APERTE ENTER");
            al_flip_display(); 
        } else if (event.type == ALLEGRO_EVENT_KEY_DOWN) 
            if (event.keyboard.keycode == ALLEGRO_KEY_ENTER) 
                trans = 1;
                        
        al_wait_for_event(queue, &event); 
    }
    while (trans && event.type != 42) {
        if (event.type == 30) {
            /*desenha a transição*/
            al_clear_to_color(al_map_rgb(69, 75, 27));
            trans = animate_menu(menu, 10, 20, trans);
            al_flip_display(); 
        }      
        al_wait_for_event(queue, &event);
    } 
    destroy_menu(menu);
    
    if (event.type == 42)
        return 1;
    
    return 0;
}

void destroy_menu (ALLEGRO_BITMAP** menu) {
    for (int i = 0; i <= 20; i++)
        al_destroy_bitmap(menu[i]);
        
    return;
}
