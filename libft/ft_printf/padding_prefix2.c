/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_prefix2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 20:12:51 by baavril           #+#    #+#             */
/*   Updated: 2019/02/09 15:20:39 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	ft_prefix4(t_pattern *voyager, t_list *vonc, t_ul type, int len)
{
	if ((voyager->precision - (int)ft_strlen((char*)(vonc->content))) == -1
	&& *((char*)(vonc->content)) != '0'
	&& ft_strlen((char*)(vonc->content)) > 1 && voyager->field_width <= -1
	&& !(voyager->conv & ((size_t)2 << (ft_indice('0', KNOWN_FLAG))))
	&& voyager->precision > 2)
		ft_memmove((char*)(vonc->content),
		((char*)(vonc->content)) + 2, len);
	if (voyager->field_width > voyager->precision
	&& voyager->field_width >= len
	&& ((char*)(vonc->content))[ft_strlen((char*)(vonc->content)) - 1] == ' '
	&& (voyager->conv & (2 << (ft_indice('-', KNOWN_FLAG))))
	&& (type & ((size_t)1 << (ft_indice('x', KNOWN_CONV)))
	|| type & ((size_t)1 << (ft_indice('X', KNOWN_CONV)))))
		((char*)(vonc->content))[voyager->field_width] = '\0';
	return (1);
}

inline static int
	ft_prefix3(t_pattern *voyager, t_list *vonc, t_ul type, int len)
{
	if ((!(type & (1 << (ft_indice('o', KNOWN_CONV)))))
	&& (!(type & ((size_t)1 << (ft_indice('O', KNOWN_CONV))))))
	{
		if ((type & (1 << (ft_indice('p', KNOWN_CONV))))
		&& voyager->precision == 0
		&& ft_strlen((char*)(vonc->content)) == 3)
			((char*)(vonc->content))[2] = '\0';
		if ((((ft_strlen((char*)vonc->content) == 1 || len == 1)
		&& (!(type & (1 << (ft_indice('p', KNOWN_CONV))))))
		&& *((char*)(vonc->content)) == '0' && voyager->precision > -1
		&& voyager->precision != 1))
			ft_bzero((char*)(vonc->content), len);
	}
	return (1);
}

inline static int
	ft_prefix2(t_pattern *voyager, t_list *vonc, t_ul type, int len)
{
	if (voyager->conv & (2 << (ft_indice('-', KNOWN_FLAG)))
	&& !(type & (1 << (ft_indice('o', KNOWN_CONV)))
	|| type & (1 << (ft_indice('p', KNOWN_CONV))))
	&& ((char*)(vonc->content))[len] == ' '
	&& !(type & ((size_t)1 << (ft_indice('O', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('x', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('X', KNOWN_CONV)))))
		((char*)(vonc->content))[len] = '\0';
	if (voyager->conv & (2 << (ft_indice('-', KNOWN_FLAG)))
	&& (type & (1 << (ft_indice('o', KNOWN_CONV)))
	|| type & ((size_t)1 << (ft_indice('O', KNOWN_CONV))))
	&& voyager->precision <= -1 && voyager->field_width > 2
	&& (voyager->field_width == len || voyager->field_width == len - 1)
	&& ((char*)(vonc->content))[len] == ' ')
		((char*)(vonc->content))[len] = '\0';
	if (!(ft_prefix3(voyager, vonc, type, len)))
		return (0);
	return (1);
}

inline static int
	ft_prefix_bis(t_pattern *voyager, t_list *vonc, char *str, int len)
{
	t_ul		type;

	type = ft_type_flag(voyager);
	if (((type & (1 << (ft_indice('p', KNOWN_CONV))))
	|| (len > 1 && !(type & (1 << (ft_indice('o', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('O', KNOWN_CONV)))))
	|| (*((char*)(vonc->content)) != '0')
	|| (type & (1 << (ft_indice('o', KNOWN_CONV)))
	&& voyager->field_width <= 0 && voyager->precision <= -1))
	&& !((type & ((size_t)1 << (ft_indice('x', KNOWN_CONV)))
	|| type & ((size_t)1 << (ft_indice('X', KNOWN_CONV))))
	&& ft_strspn((char*)(vonc->content), " 0")
	== ft_strlen((char*)(vonc->content))))
	{
		if (voyager->precision > -1 && len > 1)
			if (!(ft_padding_prec3(voyager, vonc)))
				return (0);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	else
		ft_strdel(&str);
	return (1);
}

int
	ft_prefix(t_pattern *voyager, t_list *vonc, char *str, int len)
{
	t_ul		type;

	type = ft_type_flag(voyager);
	if (voyager->conv & (2 << (ft_indice('0', KNOWN_FLAG)))
	&& *((char*)(vonc->content)) == '0' && voyager->field_width > 1
	&& (!(voyager->conv & (2 << (ft_indice('-', KNOWN_FLAG)))))
	&& (!(voyager->conv & (1 << (TYPE_START + ft_indice('o', KNOWN_CONV)))))
	&& (!(voyager->conv
	& ((size_t)1 << (TYPE_START + ft_indice('O', KNOWN_CONV)))))
	&& (!((type & ((size_t)1 << (ft_indice('x', KNOWN_CONV)))
	|| type & ((size_t)1 << (ft_indice('X', KNOWN_CONV))))
	&& (ft_strspn((char*)(vonc->content), " 0")
	== ft_strlen((char*)(vonc->content))))
	&& ft_strspn((char*)(vonc->content), "0") > 2))
		ft_memmove((char*)(vonc->content),
		((char*)(vonc->content)) + 2, len - 1);
	if (!(ft_prefix_bis(voyager, vonc, str, len)))
		return (0);
	if (!(ft_prefix2(voyager, vonc, type, len)))
		return (0);
	return (1);
}
