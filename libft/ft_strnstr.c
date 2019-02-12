/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:59:36 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/15 19:00:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t n)
{
	size_t	i;

	if (!(i = 0) && !(ft_strlen(needle)))
		return ((char*)haystack);
	while (*haystack && i < n)
	{
		if (*haystack == *needle)
		{
			i = 1;
			while (needle[i] && haystack[i] == needle[i] && i < n)
				i++;
			if (!(needle[i]))
				return ((char*)haystack);
		}
		haystack++;
		n--;
	}
	return (NULL);
}
