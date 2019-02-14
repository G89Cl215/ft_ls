/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_and_stock_ls.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 11:27:06 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/14 06:01:37 by tgouedar         ###   ########.fr       */
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
	t_list	*tmp;

	if (!lst_start)
		return ;
	if (!(*lst_start))
		*lst_start = to_sort;
	else
	{
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
		tmp = voyager->next;
		voyager->next = to_sort;
		to_sort->next = tmp;
	}
}

void		ft_sortins_time(t_list **lst_start, t_list *to_sort, int flag)
{
	char			*name_sort;
	char			*name_cur;
	struct stat		sb_sort;
	struct stat		sb;
	t_list			*voyager;
	t_list			*tmp;

	if (!lst_start)
		return ;
	if (!(*lst_start))
		*lst_start = to_sort;
	else
	{
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
		name_sort = ((struct dirent*)(to_sort->content))->d_name;
		name_cur = ((struct dirent*)(voyager->content))->d_name;
		while ((voyager->next)
		&& ((sb.st_mtimespec).tv_sec == (sb_sort.st_mtimespec).tv_sec)
		&& ((flag * ft_strcmp(name_cur, name_sort)) < 0))
		{
			if (stat(((struct dirent*)((voyager->next)->content))->d_name, &sb) == -1)
			{
				perror("stat");
				exit(EXIT_SUCCESS);
			}
			voyager = voyager->next;
		}
		tmp = voyager->next;
		voyager->next = to_sort;
		to_sort->next = tmp;
	}
}

t_list		*ft_read_stock_dir(char *dir_name, t_options option)
{
	t_list			*dir_list;
	t_list			*to_sort;
	DIR				*dirhandle;
	struct dirent	*dirdata;
	int				flag;

	dir_list = NULL;
	flag = (option.r) ? -1 : 1;
	if (!(dirhandle = opendir(dir_name)))
		return (NULL);
	while ((dirdata = readdir(dirhandle)))
	{
		if (!(to_sort = ft_lstnew(dirdata, sizeof(*dirdata))))
			return (NULL);
		if (!(option.t))
			ft_sortins_ascii(&dir_list, to_sort, flag);
		else
			ft_sortins_time(&dir_list, to_sort, flag);
	}
	closedir(dirhandle);
	return (dir_list);
}
