#include <stdlib.h>
#include "mano.h"

mano* mano_create(int width, int height, 
                  int x, int y, 
                  int max_x, int max_y)
{

    if ((x - width/2 < 0) || (x + width/2 > max_x) || (y - height < 0) 
        || (y > max_y)) 
        return NULL;

    mano *new_mano = (mano*) malloc(sizeof(mano));
  	new_mano->width = width;
  	new_mano->height = height;
    new_mano->x = x;	
    new_mano->y = y;
    new_mano->state = STAND;
    new_mano->vy = 0;
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
    else if (trajectory == 2) {
        if ((element->vy > 0 && (element->y - element->vy * steps - element->height >= 0))
            || (element->vy < 0 && (element->y - element->vy * steps) <= max_y)) 
                element->y = element->y - element->vy * steps;
        if ((element->y - element->vy * steps) > max_y)
            element->y = max_y;
    } 
}

void mano_destroy(mano *element){
    joystick_destroy(element->control);
    free(element);
}
