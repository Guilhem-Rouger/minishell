/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_verif.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 20:02:28 by grouger           #+#    #+#             */
/*   Updated: 2025/02/10 21:11:03 by guilhem          ###   ########.fr       */
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

bool char_check(t_token *token)
{
    t_token *it;
    t_token *last;

    last = last_token(token);
    it = token;
    while (it != last && it->next != last)
        it = it->next;
    if (last->type == PIPE && it->type == PIPE)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
        return (FALSE);
    }
    if (last->type == PIPE)
    {
        ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
        return (FALSE);
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
    if (!char_check(token))
        return (FALSE);
    return (TRUE);
}