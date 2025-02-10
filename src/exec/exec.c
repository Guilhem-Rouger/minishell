#include "../../include/minishell.h"

bool	exect_builtin(char **args, t_data *data)
{
	if (ft_strncmp(args[0], "echo", 4) == 0)
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

bool	exec_all(char **args, t_data *data)
{
	int	code;

	code = 0;
	if (data->path[data->nb_path] != NULL)
		code = execve(data->path[data->nb_path], args, env_to_tab(data->env));
	exit(code);
}

bool	exec_pipe(t_data *data, char ***tab)
{
	pid_t	pid;
	int		i;
	int		fd;
	int		status;

	tab = data->args;
	i = 0;
	status = 0;
	fd = -1;
	while (tab[i])
	{
		if (pipe(data->pipe) == -1)
			perror("PIPE !");
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
		{
			if (tab[i + 1] && operator_choice(tab[i + 1], &fd) == -1)
				change_pipe(data, data->pipe[0], data->pipe[1], 1);
			if (data->ope_nbr > 1)
				fd = operator_choice(tab[i + 2], &fd);
			if (ifbuiltin(tab[i]) == TRUE)
			{
				exect_builtin(tab[i], data);
				exit(0);
			}
			else
			{
				if (!exec_all(tab[i], data))
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
		i++;
		waitpid(pid, &status, 0);
	}
	change_pipe(data, data->pipe[0], data->pipe[1], 3);
	return (TRUE);
}

bool	exec_cmd(t_data *data, char ***tab)
{
	pid_t	pid;
	int		fd;
	int		status;

	fd = -1;
	status = 0;
	if (data->ope_nbr > 0)
		fd = operator_choice(tab[1], &fd);
	if (data->ope_nbr > 1)
		fd = operator_choice(tab[2], &fd);
	if (ifbuiltin(tab[0]) == TRUE)
		exect_builtin(tab[0], data);
	else
	{
		pid = fork();
		if (pid == -1)
			perror("fork");
		if (pid == 0)
			exec_all(tab[0], data);
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
