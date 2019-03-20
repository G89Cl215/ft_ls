/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:51:43 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/16 16:39:07 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"
#include "../libft/libft.h"
#include "../ft_ls.h"
#include <sys/stat.h>

int		ft_flist_time_cmp(t_flist *lst1, t_flist *lst2)
{
	struct stat		sb1;
	struct stat		sb2;

	ft_get_file_stat(lst1->file_name, &sb1);
	ft_get_file_stat(lst2->file_name, &sb2);
	if ((sb1.st_mtimespec).tv_sec == (sb2.st_mtimespec).tv_sec)
		return (ft_strcmp(lst2->file_name, lst1->file_name));
	else
		return (((sb1.st_mtimespec).tv_sec - (sb2.st_mtimespec).tv_sec));
}

int		ft_reclist_time_cmp(t_reclist *lst1, t_reclist *lst2)
{
	struct stat		sb1;
	struct stat		sb2;

	ft_get_stats(lst1, &sb1);
	ft_get_stats(lst2, &sb2);
	if ((sb1.st_mtimespec).tv_sec == (sb2.st_mtimespec).tv_sec)
		return (ft_strcmp(lst2->file_name, lst1->file_name));
	else
		return ((sb1.st_mtimespec).tv_sec - (sb2.st_mtimespec).tv_sec);
}
