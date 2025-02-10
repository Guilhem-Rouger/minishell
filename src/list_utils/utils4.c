#include "../../include/minishell.h"

void	token_quote(char *str, t_token *new)
{
	if (str[0] == '\'' || str[0] == '\"')
	{
		new->str = ft_substr(str, 1, ft_strlen(str) - 2);
		if (str[0] == '\'')
		{
			new->sq = TRUE;
			new->dq = FALSE;
		}
		else if (str[0] == '\"')
		{
			new->sq = FALSE;
			new->dq = TRUE;
		}
	}
	else
	{
		new->str = str;
		new->dq = FALSE;
		new->sq = FALSE;
	}
}

void	count_operator(t_data *data)
{
	t_token	*it;

	it = data->token;
	while (it)
	{
		if (it->type == 1 || it->type == 2 || it->type == 3 || it->type == 4)
			data->ope_nbr++;
		it = it->next;
	}
}

bool	ifbuiltin(char **args)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "export", 6) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		return (TRUE);
	return (FALSE);
}

int	ft_strtablen(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

char	*var_end(char *str, char *var, char *end, char *tmp)
{
	int	i;

	i = is_dollar(str);
	if (ft_strlen(tmp) != ft_strlen(str))
		end = ft_strdup(&str[i + ft_isalphalen(&str[i])]);
	free(tmp);
	if (i - 1 != 0)
	{
		tmp = ft_substr(str, 0, i - 1);
		tmp = ft_strjoin(tmp, var);
	}
	else
		tmp = var;
	if (end)
	{
		tmp = ft_strjoin(ft_strdup(tmp), end);
		free(end);
	}
	return (tmp);
}
