/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_syntax.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: guilhem <guilhem@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/12 15:14:33 by grouger           #+#    #+#             */
/*   Updated: 2025/02/12 15:18:26 by guilhem          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

bool check_endother(char *line)
{
    int i;

    i = 0;
    while (line[i + 1])
    {
        if ((line[i] == '&' && line[i + 1] == '&') || (line[i] == '&' && line[i + 1] == ' '))
        {
            i += 2;
            while(line[i + 1] && line[i] == ' ')
                i++;
            if (line[i] == '&' && line [i + 1] == '&')
            {
                ft_putstr_fd("bash: syntax error near unexpected token `&&'\n", 2);
                return (FALSE);
            }
            else if (line[i] == '&')
            {
                ft_putstr_fd("bash: syntax error near unexpected token `&'\n", 2);
                return (FALSE);
            }
        }
        i++;
    }
    return (TRUE);
}