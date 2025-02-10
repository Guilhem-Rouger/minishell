#include "../../include/minishell.h"

void	unset_command(char **args, t_data *data)
{
	char		*var;
	t_env		*tmp_env;

	var = NULL;
	if (args[1] != NULL)
		var = args[1];
	if (do_var_exist(data, var) == TRUE)
	{
		tmp_env = data->env;
		while (tmp_env)
		{
			if (ft_strncmp(tmp_env->str, var, ft_strlen(tmp_env->str) != 0))
			{
				if (tmp_env->next != NULL)
				{
					tmp_env->prev->next = tmp_env->next;
					tmp_env->next->prev = tmp_env->prev;
				}
				free_env(tmp_env);
				break ;
			}
			tmp_env = tmp_env->next;
		}
	}
}
