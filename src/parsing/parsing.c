/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/10 18:09:56 by grouger           #+#    #+#             */
/*   Updated: 2025/02/11 17:28:48 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool check_endpipe(char *line)
{
    int i;

    i = 0;
    while (line[i + 1])
    {
        if ((line[i] == '|' && line[i + 1] == '|') || (line[i] == '|' && line[i + 1] == ' '))
        {
            i += 2;
            while(line[i + 1] && line[i] == ' ')
                i++;
            if (line[i] == '|' && line [i + 1] == '|')
            {
                ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
                return (FALSE);
            }
            else if (line[i] == '|')
            {
                ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
                return (FALSE);
            }
        }
        i++;
    }
    return (TRUE);
}

bool check_startpipe(char *line)
{
    if (ft_strlen(line) > 1 && line[0] == '|' && line[1] == '|')
    {
        ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
        return (FALSE);
    }
    else if (line[0] == '|')
    {
        ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
        return (FALSE);
    }
    if (ft_strlen(line) > 2 && !check_endpipe(line))
        return (FALSE);
    return (TRUE);
}

bool check_red(char *line)
{
    if (line[0] == '>' || line[0] == '<')
    {
        if (line[1] == '>' || line[1] == '<' || !line[1])
        {
            if (ft_strlen(line) > 4 && line[2] == '|' && line[3] == '|')
            {
                ft_putstr_fd("bash: syntax error near unexpected token `||'\n", 2);
                g_exit_value = 2;
                return (FALSE);
            }
            if (ft_strlen(line) > 3 && line[2] == '|')
            {
                ft_putstr_fd("bash: syntax error near unexpected token `|'\n", 2);
                g_exit_value = 2;
                return (FALSE);
            }
            if (ft_strlen(line) <= 2)
            {
                ft_putstr_fd("bash: syntax error near\nunexpected token `newline'\n", 2);
                g_exit_value = 2;
                return (FALSE);
            }
        }
    }
    if (!check_startpipe(line))
    {
        g_exit_value = 2;
        return (FALSE);
    }
    return (TRUE);
}

bool check_other(char *line)
{
    if (ft_strlen(line) > 1 && line[0] == '&' && line[1] == '&')
    {
        ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
        g_exit_value = 2;
        return (FALSE);
    }
    if (line[0] == '&')
    {
        ft_putstr_fd("bash: syntax error near unexpected token `&'\n", 2);
        g_exit_value = 2;
        return (FALSE);
    }
    return (TRUE);
}

bool check_line(char *line)
{
 if (!check_red(line))
    return (FALSE);
if (!check_other(line))
    return (FALSE);
return (TRUE);
}