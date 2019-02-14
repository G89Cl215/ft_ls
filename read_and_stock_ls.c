/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_stock_ls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:27:06 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/14 13:26:31 by tgouedar         ###   ########.fr       */
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

void		ft_sortins_ascii(t_list **lst_start, t_list *to_sort, int flag)
{
	char	*name_sort;
	char	*name_cur;
	t_list	*voyager;

	voyager = *lst_start;
	name_sort = ((struct dirent*)(to_sort->content))->d_name;
	name_cur = ((struct dirent*)(voyager->content))->d_name;
	if ((flag * ft_strcmp(name_cur, name_sort)) >= 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		name_cur = ((struct dirent*)((voyager->next)->content))->d_name;
		if ((flag * ft_strcmp(name_cur, name_sort)) < 0)
			voyager = voyager->next;
		else
			break ;
	}
	to_sort->next = voyager->next;
	voyager->next = to_sort;
}

void		ft_sortins_time(t_list **lst_start, t_list *to_sort, int flag)
{
	struct stat		sb_sort;
	struct stat		sb;
	t_list			*voyager;

	if (stat(((struct dirent*)(to_sort->content))->d_name, &sb_sort) == -1
	|| stat(((struct dirent*)((*lst_start)->content))->d_name, &sb) == -1)
	{
		perror("stat");
		exit(EXIT_SUCCESS);
	}
	voyager = *lst_start;
	if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) < 0)
	{
		*lst_start = to_sort;
		to_sort->next = voyager;
		return ;
	}
	while (voyager->next)
	{
		if (stat(((struct dirent*)((voyager->next)->content))->d_name, &sb) == -1)
		{
			perror("stat");
			exit(EXIT_SUCCESS);
		}
		if ((flag * ((sb.st_mtimespec).tv_sec - (sb_sort.st_mtimespec).tv_sec)) >= 0)
			voyager = voyager->next;
		else
			break ;
	}
	while ((voyager->next)
	&& ((sb.st_mtimespec).tv_sec == (sb_sort.st_mtimespec).tv_sec)
	&& ((flag * ft_strcmp(((struct dirent*)(voyager->content))->d_name,
					((struct dirent*)(to_sort->content))->d_name)) < 0))
	{
		if (stat(((struct dirent*)((voyager->next)->content))->d_name, &sb) == -1)
		{
			perror("stat");
			exit(EXIT_SUCCESS);
		}
		voyager = voyager->next;
	}
	to_sort->next = voyager->next;
	voyager->next = to_sort;
}

t_list		*ft_read_stock_dir(char *dir_name, t_options option)
{
	t_list			*dir_list;
	t_list			*to_sort;
	DIR				*dirhandle;
	struct dirent	*dirdata;
	int				flag;

	dirhandle = NULL;
	dirdata = NULL;
	to_sort = NULL;
	dir_list = NULL;
	flag = (option.r) ? -1 : 1;
	if (!(dirhandle = opendir(dir_name)))
		return (NULL);
	while ((dirdata = readdir(dirhandle)))
	{
		if (!(to_sort = ft_lstnew(dirdata, sizeof(*dirdata))))
			return (NULL);
		if (!(dir_list))
			dir_list = to_sort;
		else
			(option.t) ? ft_sortins_time(&dir_list, to_sort, flag) :
				ft_sortins_ascii(&dir_list, to_sort, flag);
	}
	closedir(dirhandle);
	return (dir_list);
}
