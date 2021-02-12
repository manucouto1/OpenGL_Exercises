LIBS=-lGL -lGLU -lglut -lm

ejercicio3: ejercicio3.c
	gcc -o $@ $< $(LIBS)

all: clean ejercicio3 execute

execute: 
	./ejercicio3

run : ejercicio3 execute

clean:
	rm -f ejercicio3
