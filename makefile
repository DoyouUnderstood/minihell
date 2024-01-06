# Nom du programme à compiler
TARGET = a.out

# Compilateur à utiliser
CC = gcc

# Options de compilation
CFLAGS = 

# Options de liaison
LDFLAGS = -lreadline

# Liste des fichiers source
SRCS = commande.c constructeur.c parser.c redirection.c utils.c

# Liste des fichiers objets (remplacement de .c par .o)
OBJS = $(SRCS:.c=.o)

# Règle par défaut
all: $(TARGET)

# Comment créer le programme final
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Règle pour chaque fichier source
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Nettoyage (suppression des fichiers objets et du programme)
clean:
	rm -f $(OBJS) $(TARGET)

# Règle pour reconstruire le projet
re: clean all

# .PHONY signifie que ce qui suit n'est pas un fichier.
.PHONY: all clean re
