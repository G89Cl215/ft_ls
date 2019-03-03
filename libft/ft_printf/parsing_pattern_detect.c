/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_pattern_detect.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 16:13:38 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/09 15:54:25 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int
	ft_translate_int(char **str)
{
	int		i;

	i = -1;
	if (ft_isdigit(**str))
		i = ft_atoi(*str);
	while (**str && ft_isdigit(**str))
		(*str)++;
	return (i);
}

/*
** 	Cette fonction traduit le pattern et renvoie 0 s'il est invalide, 1 s'il
**	est valide et non positionnel et 2 s'il est positionnel.
*/

inline static int
	ft_pattern_pos(char **str, t_pattern *pattern, int i)
{
	size_t	j;

	j = 2;
	if ((**str == '$' && (*str)++) || ((pattern->field_width = i) && 0))
	{
		pattern->conv++;
		pattern->nbr = i;
		pattern->conv &= ~(j << ft_indice('0', KNOWN_FLAG));
		ft_translate_flag(str, pattern);
		if (!(ft_translate_f_w(str, pattern)))
			return (0);
	}
	return (1);
}

inline static int
	ft_pattern_translate(char **str, t_pattern *pattern)
{
	int		i;

	if (**str == '0' && (*str)++)
		pattern->conv = 2 << ft_indice('0', KNOWN_FLAG);
	if (ft_isdigit(**str) && (i = ft_translate_int(str)))
	{
		if (!(ft_pattern_pos(str, pattern, i)))
			return (0);
	}
	else
	{
		ft_translate_flag(str, pattern);
		if (!(ft_translate_f_w(str, pattern)))
			return (0);
	}
	if (!(ft_translate_precision(str, pattern))
	|| !(ft_translate_lmod(str, pattern)))
		return (0);
	return ((ft_translate_type(str, pattern)) ? (1 + (pattern->conv % 2)) : 0);
}

int
	ft_stock_string(t_list **buff, char *str, size_t len)
{
	t_list	*new_back;

	if (len)
	{
		if (!(new_back = ft_lstnew(str, len)))
			return (0);
	}
	else
	{
		if (!(new_back = ft_lstnew(NULL, 0)))
			return (0);
	}
	ft_lstadd_back(buff, new_back);
	return (1);
}

/*
**	Cette fonction decoupe les chaines entre deux patterns et les stocke dans
**	une liste chainee, elle envoie ensuite les patterns en traduction.
**	NB: un maillon vide sera stocke en cas 2 patterns se suivant immediatement,
**	ou de pattern directement en debut ou fin de chaine.
*/

int
	ft_pattern_detect(char *str, t_list **buff, t_pattern **pattern_list)
{
	size_t		i;
	size_t		j;
	int			flag;
	t_pattern	*pattern;

	flag = 3;
	i = 0;
	while ((j = ft_strcspn(str + i, "%")) != ft_strlen(str + i))
	{
		if (!(pattern = ft_new_pattern(pattern_list)))
			return (0);
		if (!(ft_stock_string(buff, str, i + j)))
			return (0);
		ft_memmove(str, str + i + j + 1, ft_strlen(str + i + j));
		if (!(i = ft_pattern_translate(&str, pattern)) || !(flag &= i))
			return (ft_parse_error(flag, NULL, NULL, NULL));
		i = 0;
	}
	return (ft_stock_string(buff, str, i + j));
}
