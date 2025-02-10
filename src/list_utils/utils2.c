#include "../../include/minishell.h"

char	*replace_exitcode(char *str)
{
	char	*tmp;
	int		i;

	i = is_exitcode(str);
	tmp = ft_substr(str, i + 2, ft_strlen(&str[i + 1]));
	str = ft_substr(str, 0, i);
	str = ft_strjoin(str, ft_itoa(g_exit_value));
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

int	is_exitcode(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '?')
			return (-1);
		else if (str[i] == '$' && str[i + 1] == '?')
			return (i);
		i++;
	}
	return (-1);
}

t_token	*next_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (tmp)
	{
		if (tmp->type == CMD)
			return (tmp);
		tmp = tmp->next;
	}
	return (NULL);
}

bool	other_cmd(t_token *token)
{
	t_token	*tmp;

	tmp = token->next;
	while (token)
	{
		if (tmp->type == CMD)
			return (TRUE);
		tmp = tmp->next;
	}
	return (FALSE);
}

int	countarg(t_token *token)
{
	t_token	*it;
	int		i;

	if (!token)
		return (0);
	it = token;
	i = 0;
	while (it)
	{
		if (it->type != ARG && it->type != PARAM)
			break ;
		i++;
		if (!it->next)
			break ;
		it = it->next;
	}
	return (i);
}
