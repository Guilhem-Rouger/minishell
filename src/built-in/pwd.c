#include "../../include/minishell.h"

void	pwd_command(void)
{
	char	*current_directory;

	current_directory = getcwd(NULL, 65534);
	ft_putstr_fd(current_directory, 1);
	ft_putstr_fd("\n", 1);
}
