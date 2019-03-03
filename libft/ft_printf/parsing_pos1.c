/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pos1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:46:18 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 17:05:29 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdarg.h>

/*
** Fonction qui permet d'organiser les va_args en fonction des ints adequats
*/

inline static t_list
	**ft_positional_conv(t_pattern **pattern, t_list **tmp)
{
	t_pattern	*voyager;
	t_list		**conv;
	t_list		*bus;
	int			i;

	if (!(conv = (t_list**)malloc(sizeof(t_list*))))
		return (NULL);
	voyager = *pattern;
	*conv = NULL;
	while (voyager)
	{
		bus = *tmp;
		i = 1;
		while (i++ < voyager->nbr)
			bus = bus->next;
		if (!(ft_stock_string(conv, bus->content, bus->content_size)))
			return (NULL);
		voyager = voyager->next;
	}
	ft_lstfree(tmp);
	free(tmp);
	return (conv);
}

/*
**	Lorsque le flag positionnel est active, apres le parsing,
**	on verifie que tous les arguments invoques sont atteignables
**	dans notre va_list
*/

inline static int
	ft_verif_nbr_arg(t_pattern **pattern, int min, int max)
{
	t_pattern	*voyager;
	size_t		type;

	voyager = *pattern;
	while (voyager)
	{
		type = voyager->conv;
		if (voyager->nbr > max)
			max = voyager->nbr;
		if ((type & (1 << STAR_PR)) && voyager->precision > max)
			max = voyager->precision;
		if ((type & (1 << STAR_FW)) && voyager->field_width > max)
			max = voyager->field_width;
		if (voyager->nbr == min + 1
		|| (voyager->precision == min + 1 && (type & (1 << STAR_PR)))
		|| (voyager->field_width == min + 1 && (type & (1 << STAR_FW))))
			return (ft_verif_nbr_arg(pattern, min + 1, max));
		voyager = voyager->next;
	}
	return ((min == max) ? max : 0);
}

inline static int
	ft_check_conv_in_pattern(int nbr, size_t *type, t_pattern *voyager)
{
	size_t	i;

	i = 1;
	if (voyager->nbr == nbr)
	{
		if (!(*type))
			*type = ft_type_flag_pos(voyager);
		else if (!(ft_type_flag_pos(voyager) & *type)
		|| !((ft_int_flag() & *type)
		&& (ft_int_flag() & ft_type_flag_pos(voyager))
		&& !(ft_lmod_flag(voyager)
			^ (*type & ((i << ft_strlen(KNOWN_LMOD)) - 1)))))
			return (0);
	}
	if ((voyager->precision == nbr && (voyager->conv & (1 << STAR_PR)))
	|| (voyager->field_width == nbr && (voyager->conv & (1 << STAR_FW))))
	{
		if (!(*type))
			*type = i << (ft_indice('d', KNOWN_CONV) + TYPE_START - LMOD_START);
		else if (((ft_int_flag() ^ *type) > ft_int_flag())
		|| (*type & ((i << ft_strlen(KNOWN_LMOD)) - 1)))
			return (0);
	}
	return (1);
}

/*
** On verifie ensuite que le cast de chaque parametre ne soit pas conflictuel
** Si ca n'est pas le cas, on cree la liste chainee des params castes dans
** le type adequat et on remplace les precisions/field_width par leurs valeurs
*/

inline static int
	ft_verif_type(int i, t_pattern **pattern, t_list **tmp, va_list *ap)
{
	t_pattern	*voyager;
	size_t		type;
	size_t		j;

	j = 1;
	type = 0;
	voyager = *pattern;
	while (voyager)
	{
		if (!(ft_check_conv_in_pattern(i, &type, voyager)))
			return (ft_parse_error(2, tmp, NULL, NULL));
		voyager = voyager->next;
	}
	if ((ft_int_flag() & type)
	&& !(type & ((j << ft_strlen(KNOWN_LMOD)) - 1)))
	{
		if (!(ft_pos_pr_fw(i, pattern, tmp, ap)))
			return (0);
	}
	else if (!(ft_ezequiel(*pattern, tmp, ap, 1)))
		return (0);
	return (1);
}

/*
**	Detecte si positionnal mod est actif - si oui go parse -
**	si non go liste de conversion
*/

t_list
	**ft_positional_mod(t_pattern **pattern, va_list *ap)
{
	t_pattern	*voyager;
	t_list		**tmp;
	int			i;
	int			max;

	voyager = *pattern;
	if (!(tmp = (t_list**)malloc(sizeof(t_list*))))
		return (NULL);
	*tmp = NULL;
	if ((max = ft_verif_nbr_arg(pattern, 0, 0)))
	{
		i = 0;
		while (i++ < max)
		{
			if (!(ft_verif_type(i, pattern, tmp, ap)))
				return (NULL);
		}
		return (ft_positional_conv(pattern, tmp));
	}
	else
		ft_parse_error(1, tmp, NULL, NULL);
	return (NULL);
}
