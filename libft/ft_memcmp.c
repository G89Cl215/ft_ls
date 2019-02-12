/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 21:35:55 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/07 21:52:05 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t	i;
	int		cmp;

	i = 0;
	while (i < n)
	{
		if ((cmp = *((unsigned char*)s1 + i) - *((unsigned char*)s2 + i)))
			return (cmp);
		i++;
	}
	return (0);
}
