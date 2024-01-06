#include "_minishell.h"

void	token_list_add_token(t_token_list **token_list, t_token *token, t_error *error)
{
	t_token_list	*new_node;
	t_token_list	*last;

	if (!token)
	{
		error_set(error, ERR_CUSTOM,
			ft_strdup("Syntax error: Cannot call token_list_add_token with NULL token"));
		return ;
	}
	new_node = token_list_construct(token, error);
	if (has_error(error))
		return ;
	if (!*token_list)
	{
		*token_list = new_node;
		return ;
	}
	last = token_list_last(*token_list);
	last->next = new_node;
	new_node->prev = last;
}

void	token_list_add_op(t_token_list **token_list, t_token_type token_type, t_error *error)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
	{
		error_set(error, ERR_SYSTEM, NULL);
		return ;
	}
	token_init_op(token, token_type);
	token_list_add_token(token_list, token, error);
	if (has_error(error))
	{
		token_cleanup(token);
		free(token);
	}
}

void	token_list_add_word(t_token_list **token_list, char *lexeme, char *value, t_error *error)
{
	t_token	*token;

	token = malloc(sizeof(*token));
	if (!token)
	{
		error_set(error, ERR_SYSTEM, NULL);
		return ;
	}
	token_init_word(token, lexeme, value);
	token_list_add_token(token_list, token, error);
	if (has_error(error))
	{
		token_cleanup(token);
		free(token);
	}
}