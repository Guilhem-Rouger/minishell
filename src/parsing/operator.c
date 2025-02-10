#include "../../include/minishell.h"

int	ft_append(char **args)
{
	int		fd;

	fd = -1;
	fd = open(args[1], O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		perror("file doesn't exist");
	if (dup2(fd, 1) == -1)
		perror("dup2");
	return (fd);
}

int	ft_trunc(char **args)
{
	int		fd;

	fd = -1;
	fd = open(args[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		perror("file doesn't exist");
	if (dup2(fd, 1) == -1)
		perror("dup2");
	return (fd);
}

int	ft_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;

	if (!delimiter)
		return (-1);
	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	while (1)
	{
		(void)write(1, "> ", 2);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, delimiter, ft_strlen(delimiter)) == 0)
		{
			free(line);
			break ;
		}
		(void)write(fd, line, ft_strlen(line));
		free(line);
	}
	if (dup2(fd, 0) == -1)
		perror("dup2");
	close(fd);
	return (0);
}

int	ft_input(char **args)
{
	int	fd;

	fd = open(args[1], O_RDONLY, 0777);
	if (fd == -1)
		perror("file doesn't exist");
	if (dup2(fd, 0) == -1)
		perror("dup2");
	close(fd);
	return (fd);
}

int	operator_choice(char **tab, int *fd)
{
	if (!tab)
		return (-1);
	if (ft_strncmp(tab[0], ">>", 2) == 0 && ft_strlen(tab[0]) == 2)
		*fd = ft_append(tab);
	else if (ft_strncmp(tab[0], ">", 1) == 0 && ft_strlen(tab[0]) == 1)
		*fd = ft_trunc(tab);
	else if (ft_strncmp(tab[0], "<<", 1) == 0 && ft_strlen(tab[0]) == 2)
		*fd = ft_heredoc(tab[1]);
	else if (ft_strncmp(tab[0], "<", 1) == 0 && ft_strlen(tab[0]) == 1)
		*fd = ft_input(tab);
	return (*fd);
}
