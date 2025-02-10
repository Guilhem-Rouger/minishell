#include "../../include/minishell.h"

void	cd_command(char **args, t_data *data)
{
	char	*current_dir;
	char	*new_dir;

	current_dir = getcwd(NULL, 65534);
	if (args[1] == NULL)
	{
		new_dir = ft_strtrim(get_env_var("HOME", data)->str, "HOME=");
		if (chdir(new_dir) == -1)
			perror("HOME variable not set correctly");
	}
	else
	{
		new_dir = ft_strjoin(current_dir, "/");
		new_dir = ft_strjoin(new_dir, args[1]);
		if (chdir(new_dir) == -1)
		{
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": No such file or directory", 2);
			ft_putstr_fd("\033[0;0m\n", 2);
		}
	}
}
