#include "../../include/minishell.h"

void	echo_command(char **args)
{
	int		i;
	int		j;
	char	*param;

	i = 0;
	param = NULL;
	if (args[1] != NULL)
		i++;
	else
		return ((void)write(1, "\n", 1));
	if (ft_strncmp(args[i], "-n", 2) == 0)
		param = args[i++];
	while (args[i])
	{
		if (param)
		{
			j = 0;
			while (args[i][j])
			{
				(void)write(1, &args[i][j], 1);
				if (args[i][j] == '\n')
					ft_putstr_fd("\033[47m%\033[0m\n", 1);
				i++;
			}
			ft_putstr_fd("\033[47m%\033[0m\n", 1);
		}
		else
			ft_putstr_fd(args[i], 1);
		i++;
	}
	ft_putstr_fd(args[i], 1);
	ft_putstr_fd("\n", 1);
}
