/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grouger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 12:23:40 by grouger           #+#    #+#             */
/*   Updated: 2023/11/02 12:57:31 by grouger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char *s1, char *s2)
{
	char	*re;
	int		i;
	int		ls1;
	int		ls2;
	int		l;

	if (!s1 || !s2)
		return (NULL);
	ls1 = ft_strlen((char *)s1);
	ls2 = ft_strlen((char *)s2);
	re = malloc((ls1 + ls2 + 1) * sizeof(char));
	if (!re)
		return (NULL);
	i = 0;
	l = 0;
	while (l < ls1)
		re[l++] = s1[i++];
	i = 0;
	while (l < (ls2 + ls1))
		re[l++] = s2[i++];
	re[l] = '\0';
	free(s1);
	return (re);
}
