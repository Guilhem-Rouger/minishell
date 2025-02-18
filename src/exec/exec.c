#include "../../include/minishell.h"

bool	exect_builtin(char **args, t_data *data)
{
	if (ft_strncmp(args[0], "echo", 4)  == 0 && ft_strlen(args[0]) == 4)
		echo_command(args);
	else if (ft_strncmp(args[0], "cd", 2) == 0)
		cd_command(args, data);
	else if (ft_strncmp(args[0], "pwd", 3) == 0)
		pwd_command();
	else if (ft_strncmp(args[0], "export", 6) == 0)
		export_command(args, data);
	else if (ft_strncmp(args[0], "unset", 5) == 0)
		unset_command(args, data);
	else if (ft_strncmp(args[0], "env", 3) == 0)
		env_command(args, data);
	else if (ft_strncmp(args[0], "exit", 4) == 0)
		exit_command(data);
	else if (ft_strncmp(args[0], "<<", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], ">>", 2) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], "<", 1) == 0)
		return (TRUE);
	else if (ft_strncmp(args[0], ">", 1) == 0)
		return (TRUE);
	return (FALSE);
}

bool	exec_all(t_token *token, t_data *data)
{
	int	code;

	code = 0;
	if (data->path[data->nb_path] != NULL)
		code = execve(data->path[data->nb_path], token->arg, env_to_tab(data->env));
	exit(code);
}

bool	exec_pipe(t_data *data, t_token *token)
{
	pid_t	pid;
	int		i;
	int		fd;
	int		status;
	t_token *it;

	it = token;
	status = 0;
	fd = -1;
	while (it)
	{
		if (pipe(data->pipe) == -1)
			perror("PIPE !");
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			if (it->next && operator_choice(it->arg, &fd) == -1)
				change_pipe(data, data->pipe[0], data->pipe[1], 1);
			if (it->builtins == TRUE)
			{
				exect_builtin(it->arg, data);
				exit(0);
			}
			else if (it->type == CMD || it->type == PARAM)
			{
				if (!exec_all(it, data))
					return (FALSE);
			}
		}
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
		if (fd != -1)
		{
			i++;
			close(fd);
			dup2(data->fd_out, 1);
			dup2(data->fd_in, 0);
		}
		else
		{
			data->nb_path++;
			change_pipe(data, data->pipe[0], data->pipe[1], 2);
		}
		fd = -1;
		waitpid(pid, &status, 0);
		it = it->next;
	}
	change_pipe(data, data->pipe[0], data->pipe[1], 3);
	return (TRUE);
}

bool	exec_cmd(t_data *data, t_token *token)
{
	pid_t	pid;
	int		fd;
	int		status;
	t_token *it;

	fd = -1;
	it = token;
	status = 0;
	if (data->ope_nbr > 0 && it->next->type )
		fd = operator_choice(it->arg, &fd);
	if (it->builtins == TRUE)
		exect_builtin(it->arg, data);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
			exec_all(it, data);
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			g_exit_value = WEXITSTATUS(status);
	}
	if (fd != -1)
	{
		close(fd);
		dup2(data->fd_out, 1);
		dup2(data->fd_in, 0);
	}
	return (TRUE);
}
