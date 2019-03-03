/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   g_convtab.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/13 12:57:17 by baavril           #+#    #+#             */
/*   Updated: 2019/02/01 19:43:20 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef G_CONVTAB_H
# define G_CONVTAB_H

# include "ft_printf.h"

t_conv			g_convtab[] =
{
	{(1), &ft_conv_binary},
	{(1 << 1), &ft_conv_char},
	{(1 << 2), &ft_conv_int},
	{(1 << 3), &ft_conv_scient},
	{(1 << 4), &ft_conv_float},
	{(1 << 5), &ft_conv_int},
	{(1 << 6), &ft_crise_char},
	{(1 << 7), &ft_conv_octal},
	{(1 << 8), &ft_conv_addr},
	{(1 << 9), &ft_conv_str},
	{(1 << 10), &ft_conv_uint},
	{(1 << 11), &ft_conv_hex},
	{(1 << 12), &ft_conv_unichar},
	{(1 << 13), &ft_conv_int},
	{(1 << 14), &ft_conv_scient},
	{(1 << 15), &ft_conv_octal},
	{(1 << 16), &ft_conv_unistring},
	{(1 << 17), &ft_conv_ulint},
	{(1 << 18), &ft_conv_hex},
	{(1 << 19), &ft_conv_float},
	{(1 << 20), &ft_conv_percent}
};

#endif
