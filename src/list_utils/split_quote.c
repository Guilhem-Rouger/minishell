#include "../../include/minishell.h"

void	splite_quote2(char **tab, const char *line, t_quote *q)
{
	if (q->in_quote && line[q->i] == q->quote_char)
	{
		if (line[q->start-1] == ' ')
			tab[q->j++] = ft_strndup(&line[q->start], q->i - q->start + 1);
		else
		{
			tab[q->j-1] = ft_strjoin(ft_strdup(&q->quote_char), tab[q->j-1]);
			tab[q->j-1] = ft_strjoin(tab[q->j-1], ft_strndup(&line[q->start + 1], q->i - q->start));
		}
		q->start = q->i + 1;
		q->in_quote = FALSE;
	}
	else if (!q->in_quote)
	{
		if (q->i > q->start)
			tab[q->j++] = ft_strndup(&line[q->start], q->i - q->start);
		q->quote_char = line[q->i];
		q->in_quote = TRUE;
		q->start = q->i;
	}
}

char	**split_quote(const char *line, t_quote *q)
{
	char		**tab;
	size_t		len;

	q->in_quote = FALSE;
	len = strlen(line);
	tab = malloc((len + 1) * sizeof(char *));
	while (q->i <= len)
	{
		if (line[q->i] == '\'' || line[q->i] == '\"')
			splite_quote2(tab, line, q);
		else if (!q->in_quote && (line[q->i] == ' ' || line[q->i] == '\0'))
		{
			if (q->i > q->start)
				tab[q->j++] = ft_strndup(&line[q->start], q->i - q->start);
			q->start = q->i + 1;
		}
		q->i++;
	}
	if (q->start < len)
		tab[q->j++] = ft_strndup(&line[q->start], q->i - q->start);
	tab[q->j] = NULL;
	return (tab);
}
