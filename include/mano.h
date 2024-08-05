#ifndef __MANO__
#define __MANO__

#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_image.h>

#include "box.h"
#include "joystick.h"

/*define o quão rapido o mano move*/
#define MANO_STEP 10

/*para onde o personagem está virado*/
#define LEFT  0
#define RIGHT 1

/*estados*/
#define STAND       0
#define CROUCH      2
#define JUMP        3
#define AIRBORNE    4
#define WALKL       5
#define WALKR       6
#define ATTACK      7

/*estados de ataque*/
#define NONE        0
#define PUNCH       1
#define KICK        2

/*define a posição relativa do sprite ao x e y do player
dependendo também da direção do personagem*/
typedef struct {
    int x_L;
    int x_R;
    int cr_H;
} spr_settings;

typedef struct {
    int width;
    int height;
    int x;
    int y;
    int ini_x;                  /*x inicial, para o reset entre rounds*/
    
    box *hit;   
    box *hurt;
    int health;
    int wins;
    
    char* name;
    int face;                   /*direção*/
    ALLEGRO_BITMAP *sq_sprite;  /*sprite quadradinho*/
    ALLEGRO_BITMAP *sprite;     /*sprite atual*/
    spr_settings* spr_sett;
    
    int vy;                     /*velocidade no pulo*/
    int state;
    int attk_state;
    int cont;                   /*contador para temporizar os ataques*/
    
    joystick *control;
} mano;

/*cria e inicializa o mano*/
mano* mano_create(ALLEGRO_BITMAP* sq_sprite, ALLEGRO_BITMAP* sprite, char* name, 
                  int width, int height, 
                  int x, int y, 
                  int max_x, int max_y,
                  int face, int x_L, int x_R, int cr_H);

/*edita as coordenadas do mano, dependendo da trajetória*/                 
void mano_move(mano *element, int steps, int trajectory, int max_x, int max_y);

/*diminui a altura do mano*/
void mano_crouch (mano *mano); 
/*volta a altura inicial*/
void mano_uncrouch(mano *mano);
/*inicia o pulo*/
void mano_jump(mano* mano);

/*muda as coordenadas da hurtbox dependendo do ataque*/
void mano_punch(mano* mano);
void mano_kick(mano* mano);
/*reseta as coordenadas da hurtbox*/
void mano_peace(mano* mano);
  
/*free no mano*/
void mano_destroy(mano *element);

#endif
