/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_tools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 02:11:07 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/19 23:44:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

int			ft_append_str2(char *str, int size)
{
	char	*tmp;
	int		len;

	tmp = NULL;
	len = ft_strlen(str);
	if (!(tmp = malloc(size + 1)))
		return (0);
	tmp[0] = '\0';
	ft_strcat(tmp, str);
	ft_memset(tmp + len, ' ', size - len);
	tmp[size] = '\0';
	ft_putstr(tmp);
	free(tmp);
	return (1);
}

int			ft_append_str(int str, int size)
{
	char	*tmp;
	char	*res;

	tmp = NULL;
	res = NULL;
	if (!(res = ft_itoa(str)))
		return (0);
	size = size - ft_strlen(res);
	if (!(tmp = ft_memalloc(size + 1)))
		return (0);
	ft_memset(tmp, ' ', size);
	if (!(ft_strappend_back(&tmp, &res)))
		return (0);
	ft_putstr(res);
	free(res);
	return (1);
}

void		ft_print_total(off_t total, int flag)
{
	if ((flag))
	{
		ft_putstr("total ");
		ft_putnbr(total);
		ft_putchar('\n');
	}
}
