#include "_minishell.h"

char	lexer_advance(t_lexer *lexer)
{
	char	c;

	c = lexer_peek(lexer);
	lexer->current++;
	return (c);
}

int	lexer_advance_delim(t_lexer *lexer, char *delim)
{
	int	count;

	count = 0;
	while (!lexer_at_end(lexer) && !ft_strchr(delim, lexer_peek(lexer)))
	{
		count++;
		lexer_advance(lexer);
	}
	return (count);
}

int	lexer_advance_while(t_lexer *lexer, bool (*predicate)(char))
{
	int	count;

	count = 0;
	while (!lexer_at_end(lexer) && predicate(lexer_peek(lexer)))
	{
		count++;
		lexer_advance(lexer);
	}
	return (count);
}