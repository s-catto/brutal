#ifndef __CHSELECT__ 
#define __CHSELECT__

#define CH_S_MAGAL  "./sprites/ch_sel/s_magal.png"
#define CH_J_THOMP  "./sprites/ch_sel/j_thomp.png"
#define CH_P_RAMBO  "./sprites/ch_sel/p_rambo.png"
#define CH_M_TOSTX  "./sprites/ch_sel/m_tostx.png"
#define CH_S_FTURO  "./sprites/ch_sel/s_fturo.png"

#define CASA "./sprites/cenarios/casa.jpg"
#define LOCA "./sprites/cenarios/locadora.jpg"
#define LOJA "./sprites/cenarios/loja_de_discos.jpg"

#define S_CASA 0
#define S_LOCA 1
#define S_LOJA 2

#define COR_P1      (al_map_rgb(255, 0, 0))
#define COR_P2      (al_map_rgb(0, 0, 255))
#define COR_UNSEL   (al_map_rgb(127, 127, 127))

#define GRID_X1 365
#define GRID_X2 635
#define GRID_Y1 150
#define GRID_Y2 420

#define BORDER  10
#define SQ_SIDE 120

#define SQ1_X1  ( GRID_X1 + BORDER ) 
#define SQ1_X2  ( SQ1_X1 + SQ_SIDE )
#define SQ1_Y1  ( GRID_Y1 + BORDER ) 
#define SQ1_Y2  ( SQ1_Y1 + SQ_SIDE )

#define SQ2_X1  ( SQ1_X2 + BORDER ) 
#define SQ2_X2  ( SQ2_X1 + SQ_SIDE )
#define SQ2_Y1  ( GRID_Y1 + BORDER ) 
#define SQ2_Y2  ( SQ1_Y1 + SQ_SIDE )

#define SQ3_X1  ( GRID_X1 + BORDER ) 
#define SQ3_X2  ( SQ3_X1 + SQ_SIDE )
#define SQ3_Y1  ( SQ1_Y2 + BORDER ) 
#define SQ3_Y2  ( SQ3_Y1 + SQ_SIDE )

#define SQ4_X1  ( SQ3_X2 + BORDER ) 
#define SQ4_X2  ( SQ4_X1 + SQ_SIDE )
#define SQ4_Y1  ( SQ2_Y2 + BORDER ) 
#define SQ4_Y2  ( SQ4_Y1 + SQ_SIDE )

typedef struct {
    ALLEGRO_COLOR cores[4];   
    ALLEGRO_BITMAP *chrs[5];
    int p1;
    int p2;   
} character_square;

void load_chr_bitmaps(ALLEGRO_BITMAP **chrs);

int ch_select (ALLEGRO_FONT* font, ALLEGRO_EVENT_QUEUE* queue, int max_x, int max_y,
               ALLEGRO_BITMAP** p1_sprites, ALLEGRO_BITMAP** p2_sprites,
               mano** player1, mano** player2, int* bot, ALLEGRO_BITMAP** cenario);

void destroy_chr_bitmaps(ALLEGRO_BITMAP **chrs);

#endif 
