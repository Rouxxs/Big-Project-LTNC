compile:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Game src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf

run:
	g++ -Iinclude -Iinclude/sdl -Iinclude/headers -Llib -o Game src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf
	./Game.exe

run-only:
	./Game.exe