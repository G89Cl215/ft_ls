/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:25:19 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:50:46 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/option.h"
#include "list_lib/ls_list.h"
#include "ft_ls.h"

void	ft_sortrev_ascii(t_reclist **lst_start, t_reclist *to_sort)
{
	t_reclist	*voyager;

	voyager = *lst_start;
	if (ft_strcmp(voyager->file_name, to_sort->file_name) < 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		if (ft_strcmp(voyager->file_name, to_sort->file_name) > 0)
			voyager = voyager->next;
		else
			break ;
	}
	ft_relink(voyager, to_sort);
}

void	ft_sortins_ascii(t_reclist **lst_bot, t_reclist *to_sort)
{
	t_reclist	*voyager;

	voyager = *lst_bot;
	if (ft_strcmp(voyager->file_name, to_sort->file_name) < 0)
	{
		*lst_bot = to_sort;
		to_sort->prev = voyager;
		voyager->next = to_sort;
		return ;
	}
	while (voyager->prev)
	{
		if (ft_strcmp((voyager->prev)->file_name, to_sort->file_name) > 0)
			voyager = voyager->prev;
		else
			break ;
	}
	ft_revrelink(voyager, to_sort);
}

void	ft_sortins(t_reclist *new_nod, t_reclist **dir_end, t_options option)
{
	if (!(*dir_end))
		*dir_end = new_nod;
	else if ((option.t))
		ft_reclistadd(dir_end, new_nod);
	else if ((option.r))
		ft_sortrev_ascii(dir_end, new_nod);
	else
	{
		ft_sortins_ascii(dir_end, new_nod);
		while ((*dir_end)->next)
			*dir_end = (*dir_end)->next;
	}
}
