.SUFFIXES:
.SUFFIXES: .c .o

CC = gcc
CFLAGS = -g -Wno-deprecated-declarations 
LLOC = -L/opt/homebrew/lib 
ILOC = -I/opt/homebrew/include
LDLIBS = -lglfw
FRAMEWORK = -framework OpenGL

OBJDIR = obj

vpath %.c src
vpath %.h src

OBJ = util.o shader.o snake.o object.o
HEADER = util.h shader.h object.h
objects = $(addprefix $(OBJDIR)/, $(OBJ))

snake: $(objects)
	$(CC) $(CFLAGS) -o snake $(objects) $(ILOC) $(LLOC) $(LDLIBS) $(FRAMEWORK) 

.PHONY: clean
clean:
	$(RM) -r *~ *.o $(OBJDIR)/*.o *.dSYM snake

$(OBJDIR) obj/%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) -c $(ILOC) $< -o $@
