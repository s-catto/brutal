/*define onde os personagens "pisam"*/
#define GROUND  20
#define GRAVITY -4

/*definindo tipos de colisão*/
#define NORMAL  0
#define HIT_P1  1
#define HIT_P2  2

#define MAIN    0
#define PAUSE   1
#define OVER    2


int collision (mano* player1, mano* player2, int tipo);

void update_facing_dir (mano* p1, mano* p2);
void update_state (mano* player, ALLEGRO_BITMAP* sprites[6], int max_y);
void update_position (mano* player1, mano* player2, int max_x, int max_y);
void update_bot (mano* player1, mano* player2, int max_x);

void reset (mano* player1, ALLEGRO_BITMAP* sprite1, mano* player2, ALLEGRO_BITMAP* sprite2, int max_y);

void showGame (ALLEGRO_FONT *font, mano* player1, mano* player2, ALLEGRO_BITMAP *sprok_pt, ALLEGRO_BITMAP* cenario, int max_x, int max_y);
void showOver(ALLEGRO_FONT *font, ALLEGRO_BITMAP *game_over, char* winner, int max_x, int max_y);

int game(ALLEGRO_FONT* font, ALLEGRO_EVENT_QUEUE* queue, int max_x, int max_y, 
          ALLEGRO_BITMAP** p1_sprites, ALLEGRO_BITMAP** p2_sprites, 
          mano* player1, mano* player2, int bot, ALLEGRO_BITMAP* cenario);
