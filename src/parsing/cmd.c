#include "../../include/minishell.h"

bool cmd_setup(t_token *token, t_data *data)
{
    t_token *it;

    it = token;
    data->cmd = NULL;
    while (it)
    {  
        if (it->type == CMD)
            cmd_add_back(&(data->cmd), cmd_create(it));
        it = it->next;
    }
    return (TRUE);
}

t_redir *redir_setup(t_redir *redir, t_token *token)
{
    t_token *it;

    if (token->type != 1 || token->type != 2 || token->type != 3 || token->type != 4)
        return (NULL);
    it = token;
    while (it && (it->type == 1 || it->type == 2 || it->type == 3 || it->type == 4))
    {
        redir_add_back(&(redir), redir_create(token));
        it = it->next;
    }
    return (redir);
}

void redir_check(t_cmd *cmd, t_token *token)
{
    t_token *it;

    if (token->next)
        it = token->next;
    else
    {
        cmd->redir = FALSE;
        return ;
    }
    while (it && it->type != PIPE)
    {
        if (token->str[0] == '>')
	    {
    	    cmd->out_file = operator_choice(token->next->arg, &cmd->out_file);
		    cmd->redir = TRUE;
	    }
	    else if (token->str[0] == '<')
	    {
    	    cmd->in_file = operator_choice(token->next->arg, &cmd->in_file);
		    cmd->redir = TRUE;
	    }
        else
            cmd->redir = FALSE;
        it = it->next;
    }
    return ;
}


void cmd_join(t_cmd *cmd, t_token *token)
{
    char *temp;
    int i;

    i = 1;
    temp = ft_strdup(token->arg[0]);
    
    while (token->arg[i])
    {
        temp = ft_strjoin(temp, " ");
        temp = ft_strjoin(temp, token->arg[i]);
        i++;
    }
    if (!temp)
    {
        cmd->cmd = NULL;
        return ;
    }
    cmd->cmd = ft_strdup(temp);
    free(temp);
    return ;
}