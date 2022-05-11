lab1: lab1.o funciones.o
	gcc -o lab1 lab1.c funciones.o -Wall -lm

lab1.o: lab1.c
	gcc -c lab1.c -Wall

funciones.o: funciones.c
	gcc -c funciones.c -Wall

.PHONY: clean

clear:
	rm -rf *.o

run1: 
	./lab1 -i test100.csv -o salida.out -n 1000 -d 1230 -b
	./lab1 -i hola.txt -o salida.out -n 100 -d 123

run2: 
	./lab1 -i hola.txt -o  -n 1000 -d 1230 -b
	./lab1 -i hola.txt -o salida.out -n -100 -d 1230 -b
	./lab1 -i hola.txt -o salida.out -n 1000 -d -1230
	./lab1 -i hola.txt -o salida.out -n 1000 -d 
	./lab1 -i hola.txt -o salida.out -n 10 -d 3000

run3:
	./lab1 -i test100.csv -o salida.out -n 5 -d 150