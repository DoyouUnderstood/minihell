#include "_minishell.h"

static void	extract_word(t_lexer *lexer, t_token_list **token_list, t_error *error)
{
	char	*lexeme;

	lexeme = lexer_extract(lexer);
	if (!lexeme)
	{
		error_set(error, ERR_SYSTEM, NULL);
		return ;
	}
	token_list_add_word(token_list, lexeme, NULL, error);
	if (has_error(error))
		free(lexeme);
}

static void	handle_double_quote(t_lexer *lexer, t_error *error)
{
	lexer_advance(lexer);
	lexer_advance_delim(lexer, "\"");
	if (!lexer_match(lexer, "\""))
		error_set(error, ERR_CUSTOM, ft_strdup("Missing ending double quote"));
}

static void	handle_single_quote(t_lexer *lexer, t_error *error)
{
	lexer_advance(lexer);
	lexer_advance_delim(lexer, "'");
	if (!lexer_match(lexer, "'"))
		error_set(error, ERR_CUSTOM, ft_strdup("Missing ending single quote"));
}

void	tokenize_word(t_lexer *lexer, t_token_list **token_list, t_error *error)
{
	while (!lexer_at_end(lexer))
	{
		if (ms_is_metacharacter(lexer_peek(lexer)))
			break;
		if (lexer_peek(lexer) == '"')
			handle_double_quote(lexer, error);
		else if (lexer_peek(lexer) == '\'')
			handle_single_quote(lexer, error);
		else
			lexer_advance(lexer);
		if (has_error(error))
			return ;
	}
	extract_word(lexer, token_list, error);
}
