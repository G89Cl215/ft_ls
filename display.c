/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 23:36:00 by baavril           #+#    #+#             */
/*   Updated: 2019/03/03 15:08:39 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft/libft.h"

t_padlen	g_padlen = {.nlink = 0, .pwname = 0,
	.grname = 0, .size = 0, .size_min = 0, .size_maj = 0}; 

char	*ft_get_file(t_flist *voyager)
{
	char			*file;
	size_t			len_dir;

	len_dir = (ft_strcmp("/", voyager->path)) ? ft_strlen(voyager->path) : 0;
	len_dir += ft_strlen((voyager->filedata)->d_name);
	if (!(file = (char*)malloc(len_dir + 2)))
		return (0);
	file[0] = '\0';
	if (ft_strcmp("/", voyager->path))
		ft_strcat(file, voyager->path);
	ft_strcat(file, "/\0");
	ft_strcat(file, (voyager->filedata)->d_name);
	file[len_dir + 1] = '\0';
	return (file);
}

void	ft_get_symblink(t_flist	*voyager, struct stat *sb)
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
	ft_printf("%s -> %s\n", file = ft_get_file(voyager), buf);
	free(buf);
	free(file);
}

void		ft_display_file(t_flist *voyager, t_options option)
{
	char	*file;

	//ft_putendl(voyager->path);
	if (voyager->flag)
	{
		ft_printf("ft_ls: %s: Not a directory\n", file = ft_reconstruct_path(voyager, 1));
		free(file);
	}
	else if ((voyager->filedata)
	&& ((option.a) || *((voyager->filedata))->d_name != '.'))
		(option.l || option.n || option.o || option.g) ? ft_longdisplay(voyager, option)
			: ft_printf("%s\n", (voyager->filedata)->d_name);/*ft_reconstruct_path(voyager, 0));*/
}

inline static void		ft_clock(struct stat *sb)
{
	time_t		diff;
	char		*mtime_str;

	mtime_str = ctime(&sb->st_mtime);
	diff = time(NULL) - sb->st_mtime;
	ft_memmove(mtime_str, mtime_str + 4, ft_strlen(mtime_str));
	mtime_str[6] = '\0';
	ft_printf("%s ", mtime_str);
	mtime_str = ctime(&sb->st_mtime);
	if ((diff < MONTHS_LIMIT_INF || diff > MONTHS_LIMIT_SUP))
	{
		ft_memmove(mtime_str, mtime_str + 19, ft_strlen(mtime_str));
		mtime_str[ft_strlen(mtime_str) - 1] = '\0';
		if (mtime_str[2] == ' ')
			ft_memmove(mtime_str, mtime_str + 4, ft_strlen(mtime_str));
		ft_printf("%s ", mtime_str);
	}
	else
	{
		ft_memmove(mtime_str, mtime_str + 11, ft_strlen(mtime_str));
		mtime_str[5] = '\0';
		ft_printf("%s ", mtime_str);
	}
}

void	ft_longdisplay(t_flist *voyager, t_options option)
{
	struct stat		sb;
	char			buf[12];

	ft_get_stats(voyager, &sb);
	ft_get_chmod(&sb, buf, voyager);
	ft_printf("%*d", g_padlen.nlink, sb.st_nlink);
	if (!(option.g))
		ft_get_passwd(&sb, option);
	if (!(option.o))
		ft_get_group_name(&sb, option);
	if (buf[0] != 'c' && buf[0] != 'b')
		ft_printf("%*lld ", g_padlen.size, sb.st_size);
	else
		ft_printf("%*d, %*d ", g_padlen.size_maj, major(sb.st_rdev),
			   					g_padlen.size_min, minor(sb.st_rdev));
	ft_clock(&sb);
	if (!((sb.st_mode & S_IFMT) == S_IFLNK))
		ft_printf("%s\n", (voyager->filedata)->d_name);/*ft_reconstruct_path(voyager, 0));*/
	else
		ft_get_symblink(voyager, &sb);
}
