lab1: lab1.o funciones.o vis.o
	gcc -o lab1 lab1.c funciones.o -Wall -lm
	gcc -o vis vis.c funciones.o -Wall -lm

lab1.o: lab1.c
	gcc -c lab1.c

funciones.o: funciones.c
	gcc -c funciones.c

vis.o: vis.c
	gcc -c vis.c

.PHONY: clean

clear:
	rm -rf *.o
	rm -rf vis
	rm -rf lab1
	rm -rf *.out

run1: 
	./lab1 -i test100.csv -o salida100.out -n 2 -d 200 -b
	./lab1 -i test10000.csv -o salida10000.out -n 4 -d 100 -b