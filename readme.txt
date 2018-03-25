1 - COM O GCC NO WINDOWS
gcc main.c estagio1.c estagio2.c menu.c instrucoes.c 
funcoes.c timer.c -o main.exe -lmingw32 -lSDLmain 
-lSDL -lSDL_image -lSDL_ttf -lSDL_mixer

2 - COM GCC NO LINUX
gcc main.c estagio1.c estagio2.c menu.c instrucoes.c
 funcoes.c timer.c -o main.exe -lSDLmain -lSDL 
-lSDL_image -lSDL_ttf -lSDL_mixer