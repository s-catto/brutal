#include <allegro5/allegro5.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>

#include "chselect.h"

void load_chr_bitmaps(ALLEGRO_BITMAP **chrs) {
    chrs[0] = al_load_bitmap(CH_S_MAGAL); 
    chrs[1] = al_load_bitmap(CH_J_THOMP);  
    
    return;
}

void destroy_chr_bitmaps(ALLEGRO_BITMAP **chrs) {
    for (int i = 0; i < 2; i++)
        al_destroy_bitmap(chrs[i]);
    
    return;
}
