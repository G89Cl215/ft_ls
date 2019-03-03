/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/09 15:22:28 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/26 15:32:22 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include "ft_printf.h"
#include <stdarg.h>
#include <stdio.h>

int		ft_printf(const char *restrict format, ...)
{
	va_list		ap;
	char		*str;
	t_pattern	**pattern;
	t_list		**buff;
	t_list		**conv;

	if (!(str = ft_strdup(format)))
		return (-1);
	if (!(pattern = (t_pattern**)malloc(sizeof(t_pattern*)))
	|| !(buff = (t_list**)malloc(sizeof(t_list*))))
		return (ft_free_mem(NULL, NULL, pattern, &str));
	*pattern = NULL;
	*buff = NULL;
	if ((ft_pattern_detect(str, buff, pattern)))
	{
		va_start(ap, format);
		if (!(conv = ft_conv(pattern, &ap, buff)) && (*pattern))
		{
			va_end(ap);
			return (ft_free_mem(conv, buff, pattern, NULL));
		}
		ft_free_mem(NULL, NULL, pattern, &str);
		return (ft_concat_buffer(buff, conv));
	}
	return (ft_free_mem(buff, NULL, pattern, &str));
}
