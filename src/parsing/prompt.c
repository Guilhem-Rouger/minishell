#include "../../include/minishell.h"

/* Génère le prompt personnalisé du shell
** Format: [user]@minicoque:[current_dir]$
** Avec coloration :
** - user en jaune (\033[93m)
** - minicoque en cyan (\033[36m)
** - reste en couleur par défaut (\033[0m)
**
** @param data: structure contenant les données du shell
** @return: chaîne contenant le prompt formaté */
char	*get_prompt(t_data *data)
{
	char	*prompt;     /* Chaîne finale du prompt */
	char	*current_dir; /* Répertoire courant */
	char	*user;       /* Nom d'utilisateur */

	data->prompt = NULL;
	/* Récupération du nom d'utilisateur */
	user = getenv("USER");
	if (!user)
		perror("getenv failed");
	/* Récupération du répertoire courant */
	current_dir = getcwd(NULL, 65534);
	if (!current_dir)
		perror("getcwd failed");
	
	/* Construction du prompt avec les couleurs */
	prompt = ft_strdup("\033[93m");           /* Début jaune */
	if (user)
		prompt = ft_strjoin(prompt, user);
	prompt = ft_strjoin(prompt, "\033[0m");   /* Fin jaune */
	prompt = ft_strjoin(prompt, "@");
	prompt = ft_strjoin(prompt, "\033[36m");  /* Début cyan */
	prompt = ft_strjoin(prompt, "minicoque:");
	prompt = ft_strjoin(prompt, "\033[0m");   /* Fin cyan */
	prompt = ft_strjoin(prompt, current_dir);
	free(current_dir);
	prompt = ft_strjoin(prompt, "$ ");
	
	/* Mise à jour du prompt dans la structure */
	if (data->prompt)
		free(data->prompt);
	data->prompt = prompt;
	return (data->prompt);
}

/* Affiche le prompt directement sur la sortie d'erreur (fd 2)
** Utilisé principalement pour le gestionnaire de signaux
** Format identique à get_prompt mais sans stocker la chaîne */
void	print_prompt(void)
{
	char	*current_dir; /* Répertoire courant */
	char	*user;       /* Nom d'utilisateur */

	/* Récupération du nom d'utilisateur */
	user = getenv("USER");
	if (!user)
		perror("getenv failed");
	/* Récupération du répertoire courant */
	current_dir = getcwd(NULL, 65534);
	if (!current_dir)
		perror("getcwd failed");
	
	/* Affichage du prompt avec les couleurs */
	ft_putstr_fd("\033[93m", 2);           /* Début jaune */
	if (user)
		ft_putstr_fd(user, 2);
	ft_putstr_fd("\033[0m", 2);            /* Fin jaune */
	ft_putstr_fd("@", 2);
	ft_putstr_fd("\033[36m", 2);           /* Début cyan */
	ft_putstr_fd("minicoque:", 2);
	ft_putstr_fd("\033[0m", 2);            /* Fin cyan */
	ft_putstr_fd(current_dir, 2);
	ft_putstr_fd("$ ", 2);
}
