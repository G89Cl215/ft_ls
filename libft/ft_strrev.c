/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrev.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/02 12:02:32 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/16 13:41:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrev(char *str)
{
	size_t	l;
	size_t	c;
	char	tmp;

	c = ft_strlen(str);
	l = 0;
	while (l < c / 2)
	{
		tmp = str[l];
		str[l] = str[c - l - 1];
		str[c - l - 1] = tmp;
		l++;
	}
	return (str);
}
