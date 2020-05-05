FLAGS =`pkg-config --libs --cflags gtk+-3.0`
DEBUG = `pkg-config --libs gtk+-3.0`
WARNINGS = -Wall 
REP= ..
ALL_O = inter_initialisation.o inter_connexion.o inter_inscription.o inter_menu.o 
ALL_O += inter_parametre.o inter_chiffrer.o inter_dechiffrer.o inter_messagerie.o  
all:lib
lib:object
	ar   -rv   $(NAMEL)   $(ALL_O)
	rm    *.o
	mv   -f    $(NAMEL)    $(REP)
object:
	$(CC) $(WARNINGS) $(FLAGS) -c inter_initialisation.c  -o inter_initialisation.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_connexion.c   	  -o inter_connexion.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_inscription.c 	  -o inter_inscription.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_menu.c            -o inter_menu.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_parametre.c       -o inter_parametre.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_chiffrer.c        -o inter_chiffrer.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_dechiffrer.c      -o inter_dechiffrer.o
	$(CC) $(WARNINGS) $(FLAGS) -c inter_messagerie.c      -o inter_messagerie.o

