lab1: funciones.o
	gcc -Wall -o lab1 lab1.c funciones.o

funciones.o: funciones.c funciones.h
	gcc -Wall -c funciones.c

.PHONY: clean

clean:
	rm -rf *.o

run1: 
	./lab1 -i test100.csv -o salida.out -n 1000 -d 1230 -b
	./lab1 -i hola.txt -o salida.out -n 100 -d 123

run2: 
	./lab1 -i hola.txt -o  -n 1000 -d 1230 -b
	./lab1 -i hola.txt -o salida.out -n -100 -d 1230 -b
	./lab1 -i hola.txt -o salida.out -n 1000 -d -1230
	./lab1 -i hola.txt -o salida.out -n 1000 -d 
	./lab1 -i hola.txt -o salida.out -n 20 -d 1230

run3:
	./lab1 -i test100.csv -o salida.out -n 1000 -d 1230