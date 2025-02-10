/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:45:01 by bguillot          #+#    #+#             */
/*   Updated: 2025/02/10 16:57:49 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Variable globale pour stocker le code de retour des commandes */
int	g_exit_value;

/* Gestionnaire de signaux pour SIGINT (Ctrl+C) et SIGQUIT (Ctrl+\)
** - Affiche un nouveau prompt sur interruption
** - Gère l'affichage propre du shell */
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

/* Boucle principale du shell
** - Configure les signaux
** - Gère la lecture des commandes
** - Traite l'historique
** - Execute les commandes
** - Nettoie les ressources */
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
		/* Lecture de la commande avec affichage du prompt */
		data->line = readline(get_prompt(data));
		if (data->line == NULL)  /* Gestion de Ctrl+D */
		{
			rl_clear_history();
			break ;
		}
		/* Ignore les lignes vides */
		if (!emptyline(data->line))
		{
			free(data->prompt);
			continue ;
		}
		/* Ajout de la commande à l'historique */
		add_history(data->line);
		/* Parsing et exécution de la commande */
		if (!parsing(data->line, data))
			continue ;
		task_cmd(data);
		/* Nettoyage des ressources après exécution */
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
	rl_clear_history();
	exit_command(data);
}

/* Point d'entrée du programme
** - Initialise les données du shell
** - Lance la boucle principale
** - Retourne le code de sortie */
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
