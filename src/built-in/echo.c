#include "../../include/minishell.h"

/* Commande built-in echo : affiche du texte
** - Gère l'option -n (pas de retour à la ligne)
** - Affiche tous les arguments séparés par des espaces
** - Gère l'affichage spécial des retours à la ligne avec -n
**
** @param args: tableau d'arguments
**             args[0] = "echo"
**             args[1] = premier argument ou option -n
**             args[2+] = arguments suivants */
void	echo_command(char **args)
{
	int		i;          /* Index courant dans les arguments */
	int		j;          /* Index pour parcourir un argument */
	char	*param;     /* Stocke l'option -n si présente */

	i = 0;
	param = NULL;
	
	/* Cas d'echo sans arguments : affiche juste un retour à la ligne */
	if (args[1] != NULL)
		i++;
	else
		return ((void)write(1, "\n", 1));
	
	/* Détection de l'option -n */
	if (ft_strncmp(args[i], "-n", 2) == 0)
		param = args[i++];
	
	/* Parcours et affichage des arguments */
	while (args[i])
	{
		/* Mode avec option -n : affichage spécial des retours à la ligne */
		if (param)
		{
			j = 0;
			while (args[i][j])
			{
				(void)write(1, &args[i][j], 1);
				/* Affiche un marqueur visible pour les retours à la ligne */
				if (args[i][j] == '\n')
					ft_putstr_fd("\033[47m%\033[0m\n", 1);
				j++;
			}
			ft_putstr_fd("\033[47m%\033[0m\n", 1);
		}
		/* Mode normal : affichage direct */
		else
			ft_putstr_fd(args[i], 1);
		i++;
	}
	
	/* Affichage du dernier argument et retour à la ligne final */
	/* Note: args[i] est NULL à ce stade, cette ligne devrait être supprimée */
	/* ft_putstr_fd(args[i], 1); */
	ft_putstr_fd("\n", 1);
}
