#include "../../include/minishell.h"

/* Détermine le type de token en fonction du caractère
** @param lst: élément de la liste de commandes
** @param token: dernier token traité
** @return: type de token (PIPE, APPEND, HEREDOC, INPUT, TRUNC, PARAM, CMD, ARG)
**
** Types de tokens :
** - PIPE (|) : redirection de sortie vers entrée
** - APPEND (>>) : redirection avec ajout en fin de fichier
** - HEREDOC (<<) : lecture depuis l'entrée jusqu'au délimiteur
** - INPUT (<) : redirection depuis un fichier
** - TRUNC (>) : redirection avec écrasement du fichier
** - PARAM (-) : paramètre de commande
** - CMD : commande
** - ARG : argument de commande */
int	choose_token(t_list *lst, t_token *token)
{
	/* Détection du pipe */
	if (lst->str[0] == '|')
		return (PIPE);
	
	/* Détection des opérateurs doubles (>> et <<) */
	if (ft_lstlast(lst) != lst)
	{
		if (lst->str[0] == '>' && lst->next->str[0] == '>')
			return (APPEND);
		if (lst->str[0] == '<' && lst->next->str[0] == '<')
			return (HEREDOC);
	}
	
	/* Détection des opérateurs simples */
	if (lst->str[0] == '<')
		return (INPUT);
	if (lst->str[0] == '>')
		return (TRUNC);
	if (lst->str[0] == '-')
		return (PARAM);
	
	/* Détection commande/argument */
	if (token != NULL)
	{
		if (token->type == PIPE)
			return (CMD);
		else
			return (ARG);
	}
	return (CMD);
}

/* Configuration de la liste des tokens
** - Parcourt la liste des commandes
** - Crée les tokens correspondants
** - Gère les opérateurs doubles (>> et <<)
** @param data: structure contenant les données du shell
** @return: TRUE si succès, FALSE si échec */
bool	token_setup(t_data *data)
{
	t_list	*it;        /* Itérateur sur la liste de commandes */
	char	*str_to_use; /* Chaîne à utiliser pour le token */
	int		toktok;     /* Type du token */

	it = data->parsing;
	if (!data->parsing)
		return (FALSE);
	data->token = NULL;
	
	/* Parcours de la liste des commandes */
	while (it)
	{
		toktok = choose_token(it, last_token(data->token));
		
		/* Gestion des opérateurs doubles */
		if (toktok == HEREDOC || toktok == APPEND)
		{
			str_to_use = ft_strjoin(ft_strdup(it->str), it->next->str);
			token_add_back(&(data->token), token_create(str_to_use, toktok));
			it = it->next->next;
		}
		/* Gestion des autres tokens */
		else
		{
			str_to_use = ft_strdup(it->str);
			token_add_back(&(data->token), token_create(str_to_use, toktok));
			it = it->next;
		}
	}
	return (TRUE);
}
