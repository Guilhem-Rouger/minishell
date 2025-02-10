#include "../../include/minishell.h"

void	split_1(char *start, int *j, char **result, t_split *s)
{
	if (!s->in_quote)
	{
		s->in_quote = 1;
		s->quote_char = s->c;
		s->c++;
	}
	else if (s->c == s->quote_char)
	{
		s->in_quote = 0;
		result[(*j)++] = create_token(start - 1, start);
		s->c++;
	}
}

char	*split_2(char *start, bool in_quotes)
{
	if (in_quotes)
		return (start - 1);
	else
		return (start);
}
