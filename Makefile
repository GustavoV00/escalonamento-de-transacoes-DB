# Gustavo Valente Nunes
#GRR 20182557

all: escalona
run: 
	./escalona

escalona: main.o functions.o arrumaEntrada.o
	gcc main.o functions.o arrumaEntrada.o -o escalona -Wall

main.o: main.c functions.h arrumaEntrada.h
	gcc -c main.c -Wall

functions.o: functions.c functions.h
	gcc -c functions.c -Wall

arrumaEntrada.o: arrumaEntrada.c arrumaEntrada.h
	gcc -c arrumaEntrada.c -Wall

clean:
	rm -rf *.o

purge: clean
	rm -f escalona