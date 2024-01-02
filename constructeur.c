#include "minishell.h"


// constructeur and_or.

t_ast_node *new_and_or_node(t_parser_type type, t_ast_node *left, t_ast_node *right) 
{
    t_ast_node *new_node = malloc(sizeof(t_ast_node));
    if (!new_node) return NULL;

    new_node->value = NULL;
    new_node->left = left;
    new_node->right = right;
    for (int i = 0; i < MAX_REDIRECTIONS; i++) {
        new_node->redirections[i] = NULL;
    }
    new_node->num_redirections = 0;
    for (int i = 0; i < MAX_ARGUMENTS; i++) {
        new_node->arguments[i] = NULL;
    }
    new_node->num_arguments = 0;
    new_node->type = type;

    return new_node;
}

//pipeline constructeur. 

t_ast_node *new_pipeline_node(t_ast_node *left, t_ast_node *right) {
    t_ast_node *new_node = malloc(sizeof(t_ast_node));
    if (!new_node) return NULL;

    new_node->value = NULL;
    new_node->left = left;
    new_node->right = right;
    for (int i = 0; i < MAX_REDIRECTIONS; i++) {
        new_node->redirections[i] = NULL;
    }
    new_node->num_redirections = 0;
    for (int i = 0; i < MAX_ARGUMENTS; i++) {
        new_node->arguments[i] = NULL;
    }
    new_node->num_arguments = 0;
    new_node->type = PIPELINE;

    return new_node;
}


// commande constructeur.
t_ast_node *new_command_node(char *value) 
{
    t_ast_node *new_node = malloc(sizeof(t_ast_node));
    if (!new_node) return NULL;

    new_node->value = value ? strdup(value) : NULL;
    new_node->left = NULL;
    new_node->right = NULL;
    // Initialisation des tableaux de redirections et arguments
    for (int i = 0; i < MAX_REDIRECTIONS; i++) {
        new_node->redirections[i] = NULL;
    }
    new_node->num_redirections = 0;
    for (int i = 0; i < MAX_ARGUMENTS; i++) {
        new_node->arguments[i] = NULL;
    }
    new_node->num_arguments = 0;
    new_node->type = COMMAND;

    return new_node;
}



// destructeur node.
void free_ast_node(t_ast_node *node) {
    if (node == NULL) 
        return;

    // Libérer les sous-arbres récursivement
    free_ast_node(node->left);
    free_ast_node(node->right);

    // Libérer la mémoire allouée pour les chaînes de caractères
    if (node->value) {
        free(node->value);
    }

    // Libérer les redirections
    for (int i = 0; i < node->num_redirections; i++) {
        if (node->redirections[i]) {
            // Supposons que s_redirection est une structure simple
            free(node->redirections[i]->type);
            free(node->redirections[i]->file);
            free(node->redirections[i]);
        }
    }

    // Libérer les arguments
    for (int i = 0; i < node->num_arguments; i++) {
        if (node->arguments[i]) {
            free(node->arguments[i]);
        }
    }

    // Finalement, libérer le nœud lui-même
    free(node);
}


