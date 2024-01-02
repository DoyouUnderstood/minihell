#include "minishell.h"

void handle_argument(t_parser *parser, t_ast_node *cmd_node) 
{
    while (!is_at_end(parser) && peek(parser)->type == T_WORD) 
    {
        add_argument_to_command(cmd_node, strdup(peek(parser)->token));
        advance(parser);
    }
}

void handle_redirection(t_parser *parser, t_ast_node *cmd_node) 
{
    while (!is_at_end(parser) && is_valid_redirection_token(peek(parser)->type)) {
        char *redir_type = strdup(peek(parser)->token);
        advance(parser);
        if (peek(parser)->type == T_WORD) 
        {
            add_redirection(cmd_node, redir_type, strdup(peek(parser)->token));
            advance(parser);
        }
        free(redir_type);
    }
}

void add_redirection(t_ast_node *node, const char *type, const char *file) 
{
    if (node->num_redirections >= MAX_REDIRECTIONS) 
    {
        printf("%s", "too much redirection karai\n");
        exit(0);
    }
    s_redirection *redirection = malloc(sizeof(s_redirection));
    redirection->type = strdup(type);
    redirection->file = strdup(file);

    node->redirections[node->num_redirections++] = redirection;
}

void add_argument_to_command(t_ast_node *cmd_node, char *argument) {
    if (cmd_node == NULL || argument == NULL) {
        // Gérer l'erreur: nœud de commande ou argument invalide
        if (argument != NULL) {
            free(argument); // Libérer l'argument si c'est alloué mais le nœud est NULL
        }
        return;
    }

    if (cmd_node->num_arguments >= MAX_ARGUMENTS) {
        // Gérer l'erreur: nombre maximal d'arguments atteint
        free(argument); // Important pour éviter les fuites de mémoire
        return;
    }

    // Ajout de l'argument au tableau d'arguments du nœud de commande
    cmd_node->arguments[cmd_node->num_arguments++] = argument;
}

