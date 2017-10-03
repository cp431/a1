a1:	a1.o prime_list.o
	gcc a1.o prime_list.o -o a1 -lgmp

a1.o:	a1.c prime_list.h
	gcc -c -std=c99 a1.c

prime_list.o: prime_list.c prime_list.h
	gcc -c -std=c99 prime_list.c

clean: 
	rm a1.o prime_list.o a1
