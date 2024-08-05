CC = gcc
CFLAGS = -g -Wall 

INCLUDE = ./include
LIB = ./lib
OBJ = ./obj

ALLEGRO = `pkg-config allegro-5 allegro_main-5 allegro_primitives-5 allegro_image-5 allegro_font-5 allegro_ttf-5 --libs --cflags`

all: brutal

brutal: main.o libed 
	$(CC) -o brutal $(OBJ)/*.o $(ALLEGRO)

libed: joystick.o box.o mano.o personagens.o menu.o chselect.o game.o

main.o: main.c | $(OBJ)
	$(CC) -c $(CFLAGS) $< -I $(INCLUDE) -o $(OBJ)/$@ 	 

%.o: $(LIB)/%.c $(INCLUDE)/%.h | $(OBJ)
	$(CC) -c $(CFLAGS) $< -I $(INCLUDE) -o $(OBJ)/$@

$(OBJ):
	mkdir $(OBJ)

clean:
	rm -f $(OBJ)/*.o
	rmdir $(OBJ)
	
purge: clean
	rm -f brutal
