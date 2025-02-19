#include "../../include/minishell.h"

t_redir	*redir_create(t_token *token)
{
    t_redir *new;

    new = ft_calloc(sizeof(t_redir), 1);
    new->type = token->type;
    new->file = token->arg[1];
    new->fd = -1;
    new->fd = operator_choice(token->next->arg, &new->fd);
    new->next = NULL;
    new->back = NULL;
    return (new);
}

t_redir	*last_redir(t_redir *lst)
{
	t_redir *it;

	it = lst;
	if (lst == NULL)
		return (NULL);
	while (it->next != NULL)
		it = it->next;
	return (it);
}

void	redir_add_back(t_redir **cmd, t_redir *new)
{
	t_redir	*it;

	if (!new)
		return ;
	if (cmd && *cmd)
	{
		it = *cmd;
		while (it->next)
			it = it->next;
		it->next = new;
        new->back = it;
	}
	else if (cmd)
		*cmd = new;
}

void	delredir(t_redir *cmd, void (*del)(void *))
{
	if (cmd->file)
		del(cmd->file);
	free(cmd);
}

void	redir_clear(t_redir **lst, void (*del)(void *))
{
	t_redir	*it;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		it = (*lst)->next;
		delredir(*lst, del);
		*lst = it;
	}
	*lst = NULL;
}
