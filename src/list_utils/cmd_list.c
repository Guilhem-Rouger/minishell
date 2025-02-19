#include "../../include/minishell.h"

t_cmd	*cmd_create(t_token *token)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->cmd = cmd_join(new, token);
	new->redir = FALSE;
	new->out_file = -1;
	new->in_file = -1;
	redir_check(new, token);
	new->lredir = NULL;
	if (new->redir == TRUE)
		new->lredir = redir_setup(new->lredir, token->next);
	new->is_built = token->builtins;
	new->argv = token->arg;
	new->next = NULL;
    new->back = NULL;
	return (new);
}

t_cmd	*last_cmd(t_cmd *lst)
{
	t_cmd *it;

	it = lst;
	if (lst == NULL)
		return (NULL);
	while (it->next != NULL)
		it = it->next;
	return (it);
}

void	cmd_add_back(t_cmd **cmd, t_cmd *new)
{
	t_cmd	*it;

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

void	delcmd(t_cmd *cmd, void (*del)(void *))
{
	if (cmd->cmd)
		del(cmd->cmd);
	if (cmd->argv)
		clear_tab(cmd->argv);
	free(cmd);
}

void	cmd_clear(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*it;

	if (!del || !lst || !*lst)
		return ;
	while (*lst)
	{
		it = (*lst)->next;
		delcmd(*lst, del);
		*lst = it;
	}
	*lst = NULL;
}
