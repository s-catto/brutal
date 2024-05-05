#include <stdlib.h>
#include "mano.h"

mano* mano_create(int width, int height, 
                  int x, int y, 
                  int max_x, int max_y)
{

    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height/2 < 0) 
        || (y + height/2 > max_y)) 
        return NULL;

    mano *new_mano = (mano*) malloc(sizeof(mano));
  	new_mano->width = width;
  	new_mano->height = height;
    new_mano->x = x;	
    new_mano->y = y;
    new_mano->control = joystick_create();
    return new_mano;
}

void mano_move(mano *element, int steps, int trajectory, 
               int max_x, int max_y)
{
    if (!trajectory){ 
        if ((element->x - steps*MANO_STEP) - element->width/2 >= 0) 
            element->x = element->x - steps*MANO_STEP;
    }
    else if (trajectory == 1){ 
        if ((element->x + steps*MANO_STEP) + element->width/2 <= max_x) 
            element->x = element->x + steps*MANO_STEP;
    }
    /* mudar pra jump, o parametro tem q ser diff de steps*/
    if (trajectory == 2){ 
        if ((element->y - steps*MANO_STEP) - element->height/2 >= 0) 
            element->y = element->y - steps*MANO_STEP;
    }
    else if (trajectory == 3){ 
        /*aqui é agachar/ir pro chão mais rapido nn vai ser steps tbm*/
        if ((element->y + steps*MANO_STEP) + element->height/2 <= max_y) 
            element->y = element->y + steps*MANO_STEP;
    }
}

void mano_destroy(mano *element){
    joystick_destroy(element->control);
    free(element);
}
