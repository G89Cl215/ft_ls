/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 20:06:00 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/15 18:25:15 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t	i;

	if (n > 0)
	{
		i = (dst < src ? 0 : n - 1);
		while (ft_btw(i, 0, n - 1))
		{
			*((char*)dst + i) = *((char*)src + i);
			i += (dst < src ? 1 : -1);
		}
	}
	return (dst);
}
