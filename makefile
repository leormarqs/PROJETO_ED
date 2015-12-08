sugestao: sugestao.o fileread.o consultadas.o proximas.o
	gcc -o sugestao sugestao.o fileread.o consultadas.o proximas.o 
	rm *.o
sugestao.o: sugestao.c consultadas.h
	gcc -c -g sugestao.c 
fileread.o: fileread.c fileread.h
	gcc -c -g fileread.c 
consultadas.o: consultadas.c consultadas.h proximas.h
	gcc -c -g consultadas.c
proximas.o: proximas.c proximas.h fileread.h
	gcc -c -g proximas.c

