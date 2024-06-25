#ifndef __MENU__
#define __MENU__

/*sprites animação menu*/
#define MENU0 "./sprites/menu/titulo/title_00.png"
#define MENU1 "./sprites/menu/titulo/title_01.png"
#define MENU2 "./sprites/menu/titulo/title_02.png"
#define MENU3 "./sprites/menu/titulo/title_03.png"
#define MENU4 "./sprites/menu/titulo/title_04.png"
#define MENU5 "./sprites/menu/titulo/title_05.png"

/*sprites transicao menu*/
#define MENU_T0 "./sprites/menu/trans/titlet_00.png"
#define MENU_T1 "./sprites/menu/trans/titlet_01.png"
#define MENU_T2 "./sprites/menu/trans/titlet_02.png"
#define MENU_T3 "./sprites/menu/trans/titlet_03.png"
#define MENU_T4 "./sprites/menu/trans/titlet_04.png"
#define MENU_T5 "./sprites/menu/trans/titlet_05.png"
#define MENU_T6 "./sprites/menu/trans/titlet_06.png"
#define MENU_T7 "./sprites/menu/trans/titlet_07.png"
#define MENU_T8 "./sprites/menu/trans/titlet_08.png"
#define MENU_T9 "./sprites/menu/trans/titlet_09.png"
#define MENU_T10 "./sprites/menu/trans/titlet_10.png"

#define P_ENTER "./sprites/menu/p_enter.png"

void load_menu (ALLEGRO_BITMAP** menu);

int animate_menu (ALLEGRO_BITMAP** menu, int ini, int fim, int i);

void menu (ALLEGRO_EVENT_QUEUE* queue, ALLEGRO_EVENT event, int max_x, int max_y);

void destroy_menu (ALLEGRO_BITMAP** menu);

#endif
