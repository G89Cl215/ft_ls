/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:00:24 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 21:43:19 by tgouedar         ###   ########.fr       */
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

extern t_padlen		g_padlen;

void		ft_reset(t_padlen *padlen)
{
	padlen->nlink = 0;
	padlen->pwname = 0;
	padlen->grname = 0;
	padlen->size = 0;
	padlen->size_min = 0;
	padlen->size_maj = 0;
}

int			dir_management(char *dir_name, t_options options, int flag)
{
	t_reclist	*dir_list;

	dir_list = NULL;
	if (!(dir_list = ft_read_stock_dir(dir_name, options)))
		return (0);
	if (flag == 1)
		ft_printf("%s:\n", dir_name);
	else if (flag)
		ft_printf("\n%s:\n", dir_name);
	ft_current(&dir_list, dir_name, options);
	return (1);
}

int			ft_print_new_dir(char *dir_name, char *next_dir, t_options option)
{
	size_t	len_dir;
	char	*str;

	len_dir = ft_strlen(dir_name);
	len_dir += ft_strlen(next_dir) - ((len_dir) ? 0 : 1);
	if (!(str = (char*)malloc(len_dir + 2)))
		return (0);
	str[0] = '\0';
	if (*dir_name)
	{
		ft_strcat(str, dir_name);
		ft_strcat(str, "/\0");
	}
	ft_strcat(str, next_dir);
	str[len_dir + 1] = '\0';
	ft_printf("\n%s:\n", str);
	dir_management(str, option, 0);
	free(str);
	return (1);
}

void		ft_current2(t_reclist **dir_list, char *dir_name, t_options option)
{
	t_reclist		*voyager;

	voyager = *dir_list;
	while (voyager)
	{
		ft_display_file(voyager, option);
		voyager = voyager->next;
	}
	if (option.rec)
	{
		voyager = *dir_list;
		while (voyager)
		{
			if ((voyager->type == DT_DIR)
			&& (ft_strcmp(voyager->file_name, "."))
			&& (ft_strcmp(voyager->file_name, ".."))
			&& ((option.a) || *(voyager->file_name) != '.'))
				ft_print_new_dir(dir_name, voyager->file_name, option);
			voyager = voyager->next;
		}
	}
}

int			ft_current(t_reclist **dir_list, char *dir_name, t_options option)
{
	t_reclist		*voyager;
	struct stat		sb;
	off_t			len_oct;

	voyager = *dir_list;
	len_oct = 0;
	ft_reset(&g_padlen);
	if ((option.l) || (option.n) || (option.g) || (option.o))
	{
		while (voyager)
		{
			ft_get_stats(voyager, &sb);
			ft_update_padding(option, &sb);
			if ((option.a) || *(voyager->file_name) != '.')
				len_oct += sb.st_blocks;
			voyager = voyager->next;
		}
		ft_printf("total %lld\n", len_oct);
	}
	ft_current2(dir_list, dir_name, option);
	ft_free_t_reclist(dir_list);
	return (1);
}
