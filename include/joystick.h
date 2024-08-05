#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct {
    int right;
    int left;
    int up;
    int down;
    
    int punch;
    int kick;
} joystick;

joystick* joystick_create(); 
void joystick_destroy(joystick *element);
void joystick_reset(joystick *element);

void joystick_right(joystick *element);
void joystick_left(joystick *element);
void joystick_up(joystick *element);
void joystick_down(joystick *element);

void joystick_punch(joystick *element);
void joystick_kick(joystick *element);

void joystick_unright(joystick *element);
void joystick_unleft(joystick *element);
void joystick_unup(joystick *element);
void joystick_undown(joystick *element);

void joystick_unpunch(joystick *element);
void joystick_unkick(joystick *element);

#endif
