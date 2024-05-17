#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "menu.h"

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
    
    menu[21] = al_load_bitmap(P_ENTER);
    
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

void destroy_menu (ALLEGRO_BITMAP** menu) {
    for (int i = 0; i < 22; i++)
        al_destroy_bitmap(menu[i]);
        
    return;
}
