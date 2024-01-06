NAME = minishell

SRC_FOLDER = src/
SRC_FILES = \
	main.c \
	error.c \
	token.c \
	pattern_match.c \
	constructeur.c \
	parser.c \
	redirection.c \
	utils.c \
	$(addprefix lexer/, lexer.c lexer_advance.c) \
	$(addprefix token_list/, token_list.c token_list_2.c token_list_add.c) \
	$(addprefix ms_tokenizer/, ms_tokenizer.c ms_tokenize_word.c ms_tokenizer_utils.c)

SRCS = $(addprefix $(SRC_FOLDER), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -Ilibs/libft
LDFLAGS = -Llibs/libft
LDLIBS = -lreadline -lft
SANITIZE_FLAGS = -g3 -fsanitize=address

.PHONY: all clean fclean re sanitize run valgrind-run test valgrind-test

all: $(NAME)

$(NAME): $(OBJS)
	$(MAKE) -s --no-print-directory -C libs/libft
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	$(MAKE) -s --no-print-directory -C libs/libft clean
	rm -f $(OBJS)

fclean:
	$(MAKE) -s --no-print-directory -C libs/libft fclean
	rm -f $(OBJS)
	rm -f $(NAME)

re: fclean all

sanitize: CFLAGS += $(SANITIZE_FLAGS)
sanitize: fclean $(NAME)

run: all
	./$(NAME)

valgrind-run: all
	valgrind -- ./$(NAME)

test: run fclean

valgrind-test: valgrind-run fclean

.SILENT: