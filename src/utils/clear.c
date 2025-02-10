#include "../../include/minishell.h"

void	clear_tab(char **tab)
{
	int	i;

	if (!tab)
		return ;
	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

void	clear_2tab(char ***tab)
{
	int	i;

	if (!tab || !*tab)
		return ;
	i = 0;
	while ((*tab)[i])
		i++;
	while (i > 0)
	{
		i--;
		clear_tab((tab)[i]);
	}
}

void	clear_single(t_data *data)
{
	free(data->path);
}

void	clear_all(t_data *data)
{
	close(data->fd_in);
	close(data->fd_out);
	if (data->list_path)
		clear_tab(data->list_path);
	if (data->cmd)
		ft_lstclear(&(data->cmd), free);
	if (data->token)
		token_clear(&(data->token), free);
	clear_single(data);
}
