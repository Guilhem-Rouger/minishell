#include "../../include/minishell.h"

bool cmd_setup(t_token *token, t_data *data)
{
    t_token *it;

    it = token;
    data->cmd = NULL;
    while (it)
    {  
        if (it->type == CMD)
            cmd_add_back(&(data->cmd), cmd_create(token));
        it = it->next;
    }
    return (TRUE);
}

void *cmd_join(t_cmd *cmd, t_token *token)
{
    char *temp;
    int i;

    i = 0;
    temp = token->str;
    
    while (token->arg[i])
    {
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