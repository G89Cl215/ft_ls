/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_stock_ls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:27:06 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/19 23:47:12 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_ls.h"

static void		ft_finish_stock(t_reclist **dir_list, t_options option)
{
	if (option.t)
		ft_recmerge_sort(dir_list, &ft_reclist_time_cmp, option.r ? -1 : 1);
	else if (!(option.r))
	{
		while ((*dir_list)->prev)
			*dir_list = (*dir_list)->prev;
	}
}

t_reclist		*ft_read_stock_dir(char *dir_name, t_options option)
{
	t_reclist		*dir_list;
	t_reclist		*to_sort;
	DIR				*dirhandle;
	struct dirent	*filedata;

	filedata = NULL;
	to_sort = NULL;
	dir_list = NULL;
	if (!(dirhandle = opendir(dir_name)))
	{
		perror("readdir");
		return (NULL);
	}
	while ((filedata = readdir(dirhandle)))
	{
		if (!(to_sort = ft_newdir_nod(dir_name, filedata)))
		{
			closedir(dirhandle);
			return (NULL);
		}
		ft_sortins(to_sort, &dir_list, option);
	}
	ft_finish_stock(&dir_list, option);
	closedir(dirhandle);
	return (dir_list);
}
