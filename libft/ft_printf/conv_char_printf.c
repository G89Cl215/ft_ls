/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_char_printf.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:05:41 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/02 15:49:12 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "float_conv_tools.h"

char	*ft_conv_char(va_list *ap, t_ul type, t_pattern *conv)
{
	char	*str;
	char	c;

	if (type & (1 << (ft_indice('l', KNOWN_LMOD) + LMOD_START)))
		return (ft_conv_unichar(ap, type, conv));
	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	c = (char)va_arg(*ap, int);
	if (!(str = ft_strnew(1)))
		return (NULL);
	str[0] = c;
	return (str);
}

char	*ft_conv_str(va_list *ap, t_ul type, t_pattern *conv)
{
	char	*str;

	if (type & (1 << (ft_indice('l', KNOWN_LMOD) + LMOD_START)))
		return (ft_conv_unistring(ap, type, conv));
	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	str = va_arg(*ap, char*);
	if (!str)
		return (ft_strdup("(null)"));
	return (ft_strdup(str));
}

char	*ft_conv_percent(va_list *ap, t_ul type, t_pattern *conv)
{
	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	(void)type;
	(void)conv;
	return (ft_strdup("%"));
}
