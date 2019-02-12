/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:17:02 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/16 12:30:40 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		if (!(*((unsigned char*)s + (i * sizeof(*s))) - (unsigned char)c))
			return ((void*)(s + (i * sizeof(*s))));
		i++;
	}
	return (NULL);
}
