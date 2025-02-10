#include "../../include/minishell.h"

bool	check_quote_recurs(const char *str, bool sq, bool dq)
{
	if (*str == '\0')
		return (!sq && !dq);
	if (*str == '\"')
	{
		if (!sq)
			dq = !dq;
	}
	else if (*str == '\'')
	{
		if (!dq)
			sq = !sq;
	}
	return (check_quote_recurs(str + 1, sq, dq));
}

bool	quote_check(char *line)
{
	return (check_quote_recurs(line, FALSE, FALSE));
}
