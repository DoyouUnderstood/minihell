#include "_minishell.h"

void	token_init(t_token *token, t_token_type type, char *lexeme,
	char *value)
{
	token->type = type;
	token->lexeme = lexeme;
	token->value = value;
}

void	token_init_word(t_token *token, char *lexeme, char *value)
{
	token_init(token, T_WORD, lexeme, value);
}

void	token_init_op(t_token *token, t_token_type token_type)
{
	token_init(token, token_type, NULL, NULL);
}

void	token_cleanup(t_token *token)
{
	free(token->lexeme);
	free(token->value);
}