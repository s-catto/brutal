#include <stdlib.h>
#include "box.h"

box *box_create (int x, int y,
                 int x_ref, int y_ref, 
                 int w, int h, 
                 int max_x, int max_y) {   
                 
    if ((x_ref + x- w/2 < 0) || (x_ref + x + w/2 > max_x) || (y_ref + y - h < 0) 
        || (y_ref + y > max_y)) 
        return NULL;
    
    box *new_box = (box*) malloc(sizeof(box));
    
    new_box->x = x;
    new_box->y = y;
    new_box->width = w;
  	new_box->height = h;  
  	
  	return new_box;
}
