#include "../../include/minishell.h"

int	is_separator(char c, const char *separators)
{
	while (*separators)
	{
		if (c == *separators)
			return (1);
		separators++;
	}
	return (0);
}

char	*create_token(const char *start, const char *end)
{
	char	*token;
	int		len;

	len = end - start + 1;
	token = ft_calloc(sizeof(char *), len + 1);
	if (token)
		ft_strlcpy(token, start, len + 1);
	return (token);
}

void	split_single(char *start, char **result, const char *sep, int *j)
{
	char		*token_start;
	t_split		*s;

	s = malloc(sizeof(t_split));
	s->in_quote = 0;
	s->quote_char = '\0';
	while (*start)
	{
		if (*start == '\'' || *start == '\"')
		{
			if (!s->in_quote)
			{
				s->in_quote = 1;
				s->quote_char = *start;
				start++;
			}
			else if (s->c == s->quote_char)
			{
				s->in_quote = 0;
				result[(*j)++] = create_token(start - 1, start);
				start++;
			}
		}
		if (!s->in_quote && is_separator(*start, sep))
		{
			result[(*j)++] = create_token(start, start);
			start++;
			continue ;
		}
		token_start = split_2(start, s->in_quote);
		while (*start && (s->in_quote || !is_separator(*start, sep)))
			start++;
		if (token_start < start)
			result[(*j)++] = create_token(token_start, start - 1);
	}
}

char	**split_sep(char **inputs, const char *separators)
{
	char	**result;
	int		j;
	int		i;

	result = malloc(1024 * sizeof(char *));
	if (!result || !inputs || !separators)
		return (NULL);
	i = 0;
	j = 0;
	while (inputs[i] != NULL)
	{
		split_single(inputs[i], result, separators, &j);
		i++;
	}
	result[j] = NULL;
	return (result);
}
