#include "../../include/minishell.h"

void	show_env_sorted(t_env *env)
{
	t_env		*it;
	t_env		*to_show;

	it = env->next;
	to_show = env;
	while (it)
	{
		if (to_show->str[0] > it->str[0])
			to_show = it;
		if (it->next)
			it = it->next;
	}
	printf("%s\n", to_show->str);
}

void	edit_var(char *var, char *value, t_data *data)
{
	t_env	*tmp_env;

	tmp_env = data->env;
	while (tmp_env->next)
	{
		if (ft_strstr(tmp_env->str, var))
		{
			free(tmp_env->str);
			tmp_env->str = ft_strdup(var);
			tmp_env->str = ft_strjoin(tmp_env->str, "=");
			tmp_env->str = ft_strjoin(tmp_env->str, value);
		}
		tmp_env = tmp_env->next;
	}
}

void	add_var(char *var, char *value, t_data *data)
{
	char	*tmp;

	tmp = ft_strdup(var);
	tmp = ft_strjoin(tmp, "=");
	tmp = ft_strjoin(tmp, value);
	env_add_back(&data->env, env_create(tmp, last_env(data->env)->index + 1));
}

void	export_command(char **args, t_data *data)
{
	char	**var;

	if (args[1] == NULL)
		show_env_sorted(data->env);
	else
	{
		var = ft_split(args[1], "=");
		if (do_var_exist(data, var[0]) == TRUE)
			edit_var(var[0], var[1], data);
		else
			add_var(var[0], var[1], data);
	}
}
