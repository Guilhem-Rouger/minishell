/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grouger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/07 15:58:33 by grouger           #+#    #+#             */
/*   Updated: 2023/11/07 16:04:41 by grouger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	t_list	*it;

	it = lst;
	if (lst == NULL)
		return (NULL);
	while (it->next != NULL)
		it = it->next;
	return (it);
}
