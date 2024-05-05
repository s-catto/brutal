#ifndef __JOYSTICK__
#define __JOYSTICK__

typedef struct {
    int right;
    int left;
    int up;
    int down;
} joystick;

joystick* joystick_create(); 
void joystick_destroy(joystick *element);
void joystick_right(joystick *element);
void joystick_left(joystick *element);
void joystick_up(joystick *element);
void joystick_down(joystick *element);

#endif
