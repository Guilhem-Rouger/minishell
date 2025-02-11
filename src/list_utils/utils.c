#include "../../include/minishell.h"

int	ft_isalphalen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isalpha(str[i]) != 0 || str[i] == '_')
			i++;
		else
			break ;
	}
	return (i);
}

char	*replace_var(char *str)
{
	char			*tmp;
	char			*var;
	char			*end;
	int				i;

	i = is_dollar(str);
	if (str[0] == '\\')
		return (ft_substr(str, 1, ft_strlen(str) - 1));
	if (i == -1)
		return (str);
	tmp = ft_substr(str, i, ft_isalphalen(&str[i]));
	end = NULL;
	if (getenv(tmp) != NULL)
		var = getenv(tmp);
	else
	{
		var = ft_substr(str, 0, i - 1);
		if (ft_strlen(var) == ft_strlen(str) - (ft_strlen(tmp)))
			return (var);
		var = ft_strjoin(var, &str[i + ft_strlen(tmp)]);
		return (var);
	}
	tmp = var_end(str, var, end, tmp);
	free(str);
	return (tmp);
}

int	tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	is_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_strlen(str) == 1)
			return (-1);
		else if (str[i + 1] == '$')
			i++;
		else if (str[i] == '$')
			return (i + 1);
		else
			i++;
	}
	return (-1);
}

void	setup_arg(t_token *token)
{
	char				**arg;
	t_token				*it;
	int					i;
	int					len;

	if (last_token(token) != token)
		it = token->next;
	else
		it = NULL;
	len = countarg(it) + 1;
	arg = ft_calloc(sizeof(char *), len + 1);
	i = 1;
	if (token->builtins == FALSE)
		arg[0] = ft_strdup(token->path);
	else
		arg[0] = ft_strdup(token->str);
	while (len > i && (it->type == ARG || it->type == PARAM))
	{
		arg[i] = ft_strdup(it->str);
		i++;
		it = it->next;
	}
	token->arg = arg;
	return ;
}
