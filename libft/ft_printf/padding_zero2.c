/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_zero2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 19:48:03 by baavril           #+#    #+#             */
/*   Updated: 2019/02/07 19:49:18 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_padding_0_pos(t_pattern *voyager, t_list *vonc, int len)
{
	char	*str;

	str = NULL;
	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width != -1)
	{
		if (voyager->field_width > len)
		{
			if (!(str = ft_strnew(voyager->field_width - len)))
				return (0);
			ft_memset(str, '0', voyager->field_width - len);
			str[0] = '+';
			if (!(ft_strappend_back(&str, (char**)&(vonc->content))))
				return (0);
		}
		else if (voyager->field_width < len)
		{
			if (!(str = ft_strnew(len + 1)))
				return (0);
			str[0] = '+';
			if (!(ft_strappend_back(&str, (char**)&(vonc->content))))
				return (0);
		}
	}
	return (1);
}

int		ft_padding_0_neg(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width != -1 && voyager->field_width - len > 0)
	{
		ft_memmove((char*)(vonc->content), (char*)(vonc->content) + 1, len);
		if (voyager->field_width - len > 0)
		{
			if (!(str = ft_strnew(voyager->field_width - len + 1)))
				return (0);
			ft_memset(str, '0', voyager->field_width - len + 1);
			str[0] = '-';
			if (!(ft_strappend_back(&str, (char**)&(vonc->content))))
				return (0);
		}
	}
	return (1);
}
