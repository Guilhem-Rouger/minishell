#include "../../include/minishell.h"

/* Commande built-in cd (Change Directory)
** - Si aucun argument n'est fourni, change vers le répertoire HOME
** - Sinon, change vers le chemin spécifié
** - Gère les erreurs de changement de répertoire
** @param args: tableau d'arguments (args[0] = "cd", args[1] = chemin)
** @param data: structure contenant les données du shell */
void	cd_command(char **args, t_data *data)
{
	char	*current_dir;  /* Répertoire courant */
	char	*new_dir;      /* Nouveau répertoire cible */

	(void)data;
	/* Récupère le répertoire courant */
	current_dir = getcwd(NULL, 65534);
	
	/* Cas 1: cd sans argument -> aller au HOME */
	if (args[1] == NULL)
	{
		new_dir = replace_var("$HOME");
		if (chdir(new_dir) == -1)
			perror("HOME variable not set correctly");
	}
	/* Cas 2: cd avec un chemin spécifié */
	else
	{
		/* Construit le chemin complet */
		new_dir = ft_strjoin(current_dir, "/");
		new_dir = ft_strjoin(new_dir, args[1]);
		
		/* Tente de changer de répertoire */
		if (chdir(new_dir) == -1)
		{
			/* Affiche une erreur en rouge si le chemin est invalide */
			ft_putstr_fd("\033[0;31m", 2);
			ft_putstr_fd(args[1], 2);
			ft_putstr_fd(": No such file or directory", 2);
			ft_putstr_fd("\033[0;0m\n", 2);
		}
	}
}
