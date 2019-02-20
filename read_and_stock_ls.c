/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_stock_ls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:27:06 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/20 20:08:44 by tgouedar         ###   ########.fr       */
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

void		ft_sortins_ascii(t_flist **lst_start, t_flist *to_sort, int flag)
{
	char	*name_sort;
	char	*name_cur;
	t_flist	*voyager;

	voyager = *lst_start;
	name_sort = (to_sort->filedata)->d_name;
	name_cur = (voyager->filedata)->d_name;
	if ((flag * ft_strcmp(name_cur, name_sort)) >= 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		name_cur = ((voyager->next)->filedata)->d_name;
		if ((flag * ft_strcmp(name_cur, name_sort)) < 0)
			voyager = voyager->next;
		else
			break ;
	}
	to_sort->next = voyager->next;
	voyager->next = to_sort;
}

void		ft_sortins_time(t_flist **lst_start, t_flist *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;
	t_flist			*voyager;

	ft_get_stats(to_sort, &sb_sort);
	ft_get_stats(*lst_start, &sb);
	voyager = *lst_start;
	if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) < 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		ft_get_stats(voyager->next, &sb);
		if ((flag * ((sb.st_mtimespec).tv_sec
						- (sb_sort.st_mtimespec).tv_sec)) >= 0)
			voyager = voyager->next;
		else
			break ;
	}
	while ((voyager->next)
	&& ((sb.st_mtimespec).tv_sec == (sb_sort.st_mtimespec).tv_sec)
	&& ((flag * ft_strcmp((voyager->filedata)->d_name,
									(to_sort->filedata)->d_name)) < 0))
	{
		ft_get_stats(voyager->next, &sb);
		voyager = voyager->next;
	}
	to_sort->next = voyager->next;
	voyager->next = to_sort;
}

void		ft_sortins(t_flist *new_nod, t_flist **dir_list, t_options option)
{
	int		flag;

	flag = (option.r) ? -1 : 1;
	if (!(*dir_list))
		*dir_list = new_nod;
	else
		(option.t) ? ft_sortins_time(dir_list, new_nod, flag)
					: ft_sortins_ascii(dir_list, new_nod, flag);
}

t_flist		*ft_read_stock_dir(char *dir_name, t_options option)
{
	t_flist			*dir_list;
	t_flist			*to_sort;
	DIR				*dirhandle;
	struct dirent	*filedata;

	dirhandle = NULL;
	filedata = NULL;
	to_sort = NULL;
	dir_list = NULL;
	if (!(dirhandle = opendir(dir_name)))
		return (NULL);
	while ((filedata = readdir(dirhandle)))
	{
		if (!(to_sort = ft_create_new_nod(dir_name, filedata)))
			return (NULL);
		ft_sortins(to_sort, &dir_list, option);
	}
	closedir(dirhandle);
	return (dir_list);
}
