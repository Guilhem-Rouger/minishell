/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:02:28 by grouger           #+#    #+#             */
/*   Updated: 2025/02/11 18:36:02 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int redir_scan(t_token *token, t_token *last)
{
    t_token *it;

    it = token;
    while (it != last && it->next != last)
        it = it->next;
    if (it->type == 2 || it->type == 3 || it->type == 4 || it->type == 1)
        return(1);
    return(0);
}

bool lastredir_check(t_token *token)
{
    t_token *it;
    int bol;
    
    it = last_token(token);
    bol = redir_scan(token, it);
    if (bol == 0 && (it->type == 2 || it->type == 3 || it->type == 4 || it->type == 1))
    {
        ft_putstr_fd("bash: syntax error near unexpected token `newline'\n", 2);
        return (FALSE);
    }
    if (it->type == HEREDOC)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `<<'\n", 2);
        return (FALSE);
    }
    if (it->type == TRUNC)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `>'\n", 2);
        return (FALSE);
    }
    if (it->type == INPUT)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `<'\n", 2);
        return (FALSE);
    }
    if (it->type == APPEND)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `>>'\n", 2);
        return (FALSE);
    }
    return (TRUE);
}

bool valid_dir(char *str)
{
    int i;
    int count;

    i = 0;
    count = 0;
    while (str[i])
    {
        if (str[i] != '/' && str[i] != '.')
            return (FALSE);
        if (str[i] == '.')
            count++;
        else if(str[i] == '/')
            count = 0;
        if (count == 3)
            return (FALSE);
        i++;
    }
    return (TRUE);
}

bool dir_check(t_token *token)
{
    t_token *it;

    it = token;
    if (it->str[0] == '/' || it->str[0] == '.')
    {
        if (!valid_dir(it->str))
        {
            ft_putstr_fd("bash: ", 2);
            ft_putstr_fd(it->str, 2);
            ft_putstr_fd(": No such file or directory\n", 2);
            g_exit_value = 127;
            return (FALSE);
        }
        else
        {
            ft_putstr_fd("bash: ", 2);
            ft_putstr_fd(it->str, 2);
            ft_putstr_fd(": Is a directory\n", 2);
            g_exit_value = 126;
        }
    }
    return (TRUE);
}

bool token_verif(t_token *token)
{
    if (!lastredir_check(token))
    {
        g_exit_value = 2;
        return (FALSE);
    }
    if (!dir_check(token))
        return (FALSE);
    return (TRUE);
}
