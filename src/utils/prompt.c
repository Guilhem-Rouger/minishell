#include "../../include/minishell.h"

char	*get_prompt(t_data *data)
{
	char	*prompt;
	char	*current_dir;
	char	*user;

	data->prompt = NULL;
	user = getenv("USER");
	if (!user)
		perror("getenv failed");
	current_dir = getcwd(NULL, 65534);
	if (!current_dir)
		perror("getcwd failed");
	prompt = ft_strdup("\033[93m");
	if (user)
		prompt = ft_strjoin(prompt, user);
	prompt = ft_strjoin(prompt, "\033[0m");
	prompt = ft_strjoin(prompt, "@");
	prompt = ft_strjoin(prompt, "\033[36m");
	prompt = ft_strjoin(prompt, "minicoque:");
	prompt = ft_strjoin(prompt, "\033[0m");
	prompt = ft_strjoin(prompt, current_dir);
	free(current_dir);
	prompt = ft_strjoin(prompt, "$ ");
	if (data->prompt)
		free(data->prompt);
	data->prompt = prompt;
	return (data->prompt);
}

void	print_prompt(void)
{
	char	*current_dir;
	char	*user;

	user = getenv("USER");
	if (!user)
		perror("getenv failed");
	current_dir = getcwd(NULL, 65534);
	if (!current_dir)
		perror("getcwd failed");
	ft_putstr_fd("\033[93m", 2);
	if (user)
		ft_putstr_fd(user, 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd("@", 2);
	ft_putstr_fd("\033[36m", 2);
	ft_putstr_fd("minicoque:", 2);
	ft_putstr_fd("\033[0m", 2);
	ft_putstr_fd(current_dir, 2);
	ft_putstr_fd("$ ", 2);
}
