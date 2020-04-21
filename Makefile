# variable

CC = gcc

EXEC = rsa.exe
ARCHIVE = groupe
TAR = tar.gz

SRCDIR = src
OBJDIR = obj
BINDIR = bin

DEPS = $(wildcard $(SRCDIR)/*.h)
SRC = $(wildcard $(SRCDIR)/*.c)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

FLAG = -Wall -g3

GMP = -lgmp

# make

all: config compil

compil: $(OBJ)
	@ $(CC) -o $(BINDIR)/$(EXEC) $(OBJ) $(GMP)
	@ echo "Linking complete!"

$(OBJDIR)/%.o: $(SRCDIR)/%.c $(DEPS)
	@ $(CC) -c -o $@ $< $(GMP) $(FLAG)
	@ echo "Compiled "$@" successfully!"

run:
	@ ./$(BINDIR)/$(EXEC)
	
clean:
	@ if [ $(ARCHIVE).$(TAR) ]; then rm -f $(ARCHIVE).$(TAR); echo "Archive removed!"; fi
	@ rm -f $(OBJDIR)/*
	@ echo "Object files removed!"
	@ rm -f $(BINDIR)/*
	@ echo "Executable removed!"
	
package: clean
	@ tar -czvf $(ARCHIVE).$(TAR) *
	@ echo "Archive created!"

config:
	@ if [ ! -d "bin/" ]; then mkdir bin; fi
	@ if [ ! -d "obj/" ]; then mkdir obj; fi