#include "minishell.h"

void handle_argument(t_token_list **parser, t_ast_node *cmd_node) {
    while (*parser != NULL && (*parser)->token->type == T_WORD) {
        add_argument_to_command(cmd_node, strdup((*parser)->token->lexeme));
        advance(parser);
    }
}


void handle_redirection(t_token_list **parser, t_ast_node *cmd_node) {
    while (*parser != NULL && is_valid_redirection_token((*parser)->token->type)) {
        char *redir_type = strdup((*parser)->token->lexeme);
        advance(parser);

        if (*parser != NULL && (*parser)->token->type == T_WORD) {
            add_redirection(cmd_node, redir_type, strdup((*parser)->token->lexeme));
            advance(parser);
        } else {
            free(redir_type);
            // Gérer l'erreur
        }
    }
}



void add_redirection(t_ast_node *node, const char *type, const char *file) 
{
    t_redirection *new_redir = malloc(sizeof(t_redirection));
    if (new_redir == NULL) {
        // Gérer l'erreur d'allocation mémoire
        // free((char *)type);
        // free((char *)file);
        return;
    }
    new_redir->type = redi_type(type);
    new_redir->file = strdup(file);
    new_redir->next = NULL;

    if (node->redirections == NULL) {
        node->redirections = new_redir;
    } else {
        t_redirection *current = node->redirections;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_redir;
    }
}


void add_argument_to_command(t_ast_node *cmd_node, char *argument) {
    if (cmd_node == NULL || argument == NULL) {
        if (argument != NULL) {
            free(argument);
        }
        return;
    }

    t_argument *new_arg = malloc(sizeof(t_argument));
    if (new_arg == NULL) {
        // Gérer l'erreur d'allocation mémoire
        free(argument);
        return;
    }
    new_arg->value = argument;
    new_arg->next = NULL;

    if (cmd_node->arguments == NULL) {
        cmd_node->arguments = new_arg;
    } else {
        t_argument *current = cmd_node->arguments;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = new_arg;
    }
}


