#include "../../include/minishell.h"

void	env_command(char **args, t_data *data)
{
	t_env	*tmp_env;

	(void)args;
	tmp_env = data->env;
	while (tmp_env)
	{
		ft_putstr_fd(tmp_env->str, 1);
		ft_putstr_fd("\n", 1);
		tmp_env = tmp_env->next;
	}
}
