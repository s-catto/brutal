/*define onde os personagens "pisam"*/
#define GROUND  20
#define GRAVITY -4

/*definindo tipos de colisão*/
#define NORMAL  0
#define HIT_P1  1
#define HIT_P2  2

/*tela do jogo*/
#define MAIN    0
#define PAUSE   1
#define OVER    2

/*retorna 1 caso o tipo de colisão aconteça, 0 caso contrário
os tipos são:
    - normal : colisão de hitbox com hitbox, evitar overlap dos personagens
    - hit_p1 : colisão da hurtbox do p2 com a hitbox do p1 (dano no p1)
    - hit_p2 : colisão da hurtbox do p1 com a hitbox do p2 (dano no p2)
    - outro : detecta se um está em cima do outro ("colisão" horizontal) 
*/
int collision (mano* player1, mano* player2, int tipo);



/*atualiza a direção dos players*/
void update_facing_dir (mano* p1, mano* p2);

/*atualiza o estado do player baseado no estado atual e no joystick*/
void update_state (mano* player, ALLEGRO_BITMAP* sprites[6], int max_y);

/*atualiza a posição dos players com base no estado e evitando colisões*/
void update_position (mano* player1, mano* player2, int max_x, int max_y);

/*atualiza a saude dos players baseado em se há ou não colisão entre hits e hurts*/
void update_health (mano* player1, mano* player2);

/*atualiza os joysticks e o pause usando o evento de pressionar/soltar tecla*/
void update_keys (ALLEGRO_EVENT event, mano* player1, mano* player2, int bot, int* pause);

/*atualiza o joystick do bot, aleatoriamente*/
void update_bot (mano* player1, mano* player2, int max_x);



/*reseta os players para começar um novo round*/
void reset (mano* player1, ALLEGRO_BITMAP* sprite1, mano* player2, ALLEGRO_BITMAP* sprite2, int max_y);



/*desenha o cenário, personagens, barras de vida, pontos, etc no display*/
void showGame (ALLEGRO_FONT *font, mano* player1, mano* player2, ALLEGRO_BITMAP *sprok_pt, ALLEGRO_BITMAP* cenario, int max_x, int max_y);

/*desenha na tela game over, o ganhador e a instrução para voltar ao menu*/
void showOver(ALLEGRO_FONT *font, ALLEGRO_BITMAP *game_over, char* winner, int max_x, int max_y);



/*função principal, coordena com base na fila as atualizações e desenhos*/
int game(ALLEGRO_FONT* font, ALLEGRO_EVENT_QUEUE* queue, int max_x, int max_y, 
          ALLEGRO_BITMAP** p1_sprites, ALLEGRO_BITMAP** p2_sprites, 
          mano* player1, mano* player2, int bot, ALLEGRO_BITMAP* cenario);
