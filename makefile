lab1: funciones.o
	gcc -Wall -o lab1 lab1.c funciones.o

funciones.o: funciones.c funciones.h
	gcc -Wall -c funciones.c

.PHONY: clean

clean:
	rm -rf *.o

run: 
	./lab1 -i hola.txt -o salida.out -n 1000 -d 1230 -b