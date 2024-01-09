#include "minishell.h"


// constructeur and_or.

t_ast_node *new_and_or_node(t_parser_type type, t_ast_node *left, t_ast_node *right) 
{
    if (left == NULL || right == NULL) {
        return NULL;
    }

    t_ast_node *new_node = malloc(sizeof(t_ast_node));
    if (!new_node) {
        return NULL;
    }

    new_node->value = (type == AND) ? "&&" : "||";
    new_node->left = left;
    new_node->right = right;
    new_node->redirections = NULL;
    new_node->arguments = NULL;
    new_node->type = type;

    return new_node;
}


//pipeline constructeur.

t_ast_node *new_pipeline_node(t_ast_node *left, t_ast_node *right) 
{
    if (left == NULL || right == NULL) {
        return NULL;
    }

    t_ast_node *new_node = malloc(sizeof(t_ast_node));
    if (!new_node) {
        return NULL;
    }

    new_node->value = "|";
    new_node->left = left;
    new_node->right = right;
    new_node->redirections = NULL; 
    new_node->arguments = NULL;
    new_node->type = PIPELINE;

    return new_node;
}



// commande constructeur.

t_ast_node *new_command_node(char *value) 
{
    t_ast_node *new_node = malloc(sizeof(t_ast_node));
    if (!new_node) {
        return NULL;
    }

    new_node->value = value ? strdup(value) : NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    new_node->redirections = NULL;
    new_node->arguments = NULL;
    new_node->type = COMMAND;

    return new_node;
}


// destructeur node.

void free_ast_node(t_ast_node *node) 
{
        return;
    if (node == NULL) 
    free_ast_node(node->left);
    free_ast_node(node->right);
    if (node->value) {
        free(node->value);
    }
    t_redirection *current_redirection = node->redirections;
    while (current_redirection != NULL) {
        t_redirection *next_redirection = current_redirection->next;
        free(current_redirection->file);
        free(current_redirection);
        current_redirection = next_redirection;
    }
    t_argument *current_argument = node->arguments;
    while (current_argument != NULL) {
        t_argument *next_argument = current_argument->next;
        free(current_argument->value);
        free(current_argument);
        current_argument = next_argument;
    }
    free(node);
}
