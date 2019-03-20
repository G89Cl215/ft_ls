/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   recursive_call.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/02 15:00:24 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/19 23:33:37 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include <stdlib.h>
#include "ft_ls.h"
#include "libft.h"

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
	if (flag == 1)
	{
		ft_putstr(dir_name);
		ft_putendl(":");
	}
	else if (flag)
	{
		ft_putchar('\n');
		ft_putstr(dir_name);
		ft_putendl(":");
	}
	if (!(dir_list = ft_read_stock_dir(dir_name, options)))
		return (0);
	ft_current(&dir_list, dir_name, options);
	return (1);
}

int			ft_print_new_dir(char *dir_name, char *next_dir, t_options option)
{
	size_t	len_dir;
	char	*str;

	len_dir = ft_strcmp("/", dir_name) ? ft_strlen(dir_name) : 0;
	len_dir += ft_strlen(next_dir);
	if (!(str = (char*)malloc(len_dir + 2)))
		return (0);
	str[0] = '\0';
	if (ft_strcmp("/", dir_name))
		ft_strcat(str, dir_name);
	ft_strcat(str, "/\0");
	ft_strcat(str, next_dir);
	str[len_dir + 1] = '\0';
	dir_management(str, option, 2);
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
	ft_free_t_reclist(dir_list);
}

int			ft_current(t_reclist **dir_list, char *dir_name, t_options option)
{
	t_reclist		*voyager;
	struct stat		sb;
	off_t			len_oct;
	int				nb_todisplay;

	voyager = *dir_list;
	len_oct = 0;
	nb_todisplay = 0;
	ft_reset(&g_padlen);
	if ((option.l) || (option.n) || (option.g) || (option.o))
	{
		while (voyager)
		{
			if ((option.a) || *(voyager->file_name) != '.')
			{
				ft_get_stats(voyager, &sb);
				nb_todisplay++;
				len_oct += ft_update_padding(option, &sb);
			}
			voyager = voyager->next;
		}
		ft_print_total(len_oct, nb_todisplay);
	}
	ft_current2(dir_list, dir_name, option);
	return (1);
}
