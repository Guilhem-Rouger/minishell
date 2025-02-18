#include "../../include/minishell.h"

t_cmd	*cmd_create(t_token *token)
{
	t_cmd	*new;

	new = ft_calloc(sizeof(t_cmd), 1);
	if (!new)
		return (NULL);
	new->cmd = cmd_join(new, token);
	new->is_built = token->builtins;
	new->argv = token->arg;
	new->redir = FALSE;
	new->out_file = -1;
	new->in_file = -1;
	if (token->next->str[0] == '>')
	{
    	new->out_file = operator_choice(token->next->arg, &new->out_file);
		new->redir = TRUE;
	}
	if (token->next->str[0] == '<')
	{
    	new->in_file = operator_choice(token->next->arg, &new->in_file);
		new->redir = TRUE;
	}
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
