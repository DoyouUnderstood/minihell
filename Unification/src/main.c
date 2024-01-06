#include "_minishell.h"
#include "minishell.h"

int	main(int argc, char **argv)
{
	char			*cmd_line;
	t_token_list	*token_list;
	t_error			error;
	t_token_list	*current;

	(void) argc;
	// TODO: Setup signal handling
	cmd_line = readline("> ");
	while (cmd_line && *cmd_line)
	{
		token_list = ms_tokenize(cmd_line, &error);
		if (has_error(&error))
			error_print(&error, argv[0]);
		else
		{
			current = token_list;
			while (current)
			{
				current = current->next;
			}
		}
		t_ast_node *ast = parse_and_or(&token_list);
		if (!ast)
		{
			printf("error\n");
			return 0;
		}
        print_ast(ast, 0);
		token_list_clear(&token_list);
		// TODO: Tokenize command line
		// TODO: Parameter expansion
		// TODO: Split words
		// TODO: Filename expansion
		// TODO: Split words
		// TODO: Parse tokens to AST
		// TODO: Execute AST
		printf("Your commande: %s\n", cmd_line);
		
		free(cmd_line);
		cmd_line = readline("> ");
	}
}