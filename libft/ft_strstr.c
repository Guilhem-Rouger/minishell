/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: grouger <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:46:35 by grouger           #+#    #+#             */
/*   Updated: 2023/11/01 17:52:25 by grouger          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *str, const char *srch)
{
	int			i;
	char		*s;
	size_t		n;

	n = ft_strlen(str);
	if ((!str || !srch) && (n == 0))
		return (NULL);
	i = 0;
	s = (char *)str;
	if (ft_strncmp(srch, "", 1) == 0)
		return (s);
	while (s[i] && i + ft_strlen(srch) - 1 < n)
	{
		if (ft_strncmp(&s[i], srch, ft_strlen(srch)) == 0)
			return ((char *)&s[i]);
		++i;
	}
	return (NULL);
}
