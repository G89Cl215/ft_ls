/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pos2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:45:23 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 17:33:41 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

inline static void
	ft_fill_fw_pr(t_pattern *voyager, int i, int j)
{
	if (voyager->precision == i && (voyager->conv & (1 << STAR_PR)))
	{
		voyager->precision = j;
		voyager->conv ^= 1 << STAR_PR;
	}
	if (voyager->field_width == i && (voyager->conv & (1 << STAR_FW)))
	{
		voyager->field_width = j;
		voyager->conv ^= 1 << STAR_FW;
	}
}

int
	ft_pos_pr_fw(int i, t_pattern **pattern, t_list **tmp, va_list *ap)
{
	t_pattern	*voyager;
	char		*str;
	int			j;

	j = va_arg(*ap, int);
	voyager = *pattern;
	if (!(str = ft_itoa(j)))
		return (0);
	while (voyager)
	{
		ft_fill_fw_pr(voyager, i, j);
		voyager = voyager->next;
	}
	if (!(ft_stock_string(tmp, str, ft_strlen(str) + 1)))
	{
		free(str);
		return (0);
	}
	free(str);
	return (1);
}
