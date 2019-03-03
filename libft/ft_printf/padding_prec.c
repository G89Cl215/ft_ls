/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_prec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:42:51 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 20:20:50 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int						ft_padding_prec3(t_pattern *voyager, t_list *vonc)
{
	int		len;
	char	*str;

	str = NULL;
	len = ft_strlen((char*)(vonc->content));
	if (voyager->precision - len > 0)
	{
		if (!(str = ft_strnew(voyager->precision - len)))
			return (0);
		ft_memset(str, '0', voyager->precision - len);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

inline static int		ft_padding_prec2(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if ((voyager->precision > len && len > 0)
	&& !(voyager->conv & (1 << (TYPE_START + ft_indice('p', KNOWN_CONV)))))
	{
		if (!(str = ft_strnew(voyager->precision - len)))
			return (0);
		ft_memset(str, '0', voyager->precision - len);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	if (voyager->conv & (1 << (TYPE_START + ft_indice('p', KNOWN_CONV)))
	&& (voyager->precision - len + 2 > 0) && voyager->field_width == -1)
	{
		if (!(str = ft_strnew(voyager->precision - len + 2)))
			return (0);
		ft_memset(str, '0', len + 1);
		if (!(ft_strappend((char**)(&(vonc->content)), &str)))
			return (0);
	}
	return (1);
}

int						ft_padding_prec_neg(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	str = NULL;
	len = (int)ft_strlen((char*)(vonc->content));
	if (voyager->precision > -1)
	{
		ft_memmove((char*)(vonc->content), (char*)(vonc->content) + 1, len);
		if (voyager->precision - len >= 0)
		{
			if (!(str = ft_strnew(voyager->precision - len + 2)))
				return (0);
			ft_memset(str, '0', voyager->precision - len + 2);
		}
		else if (voyager->precision < len)
		{
			if (!(str = ft_strnew(len + 1)))
				return (0);
		}
		str[0] = '-';
		if (!(ft_strappend_back(&str, (char**)&(vonc->content))))
			return (0);
	}
	return (1);
}

int						ft_padding_prec(t_pattern *voyager, t_list *vonc)
{
	int		len;

	if (voyager->precision > -1)
	{
		if (*((char*)vonc->content) == '-')
		{
			if (!(ft_padding_prec_neg(voyager, vonc)))
				return (0);
		}
		len = ft_strlen((char*)(vonc->content));
		if (!(ft_padding_prec2(voyager, vonc)))
			return (0);
		if (voyager->precision == 0 && len == 1
		&& *((char*)(vonc->content)) == '0'
		&& !(voyager->conv & (2 << (ft_indice('#', KNOWN_FLAG)))))
			*((char*)vonc->content) = '\0';
	}
	return (1);
}
