/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 00:57:02 by baavril           #+#    #+#             */
/*   Updated: 2019/03/03 12:58:06 by tgouedar         ###   ########.fr       */
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
#include <sys/acl.h>
#include <sys/xattr.h>

extern t_padlen g_padlen; 

static char		get_file_acl(t_flist *voyager)
{
	acl_t	tmp;
	char	buf[1000];
	char	*file;

	file = ft_get_file(voyager);
	if (listxattr(file, buf, sizeof(buf), XATTR_NOFOLLOW) > 0)
	{
		free(file);
		return ('@');
	}
	if ((tmp = acl_get_link_np(file, ACL_TYPE_EXTENDED)))
	{
		acl_free(tmp);
		free(file);
		return ('+');
	}
	free(file);
	return (' ');
}

void			ft_get_group_name(struct stat *sb, t_options option)
{
	struct group	*grp;

	if ((grp = getgrgid(sb->st_gid)) != NULL && !(option.n))
		((option.g)) ? ft_printf(" %-*s", g_padlen.grname, grp->gr_name)
		: ft_printf("%-*s", g_padlen.grname, grp->gr_name);
	else
		ft_printf("%-*u", g_padlen.grname, sb->st_gid);
}

void				ft_get_passwd(struct stat *sb, t_options option)
{
	struct passwd	*pwd;

	if ((pwd = getpwuid(sb->st_uid)) != NULL && !(option.n))
		ft_printf(" %-*s", g_padlen.pwname, pwd->pw_name);
	else
		ft_printf(" %-*d", g_padlen.pwname, sb->st_uid);
}

char			ft_get_file_type(struct stat *sb)
{
	if (sb->st_mode & S_IFMT)
	{
		if ((sb->st_mode & S_IFMT) == S_IFREG)
			return ('-');
		else if ((sb->st_mode & S_IFMT) == S_IFDIR)
			return ('d');
		else if ((sb->st_mode & S_IFMT) == S_IFCHR)
			return ('c');
		else if ((sb->st_mode & S_IFMT) == S_IFBLK)
			return ('b');
		else if ((sb->st_mode & S_IFMT) == S_IFIFO)
			return ('p');
		else if ((sb->st_mode & S_IFMT) == S_IFLNK)
			return ('l');
		else if ((sb->st_mode & S_IFMT) == S_IFSOCK)
			return ('s');
	}
	return ('-');
}

void				ft_get_chmod(struct stat *sb, char *buf, t_flist *voyager)
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
	buf[10] = get_file_acl(voyager);
	buf[11] = '\0';
	if (sb->st_mode & S_ISUID)
		buf[3] = (buf[3] == '-') ? 'S' : 's';
	if (sb->st_mode & S_ISGID)
		buf[6] = (buf[6] == '-') ? 'S' : 's';
	if (sb->st_mode & S_ISVTX)
		buf[9] = (buf[9] == '-') ? 'T' : 't';
	ft_printf("%s", buf);
}
