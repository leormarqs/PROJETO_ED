sugestao: src/sugestao.o src/fileread.o src/consultadas.o src/proximas.o
	gcc -o sugestao src/sugestao.o src/fileread.o src/consultadas.o src/proximas.o -lm
sugestao.o: src/sugestao.c src/consultadas.h
	gcc -c -g src/sugestao.c 
fileread.o: src/fileread.c src/fileread.h
	gcc -c -g src/fileread.c 
consultadas.o: src/consultadas.c src/consultadas.h src/proximas.h
	gcc -c -g src/consultadas.c
proximas.o: src/proximas.c src/proximas.h src/fileread.h
	gcc -c -g src/proximas.c

