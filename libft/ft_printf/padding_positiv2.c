/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_positiv2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:42:40 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 20:22:44 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int
	ft_padding_positiv6(t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (*((char*)(vonc->content)) != '+')
	{
		if (!(str = ft_strnew(1)))
			return (0);
		str[0] = '+';
		str[1] = '\0';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

inline static int
	ft_padding_positiv3(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width > -1 && voyager->precision == -1
	&& *((char*)vonc->content) != '+')
	{
		if (!(str = ft_strnew(1)))
			return (0);
		if (voyager->precision == -1)
			str[0] = '+';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
		if (!(voyager->conv & (2 << (ft_indice('0', KNOWN_FLAG))))
		&& voyager->field_width - len > 0)
			((char*)(vonc->content))[len - 1] = '\0';
	}
	else if (*((char*)(vonc->content)) != '+'
		&& !(ft_padding_positiv6(vonc)))
		return (0);
	return (1);
}

int
	ft_padding_positiv7(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen(((char*)vonc->content));
	if (voyager->precision == -1 && voyager->field_width <= -1 && len > 0)
	{
		if (!(str = ft_strnew(1)))
			return (0);
		str[0] = '+';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	if (voyager->field_width > -1
	&& ((voyager->conv & (2 << (ft_indice('-', KNOWN_FLAG)))
	|| ((voyager->conv & (2 << (ft_indice('+', KNOWN_FLAG))))
	&& voyager->field_width < (int)ft_strlen((char*)(vonc->content)))))
	&& *((char*)(vonc->content)) != '-' && *((char*)(vonc->content)) != '+')
	{
		if (!(ft_padding_positiv3(voyager, vonc)))
			return (0);
	}
	return (1);
}

int
	ft_padding_positiv5(t_pattern *voyager, t_list *vonc)
{
	int			len;
	char		*str;
	t_ul		type;

	type = ft_type_flag(voyager);
	if (voyager->precision > -1
	&& !(type & (1 << (ft_indice('u', KNOWN_CONV)))))
	{
		len = ft_strlen((char*)(vonc->content));
		if (voyager->precision >= len && *((char*)(vonc->content)) != '-')
		{
			if (!(str = ft_strnew(voyager->precision - len + 1)))
				return (0);
			ft_memset(str, '0', voyager->precision - len + 1);
			str[0] = '+';
			if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
				return (0);
		}
		else if (!(ft_padding_positiv4(voyager, vonc)))
			return (0);
	}
	return (1);
}
