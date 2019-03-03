/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_unicode_printf.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 15:05:28 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/10 18:30:22 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

inline static void
	ft_translate_unichar(union u_unicode *un)
{
	if (un->i >= 128)
	{
		if (un->i >= 4096)
		{
			if (un->i >= 65536)
			{
				(un->str)[3] = 240 | ((1835008 & un->i) >> 17);
				(un->str)[2] = ((un->str)[2] & 3) << 4;
				(un->str)[2] |= ((un->str[1] & 60) >> 2) | 128;
			}
			else
				(un->str)[2] = 224 | ((61440 & un->i) >> 12);
			(un->str)[1] = ((un->str)[1] & 15) << 2;
			(un->str)[1] |= 128 | ((un->str)[0] & 192) >> 6;
		}
		else
			(un->str)[1] = 192 | ((4032 & un->i) >> 6);
		(un->str)[0] = ((un->str)[0] & 191) | 128;
	}
}

char
	*ft_conv_unichar(va_list *ap, t_ul type, t_pattern *conv)
{
	union u_unicode	un;
	char			*str;

	(void)conv;
	(void)type;
	un.i = va_arg(*ap, wchar_t);
	ft_translate_unichar(&un);
	if (!(str = ft_strnew(4)))
		return (NULL);
	ft_memmove(str, un.str, 4);
	return (str);
}

inline static char
	*ft_translate_unistring(wchar_t *uni)
{
	union u_unicode	un;
	char			*str;
	int				i;

	i = 0;
	while (uni[i])
		i++;
	if (!i)
		return (ft_strdup("\0\0\0\0"));
	if (!(str = ft_strnew((i + 1) * 4)))
		return (NULL);
	i = 0;
	while (*uni)
	{
		un.i = *uni;
		ft_translate_unichar(&un);
		ft_memmove(str + 4 * i++, (char*)un.str, 4);
		uni++;
	}
	ft_memcpy(str + 4 * i++, "\0\0\0\0", 4);
	return (str);
}

char
	*ft_conv_unistring(va_list *ap, t_ul type, t_pattern *conv)
{
	wchar_t			*uni;
	char			*str;

	(void)conv;
	(void)type;
	uni = va_arg(*ap, wchar_t*);
	if (!uni)
	{
		if (!(str = (char*)malloc(28 * sizeof(char))))
			return (NULL);
		ft_memcpy(str,
					"(\0\0\0n\0\0\0u\0\0\0l\0\0\0l\0\0\0)\0\0\0\0\0\0\0", 28);
		return (str);
	}
	return (ft_translate_unistring(uni));
}
