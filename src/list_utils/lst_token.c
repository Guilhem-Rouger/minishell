#include "../../include/minishell.h"

t_token	*token_create(char *str, int token)
{
	t_token	*new;

	new = ft_calloc(sizeof(t_token), 1);
	if (!new)
		return (NULL);
	token_quote(str, new);
	new->path = NULL;
	new->prev = NULL;
	new->arg = NULL;
	new->next = NULL;
	new->type = token;
	return (new);
}

t_token	*last_token(t_token *lst)
{
	t_token	*it;

	it = lst;
	if (lst == NULL)
		return (NULL);
	while (it->next != NULL)
		it = it->next;
	return (it);
}

void	token_add_back(t_token **lst, t_token *new)
{
	t_token	*it;

	if (!new)
		return ;
	if (lst && *lst)
	{
		it = *lst;
		while (it->next)
			it = it->next;
		it->next = new;
	}
	else if (lst)
		*lst = new;
}

void	deltok(t_token *token, void (*del)(void *))
{
	if (token->str)
		del(token->str);
	if (token->path)
		del(token->path);
	if (token->arg)
		clear_tab(token->arg);
	free(token);
}

void	token_clear(t_token **lst, void (*del)(void *))
{
	t_token	*it;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		it = (*lst)->next;
		deltok(*lst, del);
		*lst = it;
	}
	*lst = NULL;
}
