/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_from_pattern.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 14:44:50 by tgouedar          #+#    #+#             */
/*   Updated: 2019/01/30 13:34:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

t_ul	ft_int_flag(void)
{
	t_ul	j;

	j = TYPE_START - LMOD_START;
	return ((t_ul)1 << (j + ft_indice('i', KNOWN_CONV))
			| ((t_ul)1 << (j + ft_indice('d', KNOWN_CONV)))
			| ((t_ul)1 << (j + ft_indice('D', KNOWN_CONV))));
}

t_ul	ft_lmod_flag(t_pattern *pattern)
{
	return (((((t_ul)1 << TYPE_START) - 1) & pattern->conv) >> LMOD_START);
}

t_ul	ft_type_flag(t_pattern *pattern)
{
	return ((~((t_ul)0) & pattern->conv) >> TYPE_START);
}

t_ul	ft_type_flag_pos(t_pattern *pattern)
{
	return ((~((t_ul)0) & pattern->conv) >> LMOD_START);
}

t_ul	ft_t_ul_flag(t_ul conv)
{
	return (((((t_ul)1 << TYPE_START) - 1) & conv) >> LMOD_START);
}
