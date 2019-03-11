/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:25:19 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 19:43:11 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "ls_list.h"
#include "../ft_ls.h"

static void		ft_sortins_ascii(t_flist **lst_start, t_flist *to_sort, int flag)
{
	t_flist		*voyager;

	voyager = *lst_start;
	if ((flag * ft_strcmp(voyager->file_name, to_sort->file_name)) > 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		if ((flag * ft_strcmp(voyager->file_name,
									to_sort->file_name)) < 0)
			voyager = voyager->next;
		else
			break ;
	}
	to_sort->next = voyager->next;
	voyager->next = to_sort;
}

static void		ft_sort_ascii_in_time(t_flist **voyager, t_flist *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;

	ft_get_file_stat(to_sort->file_name, &sb_sort);
	ft_get_file_stat((*voyager)->file_name, &sb);
	while (((*voyager)->next)
	&& ((sb.st_mtimespec).tv_sec == (sb_sort.st_mtimespec).tv_sec)
	&& ((flag * ft_strcmp((*voyager)->file_name, to_sort->file_name)) < 0))
	{
		*voyager = (*voyager)->next;
		ft_get_file_stat((*voyager)->file_name, &sb);
	}
}

static void		ft_sortins_time(t_flist **lst_start, t_flist *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;
	t_flist			*voyager;

	voyager = *lst_start;
	ft_get_file_stat(to_sort->file_name, &sb_sort);
	ft_get_file_stat(voyager->file_name, &sb);
	if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) < 0
	&& ((flag * ft_strcmp(voyager->file_name, to_sort->file_name)) > 0))
	{
		ft_flistadd(lst_start, to_sort);
		return ;
	}
	while ((voyager->next)
	&& (flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec) > 0))
	{
		voyager = voyager->next;
		ft_get_file_stat(voyager->file_name, &sb);
	}
	ft_sort_ascii_in_time(&voyager, to_sort, flag);
	if (voyager == *lst_start)
		ft_flistadd(lst_start, to_sort);
	to_sort->next = voyager->next;
	voyager->next = to_sort;
}

void		ft_sortparse(t_flist *new_nod, t_flist **dir_list, t_options option)
{
	int		flag;

	flag = (option.r) ? -1 : 1;
	if (!(*dir_list))
		*dir_list = new_nod;
	else
		(option.t) ? ft_sortins_time(dir_list, new_nod, flag)
					: ft_sortins_ascii(dir_list, new_nod, flag);
}
