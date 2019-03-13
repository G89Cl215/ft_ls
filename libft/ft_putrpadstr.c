/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putrpadstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:05:15 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 12:07:51 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void		ft_putrpadstr(size_t pad, char *str)
{
	size_t	len;
	size_t	to_alloc;
	size_t	i;
	char	*to_print;

	if (str)
	{
		len = ft_strlen(str);
		to_alloc = len > pad ? len : pad;
		if (!(to_print = (char*)malloc(to_alloc)))
			return ;
		i = 0;
		while (i < len)
		{
			to_print[i] = str[i];
			i++;
		}
		while (i < to_alloc)
			to_print[i++] = ' ';
		to_print[i] = '\0';
		write(1, to_print, to_alloc);
		free(to_print);
	}
}
