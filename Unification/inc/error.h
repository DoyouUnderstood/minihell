#ifndef ERROR_H
# define ERROR_H

typedef enum e_error_type
{
	ERR_NONE,
	ERR_SYSTEM,
	ERR_CUSTOM
}	t_error_type;

typedef struct s_error
{
	t_error_type	type;
	char			*msg;
}	t_error;

void	error_init(t_error *error);
void	error_set(t_error *error, t_error_type type, char *msg);
void	error_cleanup(t_error *error);
void	error_print(t_error *error, char *prompt);
bool	has_error(t_error *error);

#endif