#include "minishell.h"

bool match(t_token_list **parser, t_token_type type) 
{
    if (check(*parser, type)) 
    {
        advance(parser);
        return true;
    }
    return false;
}

t_token_list *consume(t_token_list **parser, t_token_type type) 
{
    if (check(*parser, type)) 
    {
        t_token_list *current = *parser;
        advance(parser);
        return (current);
    }
    printf("Error mon fils");
    return NULL;
}

bool check(t_token_list *parser, t_token_type type)
{
    if (parser == NULL || parser->token == NULL) 
        return false;
    return (parser->token->type == type);
}

void advance(t_token_list **parser) 
{
    if (*parser != NULL)
        *parser = (*parser)->next;
}


t_token_list *peek_next(t_token_list *parser) 
{
    if (parser == NULL || parser->next == NULL) 
        return NULL;
    return parser->next;
}

t_token_list *peek(t_token_list *parser) 
{
    return parser;
}

bool is_at_end(t_token_list *parser) {
    return parser == NULL || (parser->token != NULL && parser->token->type == T_EOF);
}

t_token_list *previous(t_token_list *parser) 
{
    return (parser != NULL) ? parser->prev : NULL;
}


int	is_valid_redirection_token(t_token_type type)
{
	if (type == T_LESS_LESS || type == T_LESS || type == T_GREAT_GREAT
		|| type == T_GREAT)
		return (1);
	return (0);
}

t_redirection_type redi_type(const char *type)
{
    if (strcmp(type, "<<") == 0)
        return E_DLESS;
    else if (strcmp(type, "<") == 0)
        return E_LESS;
    else if (strcmp(type, ">>") == 0)
        return E_DGREAT;
    else if (strcmp(type, ">") == 0)
        return E_GREAT;
    else
    {
        printf("error\n");
        exit(1);
    }
}
t_redirection_type token_to_redirection_type(t_token_type type) {
    switch (type) {
        case T_LESS_LESS:
            return E_DLESS;
        case T_LESS:
            return E_LESS;
        case T_GREAT_GREAT:
            return E_DGREAT;
        case T_GREAT:
            return E_GREAT;
        default:
            // Gérer l'erreur si nécessaire
            return E_LESS; // Retournez une valeur par défaut ou gérez l'erreur
    }
}

void print_ast(const t_ast_node *node, int level) {
    if (node == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    printf("Value: %s, Type: %u\n", node->value, node->type);

    t_argument *current_arg = node->arguments;
    while (current_arg != NULL) {
        for (int j = 0; j < level + 1; j++) printf("  ");
        printf("Arg: %s\n", current_arg->value);
        current_arg = current_arg->next;
    }

    t_redirection *current_redir = node->redirections;
    while (current_redir != NULL) {
        for (int j = 0; j < level + 1; j++) printf("  ");
        printf("Redirection: %u -> %s\n", current_redir->type, current_redir->file);
        current_redir = current_redir->next;
    }

    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}

void print_token_types(t_token_list *tokens) {
    while (tokens != NULL) 
    {
        printf("lexeme : %s\n", tokens->token->lexeme);
        if (tokens->token != NULL) {
            printf("Token type: %d\n", tokens->token->type);
        } else {
            printf("Token is NULL\n");
        }
        tokens = tokens->next;
    }
}