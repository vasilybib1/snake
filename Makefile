CC = gcc
CFLAGS = -g -Wno-deprecated-declarations -I/opt/homebrew/include
LDFLAGS = -L/opt/homebrew/lib
LDLIBS = -lglfw
OBJECTS = util.o snake.o
FRAMEWORK = -framework OpenGL

.PHONY: all
all: snake

.PHONY: clean
clean:
	$(RM) -r *~ *.o *.dSYM snake

util.o: util.h util.c
snake.o: util.h snake.c

snake: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) $(FRAMEWORK) $(LDFLAGS) $(LDLIBS) -o snake 
