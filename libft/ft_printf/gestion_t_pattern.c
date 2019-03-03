/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gestion_t_pattern.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/12 15:25:27 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/02 22:13:41 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			ft_free_pattern(t_pattern **pattern)
{
	t_pattern	*voyager;

	if (!(pattern))
		return (0);
	voyager = *pattern;
	while (voyager)
	{
		voyager = voyager->next;
		free(*pattern);
		*pattern = voyager;
	}
	return (1);
}

t_pattern	*ft_new_pattern(t_pattern **pattern_list)
{
	t_pattern	*new;
	t_pattern	*voyager;

	if (!(new = (t_pattern*)malloc(sizeof(t_pattern))))
		return (NULL);
	new->conv = 0;
	new->field_width = -1;
	new->precision = -1;
	new->nbr = 0;
	new->next = NULL;
	if (!(*pattern_list))
		*pattern_list = new;
	else
	{
		voyager = *pattern_list;
		while (voyager->next)
			voyager = voyager->next;
		voyager->next = new;
	}
	return (new);
}
