#include "../../include/minishell.h"

bool	check_allcmd(char *cmd, t_data *data, t_token *it)
{
	char	**tab_path;
	char	*path;
	char	*temp;
	int		i;

	tab_path = data->list_path;
	i = 0;
	while (tab_path[i])
	{
		if (ft_strncmp(tab_path[i], "/bin", 4) != 0)
		{
			i++;
			continue ;
		}
		temp = ft_strdup(tab_path[i]);
		path = ft_strjoin(temp, "/");
		path = ft_strjoin(path, cmd);
		if (access(path, X_OK) == 0)
		{
			it->path = path;
			return (TRUE);
		}
		free(path);
		i++;
	}
	return (FALSE);
}

bool	check_builtin(char *cmd, t_token *it, t_data *data)
{
	if ((ft_strncmp(cmd, "cd", 2) == 0 && ft_strlen(cmd) == 2) || \
		(ft_strncmp(cmd, "export", 6) == 0 && ft_strlen(cmd)  == 6) ||\
		(ft_strncmp(cmd, "unset", 5) == 0 && ft_strlen(cmd) == 5) ||\
		it->type == 3 || it->type == 4 || \
		it->type == 1 || it->type == 2)
	{
		it->builtins = 1;
		return (TRUE);
	}
	else if ((ft_strncmp(cmd, "env", 3) == 0 || ft_strncmp(cmd, "pwd", 3) == 0) && ft_strlen(cmd) == 3)
	{
		it->builtins = 1;
		return (TRUE);
	}
	else if ((ft_strncmp(cmd, "echo", 4) == 0 || ft_strncmp(cmd, "exit", 4) == 0) && ft_strlen(cmd) == 4)
	{
		it->builtins = 1;
		return (TRUE);
	}
	else if (check_allcmd(cmd, data, it) == TRUE)
		return (TRUE);
	else
	{
		printf("\033[0;36mbash \033[0;0m: \033[0;31mcommand not \
found \033[0;0m : %s \n", cmd);
		return (FALSE);
	}
}

bool	check_cmd(t_data *data)
{
	t_token	*it;
	bool	bol;
	int		i;

	i = 0;
	bol = 0;
	it = data->token;
	while (it)
	{
		if ((it->type == CMD || it->type == TRUNC || it->type == APPEND || \
			it->type == 1 || it->type == 2) && \
			!check_builtin(it->str, it, data))
		{
			bol = 1;
		}
		if (it->type == CMD || it->type == PARAM)
			data->path[i++] = it->path;
		it = it->next;
	}
	if (bol == 1)
		return (FALSE);
	return (TRUE);
}

bool	setup_tabarg(t_data *data)
{
	t_token	*it;

	if (!data || !data->token)
		return (FALSE);
	data->nb_path = 0;
	it = data->token;
	if (data->pipe_nbr < 0 || data->ope_nbr < 0)
		return (FALSE);
	while (it)
	{
		while (it && it->type != 6 && it->type != 3 && it->type != 4 && \
			it->type != 1 && it->type != 2)
			it = it->next;
		if (!it)
			break ;
		setup_arg(it);
		it = it->next;
	}
	return (TRUE);
}

//void	exec(t_data *data)
//{
//	t_list	*cmd;
//	
//	cmd = data->cmd;
//	spec_built_first(data);
//	if (index->nb_cmd)
//		ft_ft_exec(data);
//}

bool	task_cmd(t_data *data)
{
	if (!check_cmd(data))
		return (FALSE);
	if (!setup_tabarg(data))
		return (FALSE);
	//print_data(data); // print les données de la structure data
	if (data->pipe_nbr == 0 && !exec_cmd(data, data->token))
		return (FALSE);
	if (data->pipe_nbr != 0 && !exec_pipe(data, data->token))
		return (FALSE);
	return (TRUE);
}
