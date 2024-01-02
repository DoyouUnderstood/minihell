/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:08:18 by alletond          #+#    #+#             */
/*   Updated: 2024/01/02 17:43:26 by alletond         ###   ########.fr       */
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
# include <stdbool.h>
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
}						t_parser_type;

#define MAX_REDIRECTIONS 10
#define MAX_ARGUMENTS 10

// redirection 
typedef struct s_redirection 
{
    char *type;
    char *file; // Nom du fichier.
} s_redirection;

// parser struct
typedef struct s_ast_node
{
	char				*value;
	struct s_ast_node	*left;
	struct s_ast_node	*right;
	s_redirection *redirections[MAX_REDIRECTIONS];
    int num_redirections;
	char *arguments[MAX_ARGUMENTS];
    int num_arguments;
	t_parser_type		type;
}						t_ast_node;

typedef struct s_parser 
{
    t_list *token_list;
    t_list *current;
    t_list *previous;
} t_parser;






void					print_token_type(t_token_type type);
void					free_list(t_list *head);
void					add_token_to_list(t_list **head, char *token);

//parser
t_ast_node *parse_pipeline(t_parser *parser);
t_ast_node *parse_and_or(t_parser *parser);
t_ast_node *parse_command(t_parser *parser);

//utils 
bool is_at_end(t_parser *parser);
t_list *advance(t_parser *parser);
t_list *consume(t_parser *parser, t_token_type type, const char *error_message);
bool match(t_parser *parser, t_token_type type);
bool check(t_parser *parser, t_token_type type);
t_list *previous(t_parser *parser);
t_list *peek_next(t_parser *parser);
t_list *peek(t_parser *parser);
int	is_valid_redirection_token(t_token_type type);
void print_ast(const t_ast_node *node, int level);


//constructeur

t_ast_node *new_and_or_node(t_parser_type type, t_ast_node *left, t_ast_node *right);
t_ast_node *new_pipeline_node(t_ast_node *left, t_ast_node *right);
t_ast_node *new_command_node(char *value);
void free_ast_node(t_ast_node *node);

//argument et redirection
void handle_argument(t_parser *parser, t_ast_node *cmd_node);
void handle_redirection(t_parser *parser, t_ast_node *cmd_node);
void add_redirection(t_ast_node *node, const char *type, const char *file);
void add_argument_to_command(t_ast_node *cmd_node, char *argument);

void free_list(t_list *head);
void	identify_token_type(t_list *token);
void	token_type(t_list *head);
void add_token_to_list(t_list **head, char *token);

#endif
