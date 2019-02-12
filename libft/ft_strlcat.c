/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 14:14:56 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/15 14:06:20 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	i;
	size_t	j;

	j = 0;
	i = ft_strlen(dest);
	if (i < n)
	{
		while (src[j] && i + j + 1 < n)
		{
			dest[i + j] = src[j];
			j++;
		}
		dest[i + j] = '\0';
		return (i + ft_strlen(src));
	}
	else
		return (n + ft_strlen(src));
}
