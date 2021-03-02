# Gustavo Valente Nunes
#GRR 20182557



all: escalona

run: 
	./escalona

escalona: ./src/main.o ./src/functions.o ./src/arrumaEntrada.o
	gcc ./src/main.o ./src/functions.o ./src/arrumaEntrada.o -o escalona -Wall && doxygen ./doxyg/dox 

main.o: ./src/main.c ./includes/functions.h ./includes/arrumaEntrada.h
	gcc -c ./src/main.c -Wall

functions.o: ./src/functions.c ./includes/functions.h
	gcc -c ./src/functions.c -Wall

arrumaEntrada.o: ./src/arrumaEntrada.c ./includes/arrumaEntrada.h
	gcc -c ./src/arrumaEntrada.c -Wall

clean:
	rm -rf ./src/*.o

purge: clean
	rm -f escalona
	rm -r ./doxyg/latex
	rm -r ./doxyg/html