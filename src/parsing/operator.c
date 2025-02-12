#include "../../include/minishell.h"

/* Gère la redirection en mode append (>>)
** Ouvre ou crée le fichier en mode ajout
** @param args: tableau d'arguments (args[0] = ">>", args[1] = nom du fichier)
** @return: descripteur de fichier ou -1 si erreur */
int	ft_append(char **args)
{
	int		fd;

	fd = -1;
	/* Ouvre le fichier en mode ajout, écriture, création si nécessaire */
	fd = open(args[1], O_APPEND | O_WRONLY | O_CREAT, 0644);
	if (fd == -1)
		perror("file doesn't exist");
	/* Redirige la sortie standard vers le fichier */
	if (dup2(fd, 1) == -1)
		perror("dup2");
	return (fd);
}

/* Gère la redirection en mode troncature (>)
** Ouvre ou crée le fichier en écrasant son contenu
** @param args: tableau d'arguments (args[0] = ">", args[1] = nom du fichier)
** @return: descripteur de fichier ou -1 si erreur */
int	ft_trunc(char **args)
{
	int		fd;

	fd = -1;
	/* Ouvre le fichier en mode écriture, troncature, création si nécessaire */
	fd = open(args[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
	if (fd == -1)
		perror("file doesn't exist");
	/* Redirige la sortie standard vers le fichier */
	if (dup2(fd, 1) == -1)
		perror("dup2");
	return (fd);
}

/* Gère le heredoc (<<)
** Lit l'entrée standard jusqu'à rencontrer le délimiteur
** @param delimiter: chaîne qui termine la lecture
** @return: 0 si succès, -1 si erreur */
int	ft_heredoc(const char *delimiter)
{
	char	*line;
	int		fd;

	if (!delimiter)
		return (-1);
	/* Crée un fichier temporaire pour stocker les données */
	fd = open("temp", O_RDWR | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
		return (-1);
	/* Lecture ligne par ligne jusqu'au délimiteur */
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
	/* Redirige l'entrée standard vers le fichier temporaire */
	if (dup2(fd, 0) == -1)
		perror("dup2");
	close(fd);
	return (0);
}

/* Gère la redirection depuis un fichier (<)
** Ouvre le fichier en lecture
** @param args: tableau d'arguments (args[0] = "<", args[1] = nom du fichier)
** @return: descripteur de fichier ou -1 si erreur */
int	ft_input(char **args)
{
	int	fd;

	/* Ouvre le fichier en lecture seule */
	fd = open(args[1], O_RDONLY, 0777);
	if (fd == -1)
		perror("file doesn't exist");
	/* Redirige l'entrée standard depuis le fichier */
	if (dup2(fd, 0) == -1)
		perror("dup2");
	close(fd);
	return (fd);
}

/* Sélectionne et exécute l'opérateur approprié
** @param tab: tableau contenant l'opérateur et ses arguments
** @param fd: pointeur vers le descripteur de fichier à utiliser
** @return: valeur du descripteur de fichier ou -1 si erreur
**
** Opérateurs supportés :
** - >> : append (ajout en fin de fichier)
** - >  : trunc (écrasement du fichier)
** - << : heredoc (lecture jusqu'au délimiteur)
** - <  : input (lecture depuis un fichier) */
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
