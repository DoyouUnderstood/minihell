#ifndef TOKEN_H
# define TOKEN_H

typedef enum s_token_type
{
	T_WORD,
	T_AND_AND,
	T_PIPE_PIPE,
	T_PIPE,
	T_GREAT,
	T_GREAT_GREAT,
	T_LESS,
	T_LESS_LESS,
	T_PAREN_OPEN,
	T_PAREN_CLOSE,
	T_EOF
}	t_token_type;

typedef struct s_token
{
	t_token_type	type;
	char			*lexeme;
	char			*value;
}	t_token;

void	token_init(t_token *token, t_token_type type, char *lexeme,
			char *value);
void	token_init_word(t_token *token, char *lexeme, char *value);
void	token_init_op(t_token *token, t_token_type token_type);
void	token_cleanup(t_token *token);

#endif