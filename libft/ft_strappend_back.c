/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/29 17:15:19 by tgouedar          #+#    #+#             */
/*   Updated: 2019/01/31 14:40:16 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

int		ft_strappend_back(char **src, char **dest)
{
	char	*tmp;
	size_t	i;

	i = ft_strlen(*dest) + ft_strlen(*src) + 1;
	if (!(tmp = (char*)malloc(i)))
		return (0);
	ft_memcpy(tmp, *src, ft_strlen(*src) + 1);
	tmp = ft_strcat(tmp, *dest);
	ft_memdel((void**)dest);
	ft_memdel((void**)src);
	*dest = tmp;
	return (1);
}
