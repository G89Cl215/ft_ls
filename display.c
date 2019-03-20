/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 23:36:00 by baavril           #+#    #+#             */
/*   Updated: 2019/03/19 23:43:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "ft_ls.h"
#include "libft.h"

char			*ft_get_file(t_reclist *voyager)
{
	char		*file;
	size_t		len_dir;

	len_dir = (ft_strcmp("/", voyager->path)) ? ft_strlen(voyager->path) : 0;
	len_dir += ft_strlen(voyager->file_name);
	if (!(file = (char*)malloc(len_dir + 2)))
		return (0);
	file[0] = '\0';
	if (ft_strcmp("/", voyager->path))
		ft_strcat(file, voyager->path);
	ft_strcat(file, "/\0");
	ft_strcat(file, voyager->file_name);
	file[len_dir + 1] = '\0';
	return (file);
}

static void		ft_get_symblink(t_reclist *voyager, struct stat *sb)
{
	char		*buf;
	char		*file;
	ssize_t		nbytes;
	ssize_t		bufsize;

	bufsize = sb->st_size;
	file = ft_get_file(voyager);
	if (sb->st_size == 0)
		bufsize = PATH_MAX;
	if (!(buf = ft_strnew(bufsize)))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	nbytes = readlink(file, buf, bufsize);
	free(file);
	buf[bufsize] = '\0';
	ft_putstr(voyager->file_name);
	ft_putstr(" -> ");
	ft_putendl(buf);
	free(buf);
}

void			ft_display_file(t_reclist *voyager, t_options option)
{
	if ((option.a) || *(voyager->file_name) != '.')
		(option.l || option.n || option.o || option.g)
			? ft_longdisplay(voyager, option)
			: ft_putendl(voyager->file_name);
}

void			ft_clock(struct stat *sb)
{
	time_t		diff;
	char		*mtime_str;

	mtime_str = ctime(&sb->st_mtime);
	diff = time(NULL) - sb->st_mtime;
	ft_memmove(mtime_str, mtime_str + 4, ft_strlen(mtime_str));
	mtime_str[6] = '\0';
	ft_strcat(mtime_str, " ");
	ft_putstr(mtime_str);
	mtime_str = ctime(&sb->st_mtime);
	if ((diff < MONTHS_LIMIT_INF || diff > MONTHS_LIMIT_SUP))
	{
		ft_memmove(mtime_str, mtime_str + 19, ft_strlen(mtime_str));
		mtime_str[ft_strlen(mtime_str) - 1] = '\0';
		if (mtime_str[2] == ' ')
			ft_memmove(mtime_str, mtime_str + 4, ft_strlen(mtime_str));
	}
	else
	{
		ft_memmove(mtime_str, mtime_str + 11, ft_strlen(mtime_str));
		mtime_str[5] = '\0';
	}
	ft_strcat(mtime_str, " ");
	ft_putstr(mtime_str);
}

void			ft_longdisplay(t_reclist *voyager, t_options option)
{
	struct stat		sb;
	char			buf[12];

	ft_get_stats(voyager, &sb);
	ft_get_chmod(&sb, buf, voyager);
	ft_append_str(sb.st_nlink, g_padlen.nlink);
	ft_get_passwd(&sb, option);
	if (!(option.o))
		ft_get_group_name(&sb, option);
	if (((option.o) && (option.g)) || (option.n))
		ft_putstr("  ");
	if (buf[0] != 'c' && buf[0] != 'b')
		ft_printf("%*d", g_padlen.size, sb.st_size);
	else
	{
		ft_append_str(major(sb.st_rdev), g_padlen.size_maj);
		ft_putstr(", ");
		ft_append_str(minor(sb.st_rdev), g_padlen.size_min);
	}
	ft_putchar(' ');
	ft_clock(&sb);
	if (!((sb.st_mode & S_IFMT) == S_IFLNK))
		ft_putendl(voyager->file_name);
	else
		ft_get_symblink(voyager, &sb);
}
