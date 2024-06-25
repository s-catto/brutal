#ifndef __BOX__
#define __BOX__

typedef struct {
    /*relativos ao mano*/
    int x;
    int y;
    
    int width;
    int height;
} box;

box *box_create(int x, int y, 
                int x_ref, int y_ref, 
                int w, int h, 
                int max_x, int max_y);

#endif
