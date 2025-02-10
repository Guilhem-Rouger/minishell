/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillot <bguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:45:01 by bguillot          #+#    #+#             */
/*   Updated: 2024/10/08 14:36:06 by bguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	g_exit_value;

void	signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		print_prompt();
		rl_on_new_line();
	}
	if (sig == SIGQUIT)
	{
		ft_putstr_fd("\n", 1);
		print_prompt();
		rl_on_new_line();
	}
}

void	waiting_command(t_data *data)
{
	rl_outstream = stderr;
	signal(SIGQUIT, &signal_handler);
	signal(SIGINT, &signal_handler);
	data->line = NULL;
	while (1)
	{
		if (data->line)
			free(data->line);
		data->line = readline(get_prompt(data));
		if (data->line == NULL)
		{
			rl_clear_history();
			break ;
		}
		if (!emptyline(data->line))
		{
			free(data->prompt);
			continue ;
		}
		add_history(data->line);
		if (!parsing(data->line, data))
			continue ;
		task_cmd(data);
		if (data->pipe_nbr >= 1)
		{
			close(data->pipe[0]);
			close(data->pipe[1]);
		}
		close(data->fd_in);
		close(data->fd_out);
		if (last_token(data->token) != data->token)
			free(data->args);
		free(data->prompt);
		ft_lstclear(&(data->cmd), free);
		token_clear(&(data->token), free);
		free(data->path);
	}
	exit_command(data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	data;

	g_exit_value = 0;
	(void)argc;
	(void)argv;
	setup(env, &data);
	waiting_command(&data);
	return (g_exit_value);
}
