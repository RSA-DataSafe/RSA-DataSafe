FLAGS =`pkg-config --libs --cflags gtk+-3.0`
DEBUG = `pkg-config --libs gtk+-3.0`
NAME =  App
FIC = Test
WARNINGS = -Wall 
CC = gcc 
REP = Src 
MAIN = App
export CC = gcc
export NAMEL = lib.a

run:target
	./$(NAME)
target:lib object 
	$(CC) $(WARNINGS) $(MAIN).o  $(CFLAGS) -L. $(NAMEL) -o $(NAME) $(DEBUG)
object: 
	$(CC) $(WARNINGS) $(FLAGS) -c  $(MAIN).c -o $(MAIN).o
lib:
	cd $(REP) && $(MAKE)
clean: 
	rm -rf   $(MAIN) $(NAMEL) *.o