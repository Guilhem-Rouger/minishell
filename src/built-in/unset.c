#include "../../include/minishell.h"

/* Commande built-in unset : supprime des variables d'environnement
** - Recherche la variable spécifiée dans l'environnement
** - Si trouvée, la supprime en maintenant la cohérence de la liste chaînée
** - Libère la mémoire associée à la variable
**
** @param args: tableau d'arguments
**             args[0] = "unset"
**             args[1] = nom de la variable à supprimer
** @param data: structure contenant les données du shell */
void	unset_command(char **args, t_data *data)
{
	char		*var;      /* Nom de la variable à supprimer */
	t_env		*tmp_env;  /* Pointeur temporaire pour parcourir l'environnement */

	var = NULL;
	/* Récupération du nom de la variable si fourni */
	if (args[1] != NULL)
		var = args[1];
	
	/* Vérifie si la variable existe */
	if (do_var_exist(data, var) == TRUE)
	{
		tmp_env = data->env;
		/* Parcours de la liste jusqu'à trouver la variable */
		while (tmp_env)
		{
			if (ft_strncmp(tmp_env->str, var, ft_strlen(tmp_env->str) != 0))
			{
				/* Mise à jour des liens de la liste chaînée */
				if (tmp_env->next != NULL)
				{
					tmp_env->prev->next = tmp_env->next;
					tmp_env->next->prev = tmp_env->prev;
				}
				/* Libération de la mémoire */
				free_env(tmp_env);
				break ;
			}
			tmp_env = tmp_env->next;
		}
	}
}
