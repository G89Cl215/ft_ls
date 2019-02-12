/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:26:36 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/16 13:38:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(const char *haystack, const char *needle)
{
	size_t	i;

	if (ft_strlen(needle) == 0)
		return ((char*)haystack);
	while (*haystack)
	{
		if (*haystack == *needle)
		{
			i = 1;
			while (needle[i] && haystack[i] == needle[i])
				i++;
			if (!(needle[i]))
				return ((char*)haystack);
		}
		haystack++;
	}
	return (NULL);
}
