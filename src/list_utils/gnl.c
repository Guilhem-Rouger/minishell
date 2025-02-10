#include "../../include/minishell.h"

void	strreplace(char **a, char *b)
{
	free(*a);
	*a = b;
}

char	*strnjoin(char *s1, char *s2, size_t n)
{
	size_t	s1_len;
	char	*output;
	size_t	i;

	s1_len = ft_strlen(s1);
	output = malloc(s1_len + n + 1);
	if (!output)
		return (NULL);
	i = 0;
	if (s1)
		while (*s1)
			output[i++] = *(s1++);
	while (*s2 && i - s1_len < n)
		output[i++] = *(s2++);
	output[i] = '\0';
	return (output);
}

static void	clear_buffer(char buffer[BUFFER_SIZE + 1])
{
	size_t	i;

	i = 0;
	while (i < BUFFER_SIZE + 1)
	{
		buffer[i] = '\0';
		i++;
	}
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*output;
	size_t		i;

	if (fd < 0 || fd > FOPEN_MAX || BUFFER_SIZE < 0)
		return (NULL);
	output = NULL;
	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\n' && buffer[i + 1])
		strreplace(&output, strnjoin(output, buffer + i + 1, BUFFER_SIZE));
	clear_buffer(buffer);
	while (read(fd, buffer, BUFFER_SIZE) > 0)
	{
		i = 0;
		while (buffer[i] && buffer[i] != '\n')
			i++;
		strreplace(&output, strnjoin(output, buffer, i + 1));
		if (buffer[i] == '\n')
			break ;
		clear_buffer(buffer);
	}
	return (output);
}
