#include "../../include/minishell.h"

/* Affiche l'environnement trié par ordre alphabétique
** - Parcourt la liste des variables d'environnement
** - Trouve et affiche la variable qui vient en premier alphabétiquement
** @param env: liste chaînée des variables d'environnement */
void	show_env_sorted(t_env *env)
{
	t_env		*it;        /* Itérateur pour parcourir la liste */
	t_env		*to_show;   /* Variable à afficher (la plus petite alphabétiquement) */

	it = env->next;
	to_show = env;
	/* Recherche de la variable qui vient en premier alphabétiquement */
	while (it)
	{
		if (to_show->str[0] > it->str[0])
			to_show = it;
		if (it->next)
			it = it->next;
	}
	printf("%s\n", to_show->str);
}

/* Modifie une variable d'environnement existante
** - Recherche la variable dans l'environnement
** - Met à jour sa valeur
** @param var: nom de la variable
** @param value: nouvelle valeur
** @param data: structure contenant les données du shell */
void	edit_var(char *var, char *value, t_data *data)
{
	t_env	*tmp_env;  /* Pointeur temporaire pour parcourir l'environnement */

	tmp_env = data->env;
	while (tmp_env->next)
	{
		/* Si la variable est trouvée, met à jour sa valeur */
		if (ft_strstr(tmp_env->str, var))
		{
			free(tmp_env->str);
			tmp_env->str = ft_strdup(var);
			tmp_env->str = ft_strjoin(tmp_env->str, "=");
			tmp_env->str = ft_strjoin(tmp_env->str, value);
		}
		tmp_env = tmp_env->next;
	}
}

/* Ajoute une nouvelle variable d'environnement
** - Crée une nouvelle chaîne au format "VAR=valeur"
** - L'ajoute à la fin de la liste des variables
** @param var: nom de la variable
** @param value: valeur de la variable
** @param data: structure contenant les données du shell */
void	add_var(char *var, char *value, t_data *data)
{
	char	*tmp;  /* Chaîne temporaire pour construire la variable */

	/* Construction de la chaîne "VAR=valeur" */
	tmp = ft_strdup(var);
	tmp = ft_strjoin(tmp, "=");
	tmp = ft_strjoin(tmp, value);
	/* Ajout à la fin de la liste avec un nouvel index */
	env_add_back(&data->env, env_create(tmp, last_env(data->env)->index + 1));
}

/* Commande built-in export : définit des variables d'environnement
** - Sans argument : affiche l'environnement trié
** - Avec argument VAR=valeur : définit ou met à jour une variable
** @param args: tableau d'arguments
**             args[0] = "export"
**             args[1] = "VAR=valeur" ou NULL
** @param data: structure contenant les données du shell */
void	export_command(char **args, t_data *data)
{
	char	**var;  /* Tableau pour stocker le nom et la valeur de la variable */

	if (args[1] == NULL)
		show_env_sorted(data->env);
	else
	{
		/* Sépare l'argument en nom et valeur */
		var = ft_split(args[1], "=");
		/* Met à jour ou crée la variable selon qu'elle existe déjà ou non */
		if (do_var_exist(data, var[0]) == TRUE)
			edit_var(var[0], var[1], data);
		else
			add_var(var[0], var[1], data);
	}
}
