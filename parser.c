/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ast_tree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/16 18:28:06 by alletond          #+#    #+#             */
/*   Updated: 2023/12/16 20:32:45 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


t_ast_node	*parse_and_or(t_list **tokens)
{
	t_ast_node	*node;
	t_ast_node	*new_node;

	node = parse_pipeline(tokens);
	while (*tokens != NULL)
	{
		if ((*tokens)->type == T_AND || (*tokens)->type == T_OR)
		{
			new_node = malloc(sizeof(t_ast_node));
			if ((*tokens)->type == T_AND)
				new_node->type = AND;
			else
				new_node->type = OR;
			new_node->left = node;
            printf("type : %d", new_node->type);
			*tokens = (*tokens)->next;
			new_node->right = parse_pipeline(tokens);
			node = new_node;
		}
		else
			break ;
	}
	return (node);
}

t_ast_node	*parse_pipeline(t_list **tokens)
{
	t_ast_node	*node;
	t_ast_node	*new_node;

	node = parse_full_command(tokens);
	while (*tokens != NULL)
	{
		if ((*tokens)->type == T_PIPE)
		{
			new_node = malloc(sizeof(t_ast_node));
			new_node->type = PIPELINE;
			new_node->left = node;
			*tokens = (*tokens)->next;
			new_node->right = parse_full_command(tokens);
			node = new_node;
		}
		else
			break ;
	}
	return (node);
}

t_ast_node	*parse_full_command(t_list **tokens)
{
	t_ast_node	*node;
	t_ast_node	*new_node;

	node = parse_redirection(tokens);
	while (*tokens != NULL)
	{
		if (((*tokens)->type) == T_WORD)
		{
			new_node = malloc(sizeof(t_ast_node));
			new_node->type = T_WORD;
			new_node->left = node;
			*tokens = (*tokens)->next;
			new_node->right = parse_redirection(tokens);
			node = new_node;
		}
		else
			break ;
	}
	return (node);
}

t_ast_node	*parse_redirection(t_list **tokens)
{
	t_ast_node	*node;
	t_ast_node	*new_node;

	node = parse_simple_command(tokens);
	while (*tokens != NULL)
	{
		if (valid_redirection((*tokens)->type))
		{
			new_node = malloc(sizeof(t_ast_node));
			new_node->type = REDIRECTION;
			new_node->left = node;
			new_node->right = parse_simple_command(tokens);
			node = new_node;
		}
		else
			break ;
	}
	return (node);
}

int	valid_redirection(t_token_type type)
{
	if (type == T_DLESS || type == T_LESS || type == T_DGREAT
		|| type == T_GREAT)
		return (1);
	return (0);
}

/*
Pour parse_simple_command, 2 cas :
	1. juste des commandes simples avec arguments qu'il faut stocker dans liste chainnees (?).
	2. commande avec des "()" qu'il faut renvoyer a and_or.

*/

t_ast_node *parse_simple_command(t_list **tokens) 
{
    t_ast_node *command_node = NULL;
    t_ast_node *current_node = NULL;

    while (*tokens != NULL) 
    {
        if ((*tokens)->type == T_WORD) 
        {
            if (!command_node) 
            {
                command_node = new_ast_node(SIMPLE_COMMAND, (*tokens)->token);
                current_node = command_node;
            } else 
            {
                t_ast_node *arg_node = new_ast_node(COMMAND, (*tokens)->token);
                current_node->right = arg_node;
                current_node = arg_node;
            }
        }
        else if ((*tokens)->type == T_O_PARENT) 
        {
            *tokens = (*tokens)->next;  // Passer la parenthèse ouvrante

            // Appeler parse_and_or pour traiter la commande à l'intérieur des parenthèses
            t_ast_node *sub_command = parse_and_or(tokens);

            // Vérifier que la commande entre parenthèses a été correctement analysée
            if (!sub_command) {
                return NULL;
        }

        // Si c'est la première commande, créer le nœud command_node
        if (!command_node) {
            command_node = sub_command;
        } else {
            // Sinon, l'ajouter comme argument de la commande actuelle
            t_ast_node *arg_node = new_ast_node(COMMAND, NULL);
            arg_node->left = sub_command;
            current_node->right = arg_node;
            current_node = arg_node;
        }
        while (*tokens != NULL && (*tokens)->type != T_C_PARENT) {
            *tokens = (*tokens)->next;
        }

        if (*tokens == NULL) {
            // Parenthèse fermante manquante
            return NULL;
        }

        *tokens = (*tokens)->next;  // Passer la parenthèse fermante
}
     else
         break;
    *tokens = (*tokens)->next;  // Avancer au token suivant
    }

    return command_node;
}
