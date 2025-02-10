#include "../../include/minishell.h"

bool	emptyline(char *line)
{
	if (ft_strlen(line) == 0)
		return (FALSE);
	else
		return (TRUE);
}

bool	spliting_cmd(char *line, t_data *data)
{
	t_quote	*q;
	char	**tab;
	char	**tab_temp;
	int		i;

	q = malloc(sizeof(t_quote) * 1);
	i = 0;
	q->start = 0;
	q->i = 0;
	q->j = 0;
	q->quote_char = '\0';
	tab = split_quote(line, q);
	free(q);
	tab_temp = split_sep(tab, "<|>& ");
	clear_tab(tab);
	data->cmd = NULL;
	if (!tab_temp)
		return (FALSE);
	while (tab_temp[i])
	{
		ft_lstadd_back(&(data->cmd), ft_lstnew(tab_temp[i]));
		i++;
	}
	free(tab_temp);
	return (TRUE);
}

bool	replace_env_var(t_data *data)
{
	t_token	*token;
	int		var;
	int		i;

	token = data->token;
	i = 0;
	var = 0;
	while (token)
	{
		if (var == 0)
			var = count_replace(token->str);
		if (token->sq != TRUE && is_exitcode(token->str) >= 0)
		{
			token->str = replace_exitcode(token->str);
			i++;
		}
		else if (token->sq != TRUE && is_pid(token->str) >= 0)
		{
			token->str = replace_pid(token->str);
			i++;
		}
		else if (token->sq != TRUE && is_dollar(token->str) >= 0)
		{
			token->str = replace_var(token->str);
			i++;
		}
		if (i == var || token->sq == TRUE)
		{
			token = token->next;
			i = 0;
			var = 0;
		}
	}
	return (TRUE);
}

void	count_pipe(char *line, t_data *data)
{
	int	i;

	i = 0;
	data->pipe_nbr = 0;
	data->id_pipe = 0;
	while (line[i])
	{
		if (line[i] == '|')
			data->pipe_nbr++;
		i++;
	}
}

bool	parsing(char *line, t_data *data)
{
	if (!check_line(line))
		return (FALSE);
	if (!quote_check(line))
		return (FALSE);
	if (!spliting_cmd(line, data))
		return (FALSE);
	if (!token_setup(data))
		return (FALSE);
	if (!token_verif(data->token))
		return (FALSE);
	if (!replace_env_var(data))
		return (FALSE);
	count_pipe(line, data);
	count_operator(data);
	data->fd_in = dup(0);
	data->fd_out = dup(1);
	data->path = ft_calloc(sizeof(char *), data->pipe_nbr + data->ope_nbr + 1);
	return (TRUE);
}
