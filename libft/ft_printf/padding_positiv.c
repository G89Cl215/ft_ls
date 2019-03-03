/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_positiv.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:42:28 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 18:18:03 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int
	ft_padding_positiv8(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width != -1 && *((char*)(vonc->content)) != '+')
	{
		if (!(str = ft_strnew(1)))
			return (0);
		if (voyager->precision == -1)
			str[0] = '+';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

int
	ft_padding_positiv4(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->precision != -1 && *((char*)(vonc->content)) != '-'
	&& *((char*)(vonc->content)) != '+')
	{
		if (!(str = ft_strnew(1)))
			return (0);
		str[0] = '+';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

inline static int
	ft_padding_positiv2(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width - len > 0)
	{
		if (!(str = ft_strnew(voyager->field_width - len)))
			return (0);
		ft_memset(str, ' ', voyager->field_width - len);
		if (voyager->precision == -1 && *((char*)(vonc->content)) != '-')
			str[voyager->field_width - len - 1] = '+';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	if (!(ft_padding_positiv7(voyager, vonc)))
		return (0);
	return (1);
}

inline static int
	ft_padding_positiv_bis(t_pattern *voyager, t_list *vonc, int len)
{
	if (!(ft_padding_positiv5(voyager, vonc)))
		return (0);
	if (voyager->field_width > -1 || (voyager->precision == -1
	&& voyager->field_width <= -1 && *((char*)(vonc->content)) != '-'
	&& !(voyager->conv
	& ((size_t)1 << (TYPE_START + ft_indice('u', KNOWN_CONV))))))
		if (!(ft_padding_positiv2(voyager, vonc)))
			return (0);
	if (voyager->conv & (1 << (ft_indice('+', KNOWN_FLAG) + 1))
	&& *((char*)(vonc->content)) != '-'
	&& *(char*)(vonc->content) != '+' && (voyager->field_width == -1
	|| voyager->field_width - len == 0))
		if (!(ft_padding_positiv8(voyager, vonc)))
			return (0);
	return (1);
}

int
	ft_padding_positiv(t_pattern *voyager, t_list *vonc)
{
	size_t	i;
	int		len;

	i = 1;
	len = ft_strlen((char*)(vonc->content));
	if (!(voyager->conv & (i << (TYPE_START + ft_indice('o', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('s', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('%', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('x', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('X', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('p', KNOWN_CONV))))
	&& !(voyager->conv & (i << (TYPE_START + ft_indice('O', KNOWN_CONV)))))
	{
		if (!(ft_padding_positiv_bis(voyager, vonc, len)))
			return (0);
	}
	return (1);
}
