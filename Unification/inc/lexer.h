#ifndef LEXER_H
# define LEXER_H

# include <stdbool.h>
# include "libft.h"

typedef struct s_lexer
{
	char	*src;
	int		start;
	int		current;
}	t_lexer;

void	lexer_init(t_lexer *lexer, char *src);
char	lexer_peek(t_lexer *lexer);
bool	lexer_at_end(t_lexer *lexer);
char	lexer_advance(t_lexer *lexer);
int		lexer_advance_delim(t_lexer *lexer, char *delim);
int		lexer_advance_while(t_lexer *lexer, bool (*predicate)(char));
bool	lexer_match(t_lexer *lexer, char *expected);
char	*lexer_extract(t_lexer *lexer);

#endif