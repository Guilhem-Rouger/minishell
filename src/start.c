/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bguillot <bguillot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/08 14:49:25 by bguillot          #+#    #+#             */
/*   Updated: 2024/10/08 14:51:06 by bguillot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

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

void	setup(char **env, t_data *data)
{
	path_setup(env, data);
	env_setup(env, data);
	data->user = getenv("USER");
	data->operator_nbr = 0;
	list_path_setup(data);
}
