#include "minishell.h"

bool match(t_parser *parser, t_token_type type) 
{
    if (check(parser, type)) {
        advance(parser);
        return true;
    }
    return false;
}

t_list *consume(t_parser *parser, t_token_type type, const char *error_message) 
{
    if (check(parser, type))
        return advance(parser);

    printf("Error mon fils"); // gerer l'erreur 
    return NULL;
}

bool check(t_parser *parser, t_token_type type) {
    if (is_at_end(parser)) 
        return false;
    return parser->current->type == type;
}

t_list *advance(t_parser *parser) 
{
    if (parser->current != NULL) 
    {
        parser->previous = parser->current;
        parser->current = parser->current->next;
    }
    return parser->previous;
}

t_list *peek_next(t_parser *parser) 
{
    if (parser->current->next == NULL) 
        return NULL;
    return parser->current->next;
}

t_list *peek(t_parser *parser) {
    return parser->current;
}

bool is_at_end(t_parser *parser) {
    return parser->current == NULL || parser->current->type == T_EOF;
}

t_list *previous(t_parser *parser) 
{
    return parser->previous;
}

int	is_valid_redirection_token(t_token_type type)
{
	if (type == T_DLESS || type == T_LESS || type == T_DGREAT
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
        printf("errrrror\n");
        exit(1);
    }
}

void print_ast(const t_ast_node *node, int level) 
{
    if (node == NULL) {
        return;
    }

    // Imprimer l'indentation pour le niveau actuel
    for (int i = 0; i < level; i++) {
        printf("  ");
    }

    // Imprimer la valeur du nœud
    printf("Value: %s, Type: %u\n", node->value, node->type);

    // Imprimer les arguments
    for (int i = 0; i < node->num_arguments; i++) {
        for (int j = 0; j < level + 1; j++) printf("  ");
        printf("Arg: %s\n", node->arguments[i]);
    }

    // Imprimer les redirections
    for (int i = 0; i < node->num_redirections; i++) {
        for (int j = 0; j < level + 1; j++) printf("  ");
        printf("Redirection: %u -> %s\n", node->redirections[i]->type, node->redirections[i]->file);
    }

    // Imprimer récursivement les nœuds gauche et droit
    print_ast(node->left, level + 1);
    print_ast(node->right, level + 1);
}
