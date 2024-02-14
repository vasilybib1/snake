snake: snake.c
	gcc -I./lib/GLFW/include/ -L./lib/GLFW/lib-arm64/ -lglfw3 -framework Cocoa -framework IOKit -framework OpenGL -Wall -g -o snake snake.c


