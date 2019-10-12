all: compile run

run: robotArm.o
	./robotArm.o

compile: robotArm.c
	gcc -o robotArm.o robotArm.c -lGL -lglut -lm -lGLU -O3

clean: robotArm.o
	rm robotArm.o
