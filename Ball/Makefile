all: compile run

run: ball.o
	./ball.o

compile: ball.c
	gcc -o ball.o ball.c -lGL -lGLU -lglut -lm -O3

clean: ball.o
	rm ball.o
