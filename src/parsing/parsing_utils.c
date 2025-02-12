#include "../../include/minishell.h"

/* Vérifie si une ligne est vide
** @param line: ligne à vérifier
** @return: FALSE si la ligne est vide, TRUE sinon */
bool	emptyline(char *line)
{
	if (ft_strlen(line) == 0)
		return (FALSE);
	else
		return (TRUE);
}

/* Découpe la ligne de commande en tokens
** - Gère les quotes (simples et doubles)
** - Sépare sur les caractères spéciaux (<|> )
** - Crée une liste chaînée de commandes
** @param line: ligne à découper
** @param data: structure contenant les données du shell
** @return: TRUE si succès, FALSE si erreur */
bool	spliting_cmd(char *line, t_data *data)
{
	t_quote	*q;         /* Structure pour la gestion des quotes */
	char	**tab;      /* Tableau temporaire après split sur quotes */
	char	**tab_temp; /* Tableau final après split sur séparateurs */
	int		i;

	/* Initialisation de la structure quote */
	q = malloc(sizeof(t_quote) * 1);
	i = 0;
	q->start = 0;
	q->i = 0;
	q->j = 0;
	q->quote_char = '\0';
	
	/* Premier split en respectant les quotes */
	tab = split_quote(line, q);
	free(q);
	tab_temp = split_sep(tab, "<|>& ");
	clear_tab(tab);
	
	/* Création de la liste chaînée de commandes */
	data->cmd = NULL;
	if (!tab_temp)
		return (FALSE);
	while (tab_temp[i])
	{
		ft_lstadd_back(&(data->cmd), ft_lstnew(tab_temp[i]));
		i++;
	}
	free(tab_temp);
	return (TRUE);
}

/* Remplace les variables d'environnement dans les tokens
** - Gère $? (code de sortie)
** - Gère $$ (PID)
** - Gère les variables d'environnement classiques
** @param data: structure contenant les données du shell
** @return: TRUE si succès */
bool	replace_env_var(t_data *data)
{
	t_token	*token;    /* Token courant */
	int		var;       /* Nombre de variables à remplacer */
	int		i;         /* Compteur de remplacements effectués */

	token = data->token;
	i = 0;
	var = 0;
	while (token)
	{
		if (var == 0)
			var = count_replace(token->str);
		
		/* Remplacement du code de sortie ($?) */
		if (token->sq != TRUE && is_exitcode(token->str) >= 0)
		{
			token->str = replace_exitcode(token->str);
			i++;
		}
		/* Remplacement du PID ($$) */
		else if (token->sq != TRUE && is_pid(token->str) >= 0)
		{
			token->str = replace_pid(token->str);
			i++;
		}
		/* Remplacement des variables d'environnement ($VAR) */
		else if (token->sq != TRUE && is_dollar(token->str) >= 0)
		{
			token->str = replace_var(token->str);
			i++;
		}
		/* Passage au token suivant si tous les remplacements sont faits */
		if (i == var || token->sq == TRUE)
		{
			token = token->next;
			i = 0;
			var = 0;
		}
	}
	return (TRUE);
}

/* Compte le nombre de pipes dans la ligne
** Met à jour pipe_nbr et id_pipe dans la structure data
** @param line: ligne à analyser
** @param data: structure contenant les données du shell */
void	count_pipe(char *line, t_data *data)
{
	int	i;

	i = 0;
	data->pipe_nbr = 0;
	data->id_pipe = 0;
	while (line[i])
	{
		if (line[i] == '|')
			data->pipe_nbr++;
		i++;
	}
}

/* Fonction principale de parsing
** - Vérifie les quotes
** - Découpe la ligne en tokens
** - Configure les tokens
** - Remplace les variables d'environnement
** @param line: ligne à parser
** @param data: structure contenant les données du shell
** @return: TRUE si succès, FALSE si erreur de parsing */
bool	parsing(char *line, t_data *data)
{
	if (!check_line(line))
		return (FALSE);
	if (!quote_check(line))
		return (FALSE);
	if (!spliting_cmd(line, data))
		return (FALSE);
	if (!token_setup(data))
		return (FALSE);
	if (!replace_env_var(data))
		return (FALSE);
	if (!token_verif(data->token))
			return (FALSE);
	count_pipe(line, data);
	count_operator(data);
	data->fd_in = dup(0);
	data->fd_out = dup(1);
	data->path = ft_calloc(sizeof(char *), data->pipe_nbr + data->ope_nbr + 1);
	return (TRUE);
}
