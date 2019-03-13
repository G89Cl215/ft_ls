/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putlpadstr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 12:09:04 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 12:09:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

void		ft_putlpadstr(size_t pad, char *str)
{
	size_t	len;
	size_t	to_alloc;
	size_t	i;
	char	*to_print;

	if (str)
	{
		len = ft_strlen(str);
		to_alloc = len > pad ? len : pad + 1;
		if (!(to_print = (char*)malloc(to_alloc)))
			return ;
		i = to_alloc;
		to_print[i] = '\0';
		while ((len--) && (i--))
			to_print[i] = str[len];
		while (i--)
			to_print[i] = ' ';
		write(1, to_print, to_alloc);
		free(to_print);
	}
}
