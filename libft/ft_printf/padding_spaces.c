/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_spaces.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:43:12 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/09 14:46:24 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static int		ft_padding_flag_space2(t_pattern *voyager, t_list *vonc)
{
	char		*str;

	str = NULL;
	if (!(str = ft_strnew(1)))
		return (0);
	if (voyager->precision != -1)
	{
		if (!(ft_padding_prec(voyager, vonc)))
			return (0);
	}
	if (!(*((char*)(vonc->content)) == '-'))
	{
		str[0] = ' ';
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	else
		ft_strdel(&str);
	return (1);
}

int						ft_padding_flag_space(t_pattern *voyager, t_list *vonc)
{
	t_ul		type;

	type = ft_type_flag(voyager);
	if ((voyager->field_width == -1
	|| ((voyager->field_width - (int)ft_strlen(vonc->content) <= 0)
	|| ((voyager->field_width - (int)ft_strlen(vonc->content) >= 0))))
	&& !(voyager->conv & ((size_t)2 << (ft_indice('+', KNOWN_FLAG))))
	&& !(type & ((size_t)1 << (ft_indice('u', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('x', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('X', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('o', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('O', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('p', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('%', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('c', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('C', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('s', KNOWN_CONV))))
	&& !(type & ((size_t)1 << (ft_indice('S', KNOWN_CONV)))))
		if (!(ft_padding_flag_space2(voyager, vonc)))
			return (0);
	return (1);
}

int						ft_padding_spaces(t_pattern *voyager, t_list *vonc)
{
	char	*str;
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->field_width - len > 0)
	{
		if (!(str = ft_strnew(voyager->field_width - len)))
			return (0);
		ft_memset(str, ' ', voyager->field_width - len);
		if (!(ft_strappend_back(&str, (char**)(&(vonc->content)))))
			return (0);
	}
	return (1);
}

int						ft_padding_str(t_pattern *voyager, t_list *vonc)
{
	int		len;

	len = ft_strlen((char*)(vonc->content));
	if (voyager->precision != -1)
	{
		if (len - voyager->precision > 0)
			((char*)(vonc->content))[voyager->precision] = '\0';
	}
	return (1);
}
