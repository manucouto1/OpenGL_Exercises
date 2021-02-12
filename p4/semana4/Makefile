LIBS=-lGL -lGLU -lglut -lm

ejercicio4: ejercicio4.c
	gcc -o $@ $< $(LIBS)

all: clean ejercicio4 execute

execute: 
	./ejercicio4

run : ejercicio4 execute

clean:
	rm -f ejercicio4
