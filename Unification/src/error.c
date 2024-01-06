#include "_minishell.h"

/** Initialize error type and message
 * 
 * Required before using has_error
*/
void	error_init(t_error *error)
{
	error->type = ERR_NONE;
	error->msg = NULL;
}

/** Sets error fields
 * 
 * msg should either be NULL or a string that can be freed
*/
void	error_set(t_error *error, t_error_type type, char *msg)
{
	error->type = type;
	error->msg = msg;
}

/** Frees the error message and resets all fieds to defaults
 * 
*/
void	error_cleanup(t_error *error)
{
	free(error->msg);
	error_init(error);
}

void	error_print(t_error *error, char *prompt)
{
	if (error->type == ERR_NONE)
		return ;
	if (error->type == ERR_SYSTEM)
	{
		perror(prompt);
		return ;
	}
	if (prompt)
	{
		ft_putstr_fd(prompt, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putstr_fd(error->msg, 2);
	ft_putstr_fd("\n", 2);
}

bool	has_error(t_error *error)
{
	return (!error || error->type != ERR_NONE);
}