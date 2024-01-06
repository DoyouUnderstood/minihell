#include "_minishell.h"

static void	scan_token(t_lexer *lexer, t_token_list **token_list, t_error *error);

static t_token_list	*cleanup_error(t_token_list **token_list)
{
	token_list_clear(token_list);
	return (NULL);
}

t_token_list	*ms_tokenize(char *src, t_error *error)
{
	t_lexer			lexer;
	t_token_list	*token_list;

	lexer_init(&lexer, src);
	token_list = NULL;
	while (!lexer_at_end(&lexer))
	{
		lexer.start = lexer.current;
		scan_token(&lexer, &token_list, error);
		if (has_error(error))
			return (cleanup_error(&token_list));
	}
	token_list_add_op(&token_list, T_EOF, error);
	if (has_error(error))
		return (cleanup_error(&token_list));
	return (token_list);
}

static void	tokenize_op(t_lexer *lexer, t_token_list **token_list, t_error *error)
{
	char	*err_msg;

	if (lexer_match(lexer, "&&"))
		token_list_add_op(token_list, T_AND_AND, error);
	else if (lexer_match(lexer, "||"))
		token_list_add_op(token_list, T_PIPE_PIPE, error);
	else if (lexer_match(lexer, "|"))
		token_list_add_op(token_list, T_PIPE, error);
	else if (lexer_match(lexer, ">>"))
		token_list_add_op(token_list, T_GREAT_GREAT, error);
	else if (lexer_match(lexer, ">"))
		token_list_add_op(token_list, T_GREAT, error);
	else if (lexer_match(lexer, "<<"))
		token_list_add_op(token_list, T_LESS_LESS, error);
	else if (lexer_match(lexer, "<"))
		token_list_add_op(token_list, T_LESS, error);
	else if (lexer_match(lexer, "("))
		token_list_add_op(token_list, T_PAREN_OPEN, error);
	else if (lexer_match(lexer, ")"))
		token_list_add_op(token_list, T_PAREN_CLOSE, error);
	else
	{
		err_msg = ft_strdup("syntax error near unexpected character 'c'");
		if (!err_msg)
		{
			error_set(error, ERR_SYSTEM, NULL);
			return ;
		}
		err_msg[40] = lexer_peek(lexer);
		error_set(error, ERR_CUSTOM, err_msg);
	}
}

static void	scan_token(t_lexer *lexer, t_token_list **token_list, t_error *error)
{
	if (ms_is_whitespace(lexer_peek(lexer)))
		(void)lexer_advance(lexer);
	else if (ms_is_metacharacter(lexer_peek(lexer)))
		tokenize_op(lexer, token_list, error);
	else
		tokenize_word(lexer, token_list, error);
}
