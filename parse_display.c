/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_display.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:44:20 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/19 23:42:12 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include <stdlib.h>
#include <stdio.h>
#include "ft_ls.h"
#include "libft.h"

static char		get_file_acl(char *file_name)
{
	acl_t	tmp;
	char	buf[1000];

	if (listxattr(file_name, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
		return ('@');
	if ((tmp = acl_get_link_np(file_name, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		return ('+');
	}
	return (' ');
}

void			ft_parse_get_chmod(struct stat *sb, char *buf, char *file_name)
{
	buf[0] = ft_get_file_type(sb);
	buf[1] = (sb->st_mode & S_IRUSR) ? 'r' : '-';
	buf[2] = (sb->st_mode & S_IWUSR) ? 'w' : '-';
	buf[3] = (sb->st_mode & S_IXUSR) ? 'x' : '-';
	buf[4] = (sb->st_mode & S_IRGRP) ? 'r' : '-';
	buf[5] = (sb->st_mode & S_IWGRP) ? 'w' : '-';
	buf[6] = (sb->st_mode & S_IXGRP) ? 'x' : '-';
	buf[7] = (sb->st_mode & S_IROTH) ? 'r' : '-';
	buf[8] = (sb->st_mode & S_IWOTH) ? 'w' : '-';
	buf[9] = (sb->st_mode & S_IXOTH) ? 'x' : '-';
	buf[10] = get_file_acl(file_name);
	buf[11] = '\0';
	if (sb->st_mode & S_ISUID)
		buf[3] = (buf[3] == '-') ? 'S' : 's';
	if (sb->st_mode & S_ISGID)
		buf[6] = (buf[6] == '-') ? 'S' : 's';
	if (sb->st_mode & S_ISVTX)
		buf[9] = (buf[9] == '-') ? 'T' : 't';
	ft_putstr(buf);
}

static void		ft_get_symblink(char *file_name, struct stat *sb)
{
	char		*buf;
	ssize_t		nbytes;
	ssize_t		bufsize;

	bufsize = sb->st_size;
	if (sb->st_size == 0)
		bufsize = PATH_MAX;
	if (!(buf = ft_strnew(bufsize)))
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	nbytes = readlink(file_name, buf, bufsize);
	buf[bufsize] = '\0';
	ft_putstr(file_name);
	ft_putstr(" -> ");
	ft_putendl(buf);
	free(buf);
}

void			ft_parse_longdisplay(char *file_name, t_options option)
{
	struct stat		sb;
	char			buf[12];

	ft_get_file_stat(file_name, &sb);
	ft_parse_get_chmod(&sb, buf, file_name);
	ft_append_str(sb.st_nlink, g_padlen.nlink);
	ft_get_passwd(&sb, option);
	if (!(option.o))
		ft_get_group_name(&sb, option);
	if (buf[0] != 'c' && buf[0] != 'b')
		ft_append_str(sb.st_size, g_padlen.size);
	else
	{
		ft_append_str(major(sb.st_rdev), g_padlen.size_maj);
		ft_putstr(", ");
		ft_append_str(minor(sb.st_rdev), g_padlen.size_min);
	}
	ft_putchar(' ');
	ft_clock(&sb);
	if ((sb.st_mode & S_IFMT) != S_IFLNK)
		ft_putendl(file_name);
	else
		ft_get_symblink(file_name, &sb);
}

void			ft_parse_display(char *file_name, t_options option)
{
	if ((option.a) || *file_name != '.')
		(option.l || option.n || option.o || option.g) ?
			ft_parse_longdisplay(file_name, option)
			: ft_putendl(file_name);
}
