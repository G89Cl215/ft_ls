/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_int_printf.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:39:24 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 15:38:10 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static t_ull		ft_num_conv(va_list *ap, int flag)
{
	t_ull	i;

	i = 0;
	if (!flag)
		i = va_arg(*ap, int);
	else if (flag == 2)
		i = (char)va_arg(*ap, int);
	else if (flag == 1)
		i = (short)va_arg(*ap, int);
	else if (flag == 32)
		i = (intmax_t)va_arg(*ap, intmax_t);
	else if (flag == 4)
		i = va_arg(*ap, unsigned long);
	else if (flag == 64)
		i = (ssize_t)va_arg(*ap, ssize_t);
	else if (flag == 8)
		i = (uintmax_t)va_arg(*ap, unsigned long long);
	return (i);
}

char					*ft_conv_int(va_list *ap, t_ul type, t_pattern *conv)
{
	t_ull	i;

	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	if (!(type & ((t_ul)1 << (TYPE_START + ft_indice('D', KNOWN_CONV)))))
		i = ft_num_conv(ap, ft_t_ul_flag(type));
	else
		i = (unsigned long)va_arg(*ap, unsigned long);
	if (ft_t_ul_flag(type) < 4 || (intmax_t)i < 0)
		return (ft_itoa(i));
	return (ft_unsigned_itoa_base(i, "0123456789"));
}

char					*ft_conv_ulint(va_list *ap, t_ul type, t_pattern *conv)
{
	t_ull	i;

	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	i = (unsigned long)va_arg(*ap, unsigned long);
	return (ft_unsigned_itoa_base(i, "0123456789"));
}

char					*ft_conv_uint(va_list *ap, t_ul type, t_pattern *conv)
{
	t_ull	i;

	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	i = ft_unsigned_num_conv(ap, ft_lmod_flag(conv));
	return (ft_unsigned_itoa_base(i, "0123456789"));
}
