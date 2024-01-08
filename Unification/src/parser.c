#include "minishell.h"

void print_token_types(t_token_list *tokens) {
    while (tokens != NULL) {
        if (tokens->token != NULL) {
            printf("Token type: %d\n", tokens->token->type);
        } else {
            printf("Token is NULL\n");
        }
        tokens = tokens->next;
    }
}

t_ast_node *parse_and_or(t_token_list **parser) 
{
    t_parser_type type;
    t_ast_node *node = parse_pipeline(parser);
    if (!node)
        return (NULL);
    while (match(parser, T_AND_AND) || match(parser, T_PIPE_PIPE)) 
    {
        t_token_list *previous_token = previous(*parser);
        if (previous_token == NULL)
            return (NULL);
        else if (previous_token->token->type == T_AND_AND)
            type = AND;
        else
            type = OR;
        t_ast_node *right = parse_pipeline(parser);
        node = new_and_or_node(type, node, right);
    }
    return (node);
}

t_ast_node *parse_pipeline(t_token_list **parser) 
{
    t_ast_node *node = parse_command(parser);
    if (!node)
        return (NULL);
    while (match(parser, T_PIPE))
    {
        t_ast_node *right = parse_command(parser);
        if (!right)
            return (NULL);
        node = new_pipeline_node(node, right);
    }
    return (node);
}

t_ast_node *parse_command(t_token_list **parser) {
    t_ast_node *cmd_node = NULL;

    while (is_redirection(peek(*parser))) {
        handle_redirection(parser, cmd_node);
    }

    if (peek(*parser)->token->type == T_WORD) {
        cmd_node = new_command_node(peek(*parser)->token->lexeme);
        if (!cmd_node)
            return (NULL);
        advance(parser);
        handle_argument(parser, cmd_node);
    } else {
        // Gérer l'erreur ou le cas où il n'y a pas de commande simple
        return NULL;
    }

    while (is_valid_redirection_token(peek(*parser))) {
        handle_redirection(parser, cmd_node);
    }

    return cmd_node;
}
