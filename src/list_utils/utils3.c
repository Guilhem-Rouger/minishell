#include "../../include/minishell.h"

int	next_dollar(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
			return (i);
		i++;
	}
	return (i);
}

int	count_replace(char *str)
{
	int	i;
	int	var;

	i = 0;
	var = 0;
	while (str[i])
	{
		if (str[i] != '$')
			i++;
		else if (is_pid(&str[i]) >= 0)
		{
			var++;
			i = i + 2;
		}
		else if (is_dollar(&str[i]) >= 0)
		{
			var++;
			i++;
			i = i + next_dollar(&str[i]);
		}
		else
			i++;
	}
	return (var);
}

char	*replace_pid(char *str)
{
	pid_t	pid;
	char	*tmp;
	int		i;

	i = is_pid(str);
	tmp = ft_substr(str, i + 2, ft_strlen(&str[i + 1]));
	pid = getpid();
	str = ft_substr(str, 0, i);
	str = ft_strjoin(str, ft_itoa(pid));
	str = ft_strjoin(str, tmp);
	free(tmp);
	return (str);
}

int	is_pid(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '$' && str[i + 1] != '$')
			return (-1);
		else if (str[i] == '$' && str[i + 1] == '$')
			return (i);
		i++;
	}
	return (-1);
}

void	change_pipe(t_data *data, int in, int out, int status)
{
	if (status == 1)
	{
		close(in);
		dup2(out, 1);
		close(out);
	}
	if (status == 2)
	{
		close(out);
		dup2(in, 0);
		close(in);
	}
	if (status == 3)
	{
		close(in);
		close(out);
		dup2(data->fd_in, 0);
		dup2(data->fd_out, 1);
		close(data->fd_out);
		close(data->fd_in);
	}
}
