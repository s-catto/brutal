#include <stdlib.h>
#include "joystick.h"

joystick* joystick_create(){

    joystick *element = (joystick*) malloc (sizeof(joystick));
    element->right = 0;
    element->left = 0;
    element->up = 0;
    element->down = 0;
    
    element->punch = 0;
    element->kick = 0;
    
    return element;
}

void joystick_destroy(joystick *element){ free(element);}

void joystick_reset(joystick *element){
    element->right = 0;
    element->left = 0;
    element->up = 0;
    element->down = 0;
    
    element->punch = 0;
    element->kick = 0;
    
    return;        
}

void joystick_left(joystick *element){ element->left = 1;}

void joystick_right(joystick *element){ element->right = 1;}

void joystick_up(joystick *element){ element->up = 1;}

void joystick_down(joystick *element){ element->down = 1;}

void joystick_punch(joystick *element){ element->punch = 1;}

void joystick_kick(joystick *element) { element->kick = 1;}



void joystick_unleft(joystick *element){ element->left = 0;}

void joystick_unright(joystick *element){ element->right = 0;}

void joystick_unup(joystick *element){ element->up = 0;}

void joystick_undown(joystick *element){ element->down = 0;}

void joystick_unpunch(joystick *element){ element->punch = 0;}

void joystick_unkick(joystick *element) { element->kick = 0;}
