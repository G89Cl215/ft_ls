/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 15:58:07 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/16 12:01:41 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_atoi(const char *str)
{
	unsigned int	res;
	int				sign;

	while (!(res = 0) && (!(*str < '\t' || *str > '\r') || *str == ' '))
		str++;
	sign = (*str == '-' ? -1 : 1);
	if ((*str == '+' || *str == '-'))
		str++;
	while (ft_isdigit(*str))
	{
		res = res * 10 + (*str - '0');
		str++;
	}
	return (res * sign);
}
