#include "../../include/minishell.h"

int	env_len(t_env *env)
{
	t_env	*tmp_env;
	int		len;

	len = 0;
	tmp_env = env;
	while (tmp_env)
	{
		len++;
		tmp_env = tmp_env->next;
	}
	return (len);
}

char	**env_to_tab(t_env *env)
{
	char	**tab;
	int		i;

	i = 0;
	tab = ft_calloc(env_len(env) + 1, sizeof(char *));
	while (env)
	{
		tab[i] = ft_strdup(env->str);
		env = env->next;
		i++;
	}
	tab[i] = NULL;
	return (tab);
}

t_env	*get_env_var(char *var, t_data *data)
{
	t_env	*tmp_env;

	var = ft_strjoin(var, "=");
	tmp_env = data->env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->str, var, ft_strlen(var)) == 0)
			return (tmp_env);
		tmp_env = tmp_env->next;
	}
	return (NULL);
}

void	free_env(t_env *env)
{
	if (env->str)
		free(env->str);
	free(env);
}

bool	do_var_exist(t_data *data, char *var)
{
	t_env	*tmp_env;

	var = ft_strjoin(var, "=");
	tmp_env = data->env;
	while (tmp_env)
	{
		if (ft_strncmp(tmp_env->str, var, ft_strlen(var)) == 0)
			return (TRUE);
		tmp_env = tmp_env->next;
	}
	return (FALSE);
}
