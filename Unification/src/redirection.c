#include "minishell.h"

void handle_argument(t_token_list **parser, t_ast_node *cmd_node) {
    while (*parser != NULL && (*parser)->token->type == T_WORD) {
        add_argument_to_command(cmd_node, strdup((*parser)->token->lexeme));
        advance(parser);
    }
}

int handle_redirection(t_token_list **parser, t_ast_node *cmd_node) {
    if (parser == NULL || *parser == NULL || cmd_node == NULL) {
        return 0; // Échec
    }

    // Vérifier si le token actuel est une redirection valide
    if (is_valid_redirection_token((*parser)->token->type)) {
        t_redirection_type redir_type = token_to_redirection_type((*parser)->token->type);
        advance(parser);

        if (*parser != NULL && (*parser)->token->type == T_WORD) {
            char *file = strdup((*parser)->token->lexeme);
            if (file == NULL) {
                return 0;
            }
            add_redirection(cmd_node, redir_type, file);
            free(file);
            advance(parser);
            return 1;
        }
    }
    return 0; // Aucune redirection valide trouvée ou token inattendu
}


void add_redirection(t_ast_node *node, t_redirection_type type, const char *file) {
    t_redirection *new_redir = malloc(sizeof(t_redirection));
    if (new_redir == NULL) {
        return; // Échec de l'allocation mémoire
    }
    new_redir->type = type;
    new_redir->file = strdup(file);
    if (new_redir->file == NULL) {
        free(new_redir);
        return; // Échec de l'allocation mémoire
    }
    new_redir->next = NULL;

    if (node->redirections == NULL) {
        node->redirections = new_redir;
    } else {
        t_redirection *current = node->redirections;
        while (current != NULL && current->next != NULL) {
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


