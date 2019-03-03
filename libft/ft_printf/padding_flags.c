/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_flags.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:41:55 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 20:16:38 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int		ft_padding_flags5(t_pattern *voyager, t_list *vonc)
{
	if (voyager->conv & ((size_t)1 << (ft_indice('+', KNOWN_FLAG) + 1)))
	{
		if (*((char*)(vonc->content)) == '-'
		&& voyager->precision > voyager->field_width)
			ft_padding_negativ(voyager, vonc);
		if (voyager->precision >= (int)ft_strlen((char*)(vonc->content))
		&& *((char*)(vonc->content)) == '-')
			ft_padding_prec(voyager, vonc);
		if (!(ft_padding_positiv(voyager, vonc)))
			return (0);
	}
	return (1);
}

inline static int		ft_padding_flags4(t_pattern *voyager, t_list *vonc)
{
	size_t i;

	i = 1;
	if (!(voyager->conv & (i << (ft_indice('+', KNOWN_FLAG) + 1))))
	{
		if ((voyager->precision > -1
		&& !(voyager->conv & (i << (TYPE_START + ft_indice('f', KNOWN_CONV)))))
		&& !(voyager->conv & (i << (TYPE_START + ft_indice('F', KNOWN_CONV))))
		&& (!(voyager->conv & (i << (TYPE_START + ft_indice('s', KNOWN_CONV))))
		&& (!(voyager->conv & (i << (TYPE_START + ft_indice('c', KNOWN_CONV))))
		&& (!(voyager->conv & (i << (TYPE_START + ft_indice('k', KNOWN_CONV))))
	&& (!(voyager->conv & (i << (TYPE_START + ft_indice('%', KNOWN_CONV)))))))))
			if (!(ft_padding_prec(voyager, vonc)))
				return (0);
		if (voyager->field_width > -1)
			if (!(ft_padding_spaces(voyager, vonc)))
				return (0);
		if (voyager->conv & (i << (STAR_FW))
		&& voyager->field_width < 0)
			if (!(ft_padding_negative_fw(voyager, vonc)))
				return (0);
	}
	return (1);
}

inline static int		ft_padding_flags3(t_pattern *voyager, t_list *vonc)
{
	size_t i;

	i = 1;
	if ((voyager->conv & (i << (TYPE_START + ft_indice('x', KNOWN_CONV)))
	|| voyager->conv & (i << (TYPE_START + ft_indice('X', KNOWN_CONV))))
	&& voyager->precision > -1)
		if (!(ft_padding_prec(voyager, vonc)))
			return (0);
	if (voyager->conv & (i << (ft_indice('#', KNOWN_FLAG) + 1))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('u', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('U', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('f', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('F', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('E', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('e', KNOWN_CONV)))))
		if (!(ft_base_prefix(voyager, vonc)))
			return (0);
	if (!(ft_padding_flags4(voyager, vonc)))
		return (0);
	return (1);
}

inline static int		ft_padding_flags2(t_pattern *voyager, t_list *vonc)
{
	size_t j;

	j = 1;
	if (voyager->conv & (j << (ft_indice('-', KNOWN_FLAG) + 1)))
	{
		if ((voyager->conv & (j << (ft_indice('+', KNOWN_FLAG) + 1))
		|| voyager->conv & (j << (ft_indice(' ', KNOWN_FLAG) + 1))
		|| (voyager->conv & (j << (ft_indice('#', KNOWN_FLAG) + 1))
		&& voyager->precision == (int)ft_strlen((char*)(vonc->content))
		&& voyager->precision >= 1 && *((char*)(vonc->content)) != '0'
		&& !(voyager->conv & (j << (TYPE_START + ft_indice('x', KNOWN_CONV))))
		&& !(voyager->conv & (j << (TYPE_START + ft_indice('X', KNOWN_CONV))))))
		&& !(voyager->conv & (j << (TYPE_START + ft_indice('%', KNOWN_CONV))))
		&& *((char*)(vonc->content)) != '-')
			voyager->field_width = voyager->field_width - 1;
		if (!(ft_padding_negativ(voyager, vonc)))
			return (0);
	}
	if (!(ft_padding_flags5(voyager, vonc)))
		return (0);
	if (voyager->conv & (j << (ft_indice(' ', KNOWN_FLAG) + 1))
	&& !(voyager->conv & (j << (TYPE_START + (ft_indice('k', KNOWN_CONV))))))
		if (!(ft_padding_flag_space(voyager, vonc)))
			return (0);
	return (1);
}

int						ft_padding_flags(t_pattern *voyager, t_list *vonc)
{
	size_t j;

	j = 2;
	if ((voyager->conv & (j << (ft_indice('0', KNOWN_FLAG)))
	&& (!(voyager->conv & (j << (ft_indice('-', KNOWN_FLAG))))
	&& voyager->precision <= -1))
	|| (voyager->conv & (j << (ft_indice('-', KNOWN_FLAG)))
	&& voyager->conv & (j << (ft_indice('+', KNOWN_FLAG)))
	&& voyager->conv & (j << (ft_indice('0', KNOWN_FLAG)))))
		if (!(ft_padding_zero(voyager, vonc)))
			return (0);
	if (!(ft_padding_flags2(voyager, vonc)))
		return (0);
	if (!(ft_padding_flags3(voyager, vonc)))
		return (0);
	return (1);
}
