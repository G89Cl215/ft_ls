/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/12 21:27:42 by tgouedar          #+#    #+#             */
/*   Updated: 2018/12/09 12:18:20 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	ft_word(char const *str, char c)
{
	size_t	k;

	k = (*str - c ? 1 : 0);
	while (*str)
	{
		while (*str && (*str - c))
			str++;
		while (*str && !(*str - c))
			str++;
		if (*str)
			k++;
	}
	return (k);
}

char			**ft_strsplit(char const *str, char c)
{
	size_t	k;
	size_t	l;
	char	**res;

	if (!(k = 0) && (!str || !c))
		return (NULL);
	if (!(res = (char**)malloc(sizeof(*res) * ft_word(str, c) + 1)))
		return (NULL);
	while (!(l = 0) && *str)
	{
		while (*str && !(*str - c))
			str++;
		while (str[l] && (str[l] - c))
			l++;
		if (!(l))
			break ;
		res[k++] = ft_strndup(str, l);
		str += l;
	}
	res[k] = 0;
	return (res);
}
