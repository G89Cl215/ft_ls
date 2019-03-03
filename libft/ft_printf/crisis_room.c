/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crisis_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/31 18:17:28 by baavril           #+#    #+#             */
/*   Updated: 2019/02/03 01:12:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		ft_free_mem(t_list **buff, t_list **conv, t_pattern **pattern,
																char **str)
{
	if (pattern)
	{
		ft_free_pattern(pattern);
		free(pattern);
	}
	if (buff)
	{
		ft_lstfree(buff);
		free(buff);
	}
	if (conv)
	{
		ft_lstfree(conv);
		free(conv);
	}
	ft_strdel(str);
	return (-1);
}

int		ft_parse_error(int flag, t_list **buff, t_list **conv,
															t_pattern **pattern)
{
	ft_free_mem(buff, conv, pattern, NULL);
	if (flag == 0)
		ft_putendl("error : mix of postionnal & non-positionnal flags.");
	if (flag == 1)
		ft_putendl("error : wrong call of arguments.");
	if (flag == 2)
		ft_putendl("error : conflicting conversion types.");
	return (0);
}

char	*ft_crise_char(va_list *ap, t_ul type, t_pattern *conv)
{
	char	*str;

	if (conv)
	{
		if (type & ((t_ul)1 << STAR_FW))
			conv->field_width = va_arg(*ap, int);
		if (type & ((t_ul)1 << STAR_PR))
			conv->precision = va_arg(*ap, int);
	}
	if (!(str = ft_strnew(1)))
		return (NULL);
	str[0] = (char)(conv->nbr);
	return (str);
}
