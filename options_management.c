/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:42:56 by baavril           #+#    #+#             */
/*   Updated: 2019/02/20 22:44:45 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <unistd.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"
#include "libft/libft.h"

int		ft_print_new_dir(char *dir_name, char *next_dir, t_options option)
{
	size_t	len_dir;
	size_t	len_add;
	char	*str;

	len_dir = ft_strlen(dir_name);
	len_add = ft_strlen(next_dir) - ((len_dir) ? 0 : 1);
	if (!(str = (char*)malloc(len_add + len_dir + 2)))
		return (0);
	str[0] = '\0';
	if (*dir_name)
	{
		ft_strcat(str, dir_name);
		ft_strcat(str, "/\0");
	}
	ft_strcat(str, next_dir);
	str[len_dir + len_add + 1] = '\0';
	printf("\n%s:\n", str);
	dir_management(str, option, 0);
	free(str);
	return (1);
}

void	ft_current2(t_flist **dir_list, char *dir_name, t_options option)
{
	t_flist *voyager;

	voyager = *dir_list;
	while (voyager)
	{
		ft_display_file(voyager, option);
		voyager = voyager->next;
	}
	if (option.R)
	{
		voyager = *dir_list;
		while (voyager)
		{
			if (((voyager->filedata)->d_type == DT_DIR)
			&& (ft_strcmp((voyager->filedata)->d_name, "."))
			&& (ft_strcmp((voyager->filedata)->d_name, ".."))
			&& (((option.a)
			|| *((voyager->filedata)->d_name) != '.')))
				ft_print_new_dir(dir_name,
				(voyager->filedata)->d_name, option);
			voyager = voyager->next;
		}
	}
}

int		ft_current(t_flist **dir_list, char *dir_name, t_options option)
{
	t_flist			*voyager;
	struct stat		sb;
	off_t			len_oct;

	voyager = *dir_list;
	len_oct = 0;
//	ft_putendl(voyager->path);
//	ft_putendl(dir_name);

	if ((option.l))
	{
		while (voyager)
		{
			ft_get_stats(voyager, &sb);
			if ((option.a) || *((voyager->filedata)->d_name) != '.')
					len_oct += sb.st_blocks;
			voyager = voyager->next;
		}
		printf("total %lld\n", len_oct);
	}
	ft_current2(dir_list, dir_name, option);
//	ft_lstfree((t_list**)dir_list);
	return (1);
}
