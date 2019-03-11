/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:25:19 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 16:12:42 by tgouedar         ###   ########.fr       */
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
#include "ft_ls.h"

void		ft_sortrev_ascii(t_Rlist **lst_start, t_Rlist *to_sort)
{
	char	*name_sort;
	char	*name_cur;
	t_Rlist	*voyager;

	voyager = *lst_start;
	name_cur = ft_get_file(voyager);
	name_sort = ft_get_file(to_sort);
	if (ft_strcmp(name_cur, name_sort) < 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		free(name_sort);
		free(name_cur);
		return ;
	}
	free(name_cur);
	while (voyager->next)
	{
		name_cur = ft_get_file(voyager->next);
		if (ft_strcmp(name_cur, name_sort) > 0)
			voyager = voyager->next;
		else
		{
			free(name_cur);
			break ;
		}
		free(name_cur);
	}
	free(name_sort);
	ft_relink(voyager, to_sort);
}

void		ft_sortins_ascii(t_Rlist **lst_bot, t_Rlist *to_sort)
{
	char	*name_sort;
	char	*name_cur;
	t_Rlist	*voyager;

	voyager = *lst_bot;
	name_cur = ft_get_file(voyager);
	name_sort = ft_get_file(to_sort);
	if (ft_strcmp(name_cur, name_sort) < 0)
	{
		*lst_bot = to_sort;
		to_sort->prev = voyager;
		voyager->next = to_sort;
		free(name_sort);
		free(name_cur);
		return ;
	}
	free(name_cur);
	while (voyager->prev)
	{
		name_cur = ft_get_file(voyager);
		if (ft_strcmp(name_cur, name_sort) > 0)
			voyager = voyager->prev;
		else
		{
			free(name_cur);
			break ;
		}
		free(name_cur);
	}
	free(name_sort);
	ft_revrelink(voyager, to_sort);
}

void		ft_sort_ascii_in_time(t_Rlist **voyager, t_Rlist *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;

	ft_get_stats(to_sort, &sb_sort);
	ft_get_stats(*voyager, &sb);
	while (((*voyager)->next)
	&& ((sb.st_mtimespec).tv_sec == (sb_sort.st_mtimespec).tv_sec)
	&& ((flag * ft_strcmp(((*voyager)->filedata)->d_name,
									(to_sort->filedata)->d_name)) < 0))
	{
		 *voyager = (*voyager)->next;
		ft_get_stats(*voyager, &sb);
	}
}

void		ft_sortins_time(t_Rlist **lst_start, t_Rlist *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;
	t_Rlist			*voyager;

	ft_get_stats(to_sort, &sb_sort);
	ft_get_stats(*lst_start, &sb);
	voyager = *lst_start;
	if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) < 0
	&& ((flag * ft_strcmp((voyager->filedata)->d_name,
									(to_sort->filedata)->d_name)) > 0))
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		voyager->prev = to_sort;
		return ;
	}
	while ((voyager->next)
	&& (flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec) > 0))
	{
		voyager = voyager->next;
		ft_get_stats(voyager, &sb);
	}
	ft_sort_ascii_in_time(&voyager, to_sort, flag);
	if (voyager == *lst_start)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		voyager->prev = to_sort;
		return ;
	}
	ft_relink(voyager->prev, to_sort);
}


/*void		ft_parse_sort_time(t_Rlist **lst_start, t_Rlist *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;
	t_Rlist			*voyager;
	char			*to_sort_name;
	char			*cmp_name;

	ft_get_stats(to_sort, &sb_sort);
	ft_get_stats(*lst_start, &sb);
	voyager = *lst_start;
	if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) > 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		ft_get_stats(voyager->next, &sb);
		if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) < 0)
			voyager = voyager->next;
		else
			break ;
	}
	to_sort_name = ft_get_file(to_sort);
	cmp_name = ft_get_file(voyager);
	while ((voyager->next)
	&& ((sb.st_mtimespec).tv_sec == (sb_sort.st_mtimespec).tv_sec)
	&& ((flag * ft_strcmp(cmp_name, to_sort_name)) > 0))
	{
		free(cmp_name);
		voyager = voyager->next;
		cmp_name = ft_get_file(voyager);
		ft_get_stats(voyager->next, &sb);
	}
	to_sort->next = voyager->next;
	voyager->next = to_sort;
//	ft_relink(voyager, to_sort);
	free(to_sort_name);
	free(cmp_name);
}*/

void		ft_sortins(t_Rlist *new_nod, t_Rlist **dir_end, t_options option)
{
//	ft_putendl((new_nod->filedata)->d_name);
	if (!(*dir_end))
		*dir_end = new_nod;
	else if ((option.r))
		(option.t) ? ft_sortins_time(dir_end, new_nod, -1)
			: ft_sortrev_ascii(dir_end, new_nod);
	else if (option.t)
	   ft_sortins_time(dir_end, new_nod, 1);
	else
	{
		ft_sortins_ascii(dir_end, new_nod);
		while ((*dir_end)->next)
			*dir_end = (*dir_end)->next;
	}
}
