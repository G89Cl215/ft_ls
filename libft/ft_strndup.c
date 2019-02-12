/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 18:26:04 by tgouedar          #+#    #+#             */
/*   Updated: 2018/12/09 12:13:59 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

char	*ft_strndup(const char *str, size_t n)
{
	size_t	i;
	char	*dup;

	i = (n < ft_strlen(str) ? n : ft_strlen(str));
	if (!(dup = (char *)malloc(sizeof(*dup) * (i + 1))))
		return (NULL);
	dup[i] = '\0';
	while (i-- > 0)
		dup[i] = str[i];
	return (dup);
}
