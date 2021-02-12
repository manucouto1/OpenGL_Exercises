OBJECTS= ./lib/my_movement.o ./lib/my_objects.o 

BUILD_DIR = ./build

LIBS=-lGL -lGLU -lglut -lm

compile-%: $(OBJECTS)
	gcc -Wall $(OBJECTS) $*.c -o ./$* $(LIBS)

all: clean examen execute

execute: 
	./examen

run : compile-examen execute

clean:
	rm -f examen
