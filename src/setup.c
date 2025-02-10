/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:49:25 by bguillot          #+#    #+#             */
/*   Updated: 2025/02/10 16:48:44 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* Configuration de la liste des chemins d'exécution
** - Divise la variable PATH en chemins individuels
** - Vérifie les permissions d'exécution pour chaque chemin
** - Affiche une erreur pour les chemins invalides */
void	list_path_setup(t_data *data)
{
	int	i;

	data->list_path = ft_split(data->minishell_path, ":");
	i = 0;
	while (data->list_path[i])
	{
		if (access(data->list_path[i], X_OK) == -1)
			printf("\033[0;31mERROR : '%s' is not a valid path\033[0;0m\n", \
				data->list_path[i]);
		i++;
	}
}

/* Configuration du PATH
** - Recherche la variable PATH dans l'environnement
** - Si non trouvée, utilise un chemin par défaut
** - Stocke l'index et la valeur du PATH */
void	path_setup(char **env, t_data *data)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5))
		{
			data->p_index = i;
			data->minishell_path = &(env[i][5]);
			return ;
		}
		i++;
	}
	if (!data->minishell_path)
		data->minishell_path = strdup("/bin:/usr/local/bin:/usr/bin:/\
			bin:/usr/local/sbin");
	return ;
}

/* Configuration de l'environnement
** - Crée une liste chaînée des variables d'environnement
** - Chaque nœud contient la variable et son index */
void	env_setup(char **env, t_data *data)
{
	int	i;

	data->env = env_create(env[0], 0);
	i = 1;
	while (env[i])
	{
		env_add_back(&data->env, env_create(env[i], i));
		i++;
	}
}

/* Fonction principale d'initialisation
** - Configure le PATH
** - Configure l'environnement
** - Récupère le nom d'utilisateur
** - Initialise les compteurs et structures */
void	setup(char **env, t_data *data)
{
	path_setup(env, data);
	env_setup(env, data);
	data->user = getenv("USER");
	data->ope_nbr = 0;
	list_path_setup(data);
}
