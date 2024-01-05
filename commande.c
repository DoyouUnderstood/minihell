#include "minishell.h"

void free_list(t_list *head)
{
    t_list *tmp;

    while (head != NULL) 
	{
        tmp = head;
        head = head->next;
        free(tmp->token);
        free(tmp);
    }
}

void	identify_token_type(t_list *token)
{
	if (token == NULL || token->token == NULL)
		return ;
	// Détermination du type de token
	if (strncmp(token->token, "<<", 2) == 0)
		token->type = T_DLESS;
	else if (strncmp(token->token, "<", 1) == 0)
		token->type = T_LESS;
	else if (strncmp(token->token, ">>", 2) == 0)
		token->type = T_DGREAT;
	else if (strncmp(token->token, ">", 1) == 0)
		token->type = T_GREAT;
	else if (strncmp(token->token, "||", 2) == 0)
		token->type = T_OR;
	else if (strncmp(token->token, "|", 1) == 0)
		token->type = T_PIPE;
	else if (strncmp(token->token, "(", 1) == 0)
		token->type = T_O_PARENT;
	else if (strncmp(token->token, ")", 1) == 0)
		token->type = T_C_PARENT;
	else if (strncmp(token->token, "&&", 2) == 0)
		token->type = T_AND;
	// else if (token->token[0] == '$')
	// 	token->type = T_ENV_VAR;
	// else if (strncmp(token->token, "'", 1) == 0)
	// 	token->type = T_SINGLE_QUOTE;
	// else if (token->token[0] == '"')
	// 	token->type = T_DOUBLE_QUOTE;s
	else if (strncmp(token->token, "*", 1) == 0)
		token->type = T_WILDCARD;
	else if (strncmp(token->token, "$?", 2) == 0)
		token->type = T_PREV_STATUS;
	else
		token->type = T_WORD; // Type par défaut ?
	// Appel récursif pour le token suivant
	if (token->next != NULL)
		identify_token_type(token->next);
}

void	token_type(t_list *head)
{
	t_list	*current;

	current = head;
	while (current != NULL)
	{
		identify_token_type(current);
		//printf("token :%stype : %u\n",current->token, current->type);
		current = current->next;
	}
}

void add_token_to_list(t_list **head, char *token) 
{
    t_list *new_node = malloc(sizeof(t_list));
    if (!new_node) 
	{
        perror("Failed to allocate memory for new node");
        return;
    }

    new_node->token = strdup(token);
    new_node->type = T_WORD; // Default type, can be changed later
    new_node->next = NULL;

    if (*head == NULL) 
	{
        *head = new_node;
    } 
	else 
	{
        t_list *current = *head;
        while (current->next != NULL) 
		{
            current = current->next;
        }
        current->next = new_node;
    }
}

int main() 
{
    char *input_line;
    char *token;
    const char *delim = " ";

    while (1) {
        input_line = readline("minishell> ");
        if (!input_line)
            break;

        t_list *head = NULL;
        token = strtok(input_line, delim);
        while (token != NULL) {
            add_token_to_list(&head, token);
            token = strtok(NULL, delim);
        }
        token_type(head);

        t_parser parser;
        parser.token_list = head;
        parser.current = head;
        parser.previous = NULL;

        t_ast_node *ast = parse_and_or(&parser);
		if (!ast)
		{
			printf("error\n");
			return 0;
		}
        print_ast(ast, 0);
        // free_ast_node(ast);
        // free_list(head);
        // free(input_line);
    }

    return 0;
}