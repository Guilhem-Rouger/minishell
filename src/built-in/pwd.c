#include "../../include/minishell.h"

/* Commande built-in pwd (Print Working Directory)
** - Récupère le chemin absolu du répertoire courant
** - Affiche le chemin suivi d'un retour à la ligne
** - Utilise getcwd avec une taille maximale de 65534 caractères
**
** Note : La mémoire allouée par getcwd n'est pas libérée ici,
** ce qui pourrait causer une fuite de mémoire. Il faudrait
** ajouter un free(current_directory) après l'affichage. */
void	pwd_command(void)
{
	char	*current_directory;  /* Stocke le chemin du répertoire courant */

	current_directory = getcwd(NULL, 65534);
	ft_putstr_fd(current_directory, 1);  /* Affiche le chemin */
	ft_putstr_fd("\n", 1);              /* Ajoute un retour à la ligne */
}
