/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:08:18 by alletond          #+#    #+#             */
/*   Updated: 2023/12/16 19:24:24 by alletond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>

//token enum
typedef enum e_token_type
{
	T_WORD,
	T_DLESS,
	T_LESS,
	T_DGREAT,
	T_GREAT,
	T_PIPE,
	T_O_PARENT,
	T_PREV_STATUS,
	T_C_PARENT,
	T_STRING,
	T_STRING_FRAGMENT,
	T_AND,
	T_OR,
	T_SINGLE_AND,
	T_ENV_VAR,
	T_SINGLE_QUOTE,
	T_DOUBLE_QUOTE,
	T_WILDCARD,
	T_EOF,
	/*BUILTINS*/
	T_CD,
	T_ECHO,
	T_ENV,
	T_EXIT,
	T_EXPORT,
	T_PWD,
	T_UNSET,
}						t_token_type;

//token struct
typedef struct s_list
{
	char				*token;
	char				*literal;
	t_token_type		type;
	struct s_list		*next;

}						t_list;

//parser enum
typedef enum parser_type
{
	AND,
	OR,
	PIPELINE,
	COMMAND,
	SIMPLE_COMMAND,
	REDIRECTION,
}						t_parser_type;

// parser struct
typedef struct s_ast_node
{
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	t_parser_type		type;
}						t_ast_node;

//linked list pour argument
typedef struct s_arguments
{
    char *value;
    struct s_argument *next;
} t_arguments;


void					print_token_type(t_token_type type);
void					free_list(t_list *head);
t_list					*add_token_to_list(t_list **head, char *token);

#endif
