/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_zero.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:43:43 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/09 15:33:52 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int
	ft_padding_zero4(t_pattern *voyager, t_list *vonc, int len)
{
	if (!(voyager->conv & (1 << (TYPE_START + ft_indice('o', KNOWN_CONV))))
	&& (!(voyager->conv
	& ((size_t)1 << (TYPE_START + ft_indice('O', KNOWN_CONV)))))
	&& (voyager->conv & (1 << (TYPE_START + ft_indice('x', KNOWN_CONV)))
	|| voyager->conv & ((size_t)1 << (TYPE_START + ft_indice('X', KNOWN_CONV))))
	&& voyager->conv & (2 << (ft_indice('#', KNOWN_FLAG)))
	&& voyager->field_width >= len + 2 && ((char*)(vonc->content))[2] != '0')
		ft_memmove((char*)(vonc->content),
		(char*)(vonc->content) + 2, ft_strlen((char*)(vonc->content) + 1));
	else if (!(voyager->conv & (1 << (TYPE_START + ft_indice('o', KNOWN_CONV))))
	&& (!(voyager->conv
	& ((size_t)1 << (TYPE_START + ft_indice('O', KNOWN_CONV)))))
	&& (voyager->conv & (1 << (TYPE_START + ft_indice('x', KNOWN_CONV)))
	|| voyager->conv & ((size_t)1 << (TYPE_START + ft_indice('X', KNOWN_CONV))))
	&& voyager->conv & (2 << (ft_indice('#', KNOWN_FLAG)))
	&& voyager->field_width >= len + 1 && ((char*)(vonc->content))[1] != '0')
		ft_memmove((char*)(vonc->content), (char*)(vonc->content) + 1, len + 1);
	return (1);
}

inline static int
	ft_padding_zero3(t_pattern *voyager, t_list *vonc, int len, char *str)
{
	if (!(voyager->conv & ((size_t)2 << (ft_indice('#', KNOWN_FLAG)))
	&& voyager->field_width - len < 2)
	&& !(voyager->conv & (1 << (TYPE_START + ft_indice('x', KNOWN_CONV))))
	&& !(voyager->conv & (1 << (TYPE_START + ft_indice('X', KNOWN_CONV)))))
	{
		if (!(str = ft_strnew(voyager->field_width - len)))
			return (0);
		ft_memset(str, '0', voyager->field_width - len);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	else if (voyager->conv & ((size_t)2 << (ft_indice('#', KNOWN_FLAG))))
	{
		if (!(str = ft_strnew(voyager->field_width - len)))
			return (0);
		ft_memset(str, '0', voyager->field_width - len);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

inline static int
	ft_padding_zero2(t_pattern *voyager, t_list *vonc)
{
	int		len;
	char	*str;

	str = NULL;
	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width - len > 0
	&& !(voyager->conv & ((size_t)2 << (ft_indice(' ', KNOWN_FLAG)))))
	{
		if (!(ft_padding_zero3(voyager, vonc, len, str)))
			return (0);
	}
	else if (voyager->field_width - len - 1 > 0
	&& (voyager->conv & ((size_t)2 << (ft_indice(' ', KNOWN_FLAG)))))
	{
		if (!(str = ft_strnew(voyager->field_width - len - 1)))
			return (0);
		ft_memset(str, '0', voyager->field_width - len - 1);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

int
	ft_padding_zero(t_pattern *voyager, t_list *vonc)
{
	int len;

	len = ft_strlen((char*)(vonc->content));
	if (*((char*)(vonc->content)) == '-')
		if ((ft_padding_0_neg(voyager, vonc)))
			return (1);
	if (voyager->conv & (2 << (ft_indice('+', KNOWN_FLAG))))
		if ((ft_padding_0_pos(voyager, vonc, 0)))
			return (1);
	if (!(ft_padding_zero2(voyager, vonc)))
		return (0);
	if (!(ft_padding_zero4(voyager, vonc, len)))
		return (0);
	return (1);
}
