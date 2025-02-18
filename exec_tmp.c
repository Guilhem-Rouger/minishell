/*exec()
├── spec_built_first()
└── ft_ft_exec()
    ├── Pour chaque commande (cmd) :
    │   ├── Si redirection invalide
    │   │   └── Affiche erreur
    │   ├── Si commande builtin spéciale
    │   │   └── spec_built()
    │   └── Sinon (commande normale)
    │       └── ft_launch_cmd()
    │           ├── Fork()
    │           ├── Processus enfant (g_pid == 0)
    │           │   └── child_process()
    │           │       ├── redirect_in_out()
    │           │       └── ft_execve()
    │           │           └── Tente l'exécution dans tous les chemins PATH
    │           └── Processus parent
    │               └── parent_process()
    └── wait_all_and_finish()
        ├── Attend tous les processus enfants
        ├── Gère le statut de sortie
        └── Ferme les descripteurs de fichiers
*/

void	spec_built_first(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd != NULL && cmd->argv != NULL && cmd->argv[0] != NULL)
		{
			if (ft_strcmp(cmd->argv[0], "cd") == 0)
				cmd->spec_built = 2;
			else if (ft_strcmp(cmd->argv[0], "exit") == 0)
				cmd->spec_built = 1;
			else if (ft_strcmp(cmd->argv[0], "export") == 0)
				cmd->spec_built = 3;
			else if (ft_strcmp(cmd->argv[0], "unset") == 0)
				cmd->spec_built = 4;
			else
				cmd->spec_built = 0;
		}
		else
		{	
			cmd->spec_built = -1;
		}
		cmd = cmd->next;
	}
} // je sais pas si cest utile

void	exec(t_data *data)
{
	//t_cmd	*index;
	t_list	*cmd;
	
	cmd = data->cmd;
	//index = data->cmd;
	spec_built_first(data);
	if (index->nb_cmd)
		ft_ft_exec(data);
}


// ==========================================================

void	spec_built(t_cmd *cmd, t_data *data)
{
	if (cmd->spec_built == 1)
		ft_exit(cmd, data);
	else if (cmd->spec_built == 2)
		ft_cd(cmd, data->env, data);
	else if (cmd->spec_built == 3)
		ft_export(data->env, cmd, data);
	else if (cmd->spec_built == 4)
		ft_unset(data->env, cmd, data);
	else
		return ;
}

int	ft_ft_exec(t_data *data)
{
	t_cmd	*cmd;
	int		fd[2];

	cmd = data->cmd_index->begin;
	while (cmd)
	{
		if (cmd->out_file == -1 || cmd->in_file == -1)
			ft_putstr_fd("Error: redirection\n", 2);
		else if (cmd->spec_built)
			spec_built(cmd, data);
		else
		{
			if (pipe(fd) == -1)
				return (-1);
			else
				ft_launch_cmd(data, cmd, fd);
		}
		cmd = cmd->next;
	}
	wait_all_and_finish(data->cmd_index->begin, data);
	free_list_second(data);
	return (1);
}

void	wait_all_and_finish(t_cmd *cmds, t_data *data)
{
	int	status;
	int	pidtmp;

	while (cmds)
	{
		pidtmp = waitpid(0, &status, 0);
		if (pidtmp == g_pid)
		{
			if (WIFEXITED(status))
				data->exit_return = WEXITSTATUS(status);
		}
		if (cmds->out_file >= 0)
			close(cmds->out_file);
		if (cmds->in_file >= 0)
			close(cmds->in_file);
		cmds = cmds->next;
	}
}

void	free_list_second(t_data *data)
{
	t_cmd	*tmp;

	tmp = data->cmd_index->begin;
	while (tmp)
	{
		tmp = pop_front_dlist(data->cmd_index);
		free(tmp);
	}
}

// ==========================================================

void	ft_launch_cmd(t_data *data, t_cmd *cmd, int *fd)
{
	cmdbloc_signal();
	g_pid = fork();
	if (g_pid < 0)
	{
		perror("fork");
		return ;
	}
	else if (g_pid == 0)
	{
		if (cmd->argv && cmd->argv[0])
			child_process(data, cmd, fd);
		_exit(EXIT_FAILURE);
	}
	else
		parent_process(cmd, fd);
}

void	child_process(t_data *data, t_cmd *cmd, int *fd)
{
	int	n;

	redirect_in_out(cmd, fd);
	if (cmd->is_built && !cmd->spec_built)
	{
		ft_builtins(cmd, data->env, data);
		n = data->exit_return;
		free_everything(data);
		exit(n);
	}
	ft_execve(cmd, data);
	exit_process(data, fd);
}

void	parent_process(t_cmd *cmd, int *fd)
{
	close(fd[1]);
	if (cmd->in_file >= 0)
		close(cmd->in_file);
	if (cmd->in_file == -2)
		cmd->in_file = fd[0];
	if (cmd->next && cmd->next->in_file == -2)
		cmd->next->in_file = fd[0];
	else
		close(fd[0]);
	return ;
}

// ==========================================================

