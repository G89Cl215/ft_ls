/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unsigned_itoa_base.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 22:07:45 by tgouedar          #+#    #+#             */
/*   Updated: 2019/01/25 17:43:13 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_unsigned_itoa_base(unsigned long long nbr, char *base)
{
	unsigned long long	conv;
	int					i;
	char				*res;
	int					length;

	length = ft_strlen(base);
	conv = nbr;
	i = 1;
	while (conv /= length)
		i++;
	if (!(res = ft_strnew(i)))
		return (NULL);
	res[0] = base[0];
	while (nbr)
	{
		res[--i] = base[nbr % length];
		nbr /= length;
	}
	return (res);
}
