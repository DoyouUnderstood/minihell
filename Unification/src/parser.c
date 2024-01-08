#include "minishell.h"

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

t_ast_node *parse_command(t_token_list **parser) 
{
    t_ast_node *cmd_node = NULL;

    while (*parser != NULL && is_valid_redirection_token(peek(*parser)->token->type)) 
    {
        if (!handle_redirection(parser, cmd_node)) {
            // Gérer l'erreur
            break;
        }
    }
    if (peek(*parser)->token->type == T_WORD) {
        cmd_node = new_command_node(peek(*parser)->token->lexeme);
        if (!cmd_node)
            return (NULL);
        advance(parser);
        handle_argument(parser, cmd_node);
    } else {
        // Gérer l'erreur
        return NULL;
    }
    while (is_valid_redirection_token(peek(*parser)->token->type)) {
        handle_redirection(parser, cmd_node);
    }
    return cmd_node;
}


// Fonction Paranthese TEST a paufiney


t_ast_node *parse_subshell(t_token_list **parser) {
    if (current_token_is(T_PAREN_OPEN)) {
        advance(parser); // Passer la parenthèse ouvrante

        t_ast_node *subshell_node = create_new_ast_node("SUBSHELL");

        while (!current_token_is(T_PAREN_CLOSE) && !is_at_end(*parser)) {
            t_ast_node *cmd = parse_command(parser); // Appel récursif ou sous-section du parseur
            add_child_to_subshell(subshell_node, cmd);
        }

        if (!current_token_is(T_PAREN_CLOSE)) {
            return (NULL);
        }
        advance(parser);

        return subshell_node;
    }

    return NULL;
}

