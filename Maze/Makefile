IDIR=include
SDIR=src
ODIR=out
vpath %.h $(IDIR)
vpath %.c $(SDIR)
vpath %.o $(ODIR)
APP=maze
INC=$(wildcard $(IDIR)/*.h)
SRC=$(wildcard $(SDIR)/*.c)
OBJ=$(patsubst $(SDIR)/%.c,$(ODIR)/%.o, $(SRC))
CC=gcc
CFLAGS=\
	-lm		\
	-lglut	\
	-lGL	\
	-lGLU	\
	-I./$(IDIR)

.PHONY: clean compile test run

all: compile run

run: $(APP)
	./$(APP)

compile: $(APP)

$(APP): $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS)

$(ODIR)/main.o: $(SDIR)/main.c
	gcc -o $@ -c $< $(CFLAGS)

$(ODIR)/%.o: %.c %.h
	mkdir -p $(ODIR)
	$(CC) -o $@ -c $< $(CFLAGS)

clean:
	rm -rf $(ODIR)/*.o $(APP)
