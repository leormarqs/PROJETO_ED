main: main_abp.o abp.o
	gcc -o main main_abp.o abp.o
	rm *.o
main_abp.o: main_abp.c abp.h 
	gcc -c -g main_abp.c 
abp.o: abp.c abp.h
	gcc -c -g abp.c 
