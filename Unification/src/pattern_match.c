#include "_minishell.h"

static bool	handle_star(char *pattern, char *str);
static bool	handle_double_quotes(char *pattern, char *str);
static bool	handle_single_quotes(char *pattern, char *str);
	
static bool	handle_char(char *pattern, char *str)
{
	while (1)
	{
		if (*pattern == '*')
			return (handle_star(pattern, str));
		if (*pattern == '"')
			return (handle_double_quotes(pattern, str));
		if (*pattern == '\'')
			return (handle_single_quotes(pattern, str));
		if (*pattern != *str)
			return (false);
		if (!*pattern)
			return (true);
		pattern++;
		str++;
	}
}

static bool handle_double_quotes(char *pattern, char *str)
{
	pattern++;
	while (*pattern != '"')
	{
		if (*pattern != *str)
			return (false);
		if (!*pattern)
			return (true);
		pattern++;
		str++;
	}
	pattern++;
	return (handle_char(pattern, str));
}

static bool handle_single_quotes(char *pattern, char *str)
{
	pattern++;
	while (*pattern != '\'')
	{
		if (*pattern != *str)
			return (false);
		if (!*pattern)
			return (true);
		pattern++;
		str++;
	}
	pattern++;
	return (handle_char(pattern, str));
}

static bool	handle_star(char *pattern, char *str)
{
	while (*pattern == '*')
		pattern++;
	if (!*pattern)
		return (true);
	while (*str)
	{
		if (*str == *pattern && handle_char(pattern, str))
			return (true);
		str++;
	}
	return (false);
}

bool	pattern_match(char *pattern, char *str)
{
	if (*pattern == '*')
		return (handle_star(pattern, str));
	else if (*pattern == '"')
		return (handle_double_quotes(pattern, str));
	else if (*pattern == '\'')
		return (handle_single_quotes(pattern, str));
	return (handle_char(pattern, str));
}