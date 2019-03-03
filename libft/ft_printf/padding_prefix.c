/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_prefix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:43:03 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 20:22:31 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int
	ft_base_prefix_ter(t_pattern *voyager, t_list *vonc, t_ul type, char *str)
{
	int len;

	len = ft_strlen((char*)(vonc->content));
	if ((type & (1 << (ft_indice('o', KNOWN_CONV)))
	|| type & ((size_t)1 << (ft_indice('O', KNOWN_CONV))))
	&& ((voyager->precision == -1 || voyager->precision == 0)
	|| (voyager->precision - len <= 0)))
	{
		str[0] = '0';
		str[1] = '\0';
	}
	if (*((char*)(vonc->content)) == '0' && len == 1
	&& !(type & (1 << (ft_indice('p', KNOWN_CONV)))))
		str[0] = '\0';
	str[2] = '\0';
	if (!(ft_prefix(voyager, vonc, str, len)))
		return (0);
	return (1);
}

inline static int
	ft_base_prefix_bis(t_pattern *voyager, char *str)
{
	t_ul		type;

	type = ft_type_flag(voyager);
	if (type & (1 << (ft_indice('x', KNOWN_CONV)))
	|| type & (1 << (ft_indice('p', KNOWN_CONV))))
	{
		str[0] = '0';
		str[1] = 'x';
	}
	if (type & (1 << (ft_indice('X', KNOWN_CONV))))
	{
		str[0] = '0';
		str[1] = 'X';
	}
	if (type & (1 << (ft_indice('b', KNOWN_CONV))))
	{
		str[0] = '0';
		str[1] = 'b';
	}
	return (1);
}

int
	ft_base_prefix(t_pattern *voyager, t_list *vonc)
{
	char		*str;
	t_ul		type;
	int			len;

	len = ft_strlen((char*)(vonc->content));
	type = ft_type_flag(voyager);
	if (!(str = ft_strnew(2)))
		return (0);
	if (!(ft_base_prefix_bis(voyager, str)))
		return (0);
	if (!(ft_base_prefix_ter(voyager, vonc, type, str)))
		return (0);
	if (!(ft_prefix4(voyager, vonc, type, len)))
		return (0);
	return (1);
}
