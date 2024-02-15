snake: snake.c
	gcc -Wno-deprecated-declarations \
		-L/opt/homebrew/lib \
		-I/opt/homebrew/include \
		-lglfw \
		-framework OpenGL \
		-g -o snake \
		util.c snake.c
