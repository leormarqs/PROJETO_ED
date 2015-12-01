sugestao: sugestao.o sugestao_lib.o
	gcc -o sugestao sugestao.o sugestao_lib.o
	rm *.o
sugestao.o: sugestao.c sugestao_lib.h 
	gcc -c -g sugestao.c 
sugestao_lib.o: sugestao_lib.c sugestao_lib.h
	gcc -c -g sugestao_lib.c 
