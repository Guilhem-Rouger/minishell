#include "../../include/minishell.h"

/* Commande built-in env : affiche l'environnement
** - Parcourt la liste chaînée des variables d'environnement
** - Affiche chaque variable sur une nouvelle ligne
** @param args: tableau d'arguments (non utilisé)
** @param data: structure contenant les données du shell, notamment l'environnement */
void	env_command(char **args, t_data *data)
{
	t_env	*tmp_env;  /* Pointeur temporaire pour parcourir l'environnement */

	(void)args;  /* Arguments non utilisés */
	tmp_env = data->env;
	/* Parcours et affichage de toutes les variables d'environnement */
	while (tmp_env)
	{
		ft_putstr_fd(tmp_env->str, 1);  /* Affiche la variable */
		ft_putstr_fd("\n", 1);          /* Nouvelle ligne */
		tmp_env = tmp_env->next;
	}
}
