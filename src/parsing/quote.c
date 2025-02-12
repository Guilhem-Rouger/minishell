#include "../../include/minishell.h"

/* Vérifie récursivement la validité des quotes dans une chaîne
** @param str: chaîne à vérifier
** @param sq: état des quotes simples (TRUE si ouvert)
** @param dq: état des quotes doubles (TRUE si ouvert)
** @return: TRUE si toutes les quotes sont correctement fermées
**
** Règles :
** - Les quotes simples (') ne sont pas interprétées dans les quotes doubles
** - Les quotes doubles (") ne sont pas interprétées dans les quotes simples
** - Une quote ouverte doit être fermée par une quote du même type */
bool	check_quote_recurs(const char *str, bool sq, bool dq)
{
	/* Fin de chaîne : vérifie qu'aucune quote n'est ouverte */
	if (*str == '\0')
		return (!sq && !dq);
	
	/* Gestion des quotes doubles */
	if (*str == '\"')
	{
		if (!sq)  /* Ignore si dans des quotes simples */
			dq = !dq;  /* Inverse l'état des quotes doubles */
	}
	/* Gestion des quotes simples */
	else if (*str == '\'')
	{
		if (!dq)  /* Ignore si dans des quotes doubles */
			sq = !sq;  /* Inverse l'état des quotes simples */
	}
	/* Continue récursivement avec le caractère suivant */
	return (check_quote_recurs(str + 1, sq, dq));
}

/* Fonction wrapper pour vérifier les quotes d'une ligne
** @param line: ligne à vérifier
** @return: TRUE si toutes les quotes sont correctement fermées */
bool	quote_check(char *line)
{
	return (check_quote_recurs(line, FALSE, FALSE));
}
