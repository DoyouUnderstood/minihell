#include "minishell.h"


t_ast_node *parse_and_or(t_parser *parser) 
{
    t_ast_node *node = parse_pipeline(parser);
    while (match(parser, T_AND) || match(parser, T_OR)) 
    {
        t_parser_type type = previous(parser)->type == T_AND ? AND : OR;
        t_ast_node *right = parse_pipeline(parser);
        node = new_and_or_node(type, node, right);
    }
    return node;
}

t_ast_node *parse_pipeline(t_parser *parser) 
{
    t_ast_node *node = parse_command(parser);
    while (match(parser, T_PIPE)) 
    {
        t_ast_node *right = parse_command(parser);
        node = new_pipeline_node(node, right);
    }
    return node;
}

t_ast_node *parse_command(t_parser *parser) 
{
    if (peek(parser)->type != T_WORD) 
        return NULL;

    t_ast_node *cmd_node = new_command_node(peek(parser)->token);
    advance(parser);

    // Gérer les arguments de la commande
    handle_argument(parser, cmd_node);

    // Gérer les redirections
    handle_redirection(parser, cmd_node);

    return cmd_node;
}


