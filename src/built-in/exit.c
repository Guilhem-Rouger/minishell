#include "../../include/minishell.h"

/* Commande built-in exit : termine proprement l'exécution du shell
** - Libère la mémoire allouée pour la ligne de commande
** - Nettoie toutes les ressources (environnement, tokens, etc.)
** - Efface l'historique des commandes
** - Quitte le programme avec le code de sortie stocké dans g_exit_value
**
** @param data: structure contenant les données du shell à nettoyer
**
** Note : g_exit_value est une variable globale qui contient le code
** de sortie de la dernière commande exécutée */
void	exit_command(t_data *data)
{
	free(data->line);           /* Libère la ligne de commande courante */
	clear_all(data);            /* Nettoie toutes les ressources */
	rl_clear_history();         /* Efface l'historique des commandes */
	exit(g_exit_value);         /* Quitte avec le code de sortie approprié */
}
