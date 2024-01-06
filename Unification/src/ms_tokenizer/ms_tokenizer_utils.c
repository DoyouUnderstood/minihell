#include "_minishell.h"

bool	ms_is_whitespace(char c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

bool	ms_is_metacharacter(char c)
{
	return (
		ms_is_whitespace(c)
		|| c == '|'
		|| c == '&'
		|| c == ';'
		|| c == '('
		|| c == ')'
		|| c == '<'
		|| c == '>'
		);
}
