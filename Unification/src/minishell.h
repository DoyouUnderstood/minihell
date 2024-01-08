/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alletond <alletond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 16:08:18 by alletond          #+#    #+#             */
/*   Updated: 2024/01/08 17:10:18 by alletond         ###   ########.fr       */
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
# include "_minishell.h"


// COMMANDE A CORRIGER : > cat missingfile.txt 2> error.log

// Enum parser.
typedef enum parser_type
{
	AND,
	OR,
	PIPELINE,
	COMMAND,
}						t_parser_type;

//Enum redirection.
typedef enum e_redirection_type
{
	E_DLESS,  
	E_LESS,   
	E_DGREAT, 
	E_GREAT,  
}	t_redirection_type;

// Liste chaînée de redirection.
typedef struct s_redirection 
{
    t_redirection_type type;
    char *file;
    struct s_redirection *next;
} t_redirection;


// Liste chaînée d'arguments.
typedef struct s_argument
{
    char *value;
    struct s_argument *next;
} t_argument;

// AST parser.
typedef struct s_ast_node
{
    char *value;
    struct s_ast_node *left;
    struct s_ast_node *right;
    t_redirection *redirections;
    t_argument *arguments;
    t_parser_type type;
} t_ast_node;


void					print_token_type(t_token_type type);
void					free_list(t_list *head);
void					add_token_to_list(t_list **head, char *token);

//parser
t_ast_node *parse_pipeline(t_token_list **parser);
t_ast_node *parse_and_or(t_token_list **parser);
t_ast_node *parse_command(t_token_list **parser);

//utils 
bool is_at_end(t_token_list *parser);
void advance(t_token_list **parser);
t_token_list *consume(t_token_list **parser, t_token_type type);
bool match(t_token_list **parser, t_token_type type);
bool check(t_token_list *parser, t_token_type type);
t_token_list *previous(t_token_list *parser);
t_token_list *peek_next(t_token_list *parser);
t_token_list *peek(t_token_list *parser);
int	is_valid_redirection_token(t_token_type type);
void print_ast(const t_ast_node *node, int level);
t_redirection_type redi_type(const char *type);
t_redirection_type token_to_redirection_type(t_token_type type);


//constructeur

t_ast_node *new_and_or_node(t_parser_type type, t_ast_node *left, t_ast_node *right);
t_ast_node *new_pipeline_node(t_ast_node *left, t_ast_node *right);
t_ast_node *new_command_node(char *value);
void free_ast_node(t_ast_node *node);

//argument et redirection
void handle_argument(t_token_list **parser, t_ast_node *cmd_node);
int handle_redirection(t_token_list **parser, t_ast_node *cmd_node); 
void add_redirection(t_ast_node *node, t_redirection_type type, const char *file);
void add_argument_to_command(t_ast_node *cmd_node, char *argument);

void    free_list(t_list *head);
void	identify_token_type(t_list *token);
void	token_type(t_list *head);
void    add_token_to_list(t_list **head, char *token);

void print_token_types(t_token_list *tokens);

#endif
