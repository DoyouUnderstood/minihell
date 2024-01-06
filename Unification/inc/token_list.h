#ifndef TOKEN_LIST_H
# define TOKEN_LIST_H

typedef struct s_token_list
{
	struct s_token_list	*prev;
	struct s_token_list	*next;
	t_token				*token;
}	t_token_list;

// Token.
t_token_list	*token_list_construct(t_token *token, t_error *error);
void			token_list_del(t_token_list *node);
void			token_list_clear(t_token_list **token_list);
t_token_list	*token_list_last(t_token_list *token_list);
t_token_list	*token_list_at(t_token_list *token_list, int index);
void			token_list_insert(t_token_list **token_list, t_token_list *insertion);
void			token_list_remove(t_token_list **token_list, int count);
void			token_list_remove_after(t_token_list *token_list, int count);
void			token_list_replace_after(t_token_list *token_list,
					int count, t_token_list *insertion);

// Token add.
void			token_list_add_token(t_token_list **token_list, t_token *token, t_error *error);
void			token_list_add_op(t_token_list **token_list, t_token_type token_type, t_error *error);
void			token_list_add_word(t_token_list **token_list, char *lexeme, char *value, t_error *error);

#endif
