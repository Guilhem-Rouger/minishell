#include "../../include/minishell.h"

void	exit_command(t_data *data)
{
	clear_all(data);
	rl_clear_history();
	exit(g_exit_value);
}