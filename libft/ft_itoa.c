/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/08 16:09:08 by tgouedar          #+#    #+#             */
/*   Updated: 2019/01/27 09:01:08 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(intmax_t nb)
{
	char			*res;
	intmax_t		j;
	size_t			i;
	int				s;

	i = 0;
	s = (nb < 0 ? -1 : 1);
	j = s * nb;
	while (++i && j)
		j /= 10;
	((s < 0 || !nb) ? 1 : --i);
	if (!(res = ft_strnew(i)))
		return (NULL);
	while (i > 0)
	{
		j = (s * nb) % 10;
		res[--i] = (ft_isdigit(j + '0') ? j + '0' : -1 * j + '0');
		nb /= 10;
	}
	(s < 0 ? res[0] = '-' : 1);
	return (res);
}
