/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grouger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 16:07:06 by grouger           #+#    #+#             */
/*   Updated: 2023/11/08 15:30:19 by grouger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*it;

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
