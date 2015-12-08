CC=gcc
CFLAGS=-W -Wall -pedantic -g -std=c99
EXEC=3SatStable

all: $(EXEC)

3SatStable: 3SatStable.o
	$(CC) -o 3SatStable 3SatStable.o $(CFLAGS)

3SatStable.o: 3SatStable.c 
	$(CC) -o 3SatStable.o -c 3SatStable.c $(CFLAGS)

clean:
	rm -rf *.o

cleanall: clean
	rm -rf $(EXEC)

help:
	@echo "make 		Compile le projet"
	@echo "make clean 	Supprime les fichiers objet (.o)"
	@echo "make cleanall 	Supprime les fichiers objet (.o) et le binaire" $(EXEC)
	@echo "make help 	Affiche ce message d'aide"
