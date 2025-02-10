#include "../../include/minishell.h"

t_env	*env_create(char *str, int index)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->prev = NULL;
	new->next = NULL;
	new->index = index;
	new->str = str;
	new->first_value = str[0];
	return (new);
}

t_env	*last_env(t_env *lst)
{
	t_env	*it;

	it = lst;
	if (lst == NULL)
		return (NULL);
	while (it->next != NULL)
		it = it->next;
	return (it);
}

void	env_add_back(t_env **lst, t_env *neew)
{
	t_env	*it;

	if (!neew)
		return ;
	if (lst && *lst)
	{
		it = *lst;
		while (it->next)
			it = it->next;
		it->next = neew;
	}
	else if (lst)
		*lst = neew;
}

void	delenv(t_env *lst, void (*del)(void *))
{
	if (!del || !lst)
		return ;
	del(lst->str);
	free(lst);
}

void	env_clear(t_env **lst)
{
	t_env	*it;

	if (!lst || !*lst)
		return ;
	while (*lst)
	{
		it = (*lst)->next;
		delenv(*lst, free);
		*lst = it;
	}
	free(lst);
}
