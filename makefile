CFLAGS =  -Wall -g $(shellpkg-config --cflags)
LDFLAGS = $(shell pkg-config allegro-5 allegro_main-5 allegro_font-5 allegro_primitives-5 allegro_image-5 --libs)

objs = main.o joystick.o mano.o box.o personagens.o menu.o chselect.o

all: $(objs)
	gcc -o brutal $(objs) $(CFLAGS) $(LDFLAGS)

main.o: main.c joystick.h box.h personagens.h mano.h menu.h chselect.h

personagens.o: personagens.c personagens.h mano.h
mano.o: mano.c mano.h box.h

joystick.o: joystick.c joystick.h 
box.o: box.c box.h

menu.o: menu.c menu.h
chselect.o: chselect.c chselect.h

clean:
	-rm -f $(objs)
