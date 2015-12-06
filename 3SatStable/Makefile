CC=gcc
CFLAGS=-W -Wall -pedantic -g -std=c99
EXEC=3SatStable

all: $(EXEC)

3SatStable: 3SatStable.o graph_l.o util.o
	$(CC) -o 3SatStable 3SatStable.o graph_l.o util.o $(CFLAGS)

3SatStable.o: 3SatStable.c graph_l.o
		$(CC) -o 3SatStable.o -c 3SatStable.c $(CFLAGS)

graph_l.o: graph_l.c
		$(CC) -o graph_l.o -c graph_l.c $(CFLAGS)

util.o: util.c
		$(CC) -o util.o -c util.c $(CFLAGS)

clean:
		rm -rf *.o

cleanall: clean
		rm -rf $(EXEC)

help:
		@echo "make 		Compile le projet"
		@echo "make clean 	Supprime les fichiers objet (.o)"
		@echo "make cleanall 	Supprime les fichiers objet (.o) et le binaire" $(EXEC)
		@echo "make help 	Affiche ce message d'aide"
