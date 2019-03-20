/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 00:57:02 by baavril           #+#    #+#             */
/*   Updated: 2019/03/20 11:14:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdlib.h>
#include <pwd.h>
#include <grp.h>
#include <sys/acl.h>
#include <sys/xattr.h>
#include "ft_ls.h"
#include "libft.h"

extern t_padlen		g_padlen;

static char			get_file_acl(t_reclist *voyager)
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

void				ft_get_group_name(struct stat *sb, t_options option)
{
	struct group	*grp;

	if ((grp = getgrgid(sb->st_gid)) != NULL && !(option.n))
		ft_append_str2(grp->gr_name, g_padlen.grname);
	else
		ft_append_str(sb->st_gid, g_padlen.grname);
}

void				ft_get_passwd(struct stat *sb, t_options option)
{
	struct passwd	*pwd;
	char			*tmp;

	ft_putchar(' ');
	if (!(option.g))
	{
		if ((pwd = getpwuid(sb->st_uid)) != NULL && !(option.n))
			ft_append_str2(pwd->pw_name, g_padlen.pwname);
		else if (!(option.n))
		{
			tmp = ft_itoa(sb->st_uid);
			ft_append_str2(tmp, g_padlen.pwname);
			free(tmp);
		}
		else
			ft_append_str(sb->st_uid, g_padlen.pwname);
	}
}

char				ft_get_file_type(struct stat *sb)
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

void				ft_get_chmod(struct stat *sb, char *buf, t_reclist *voyager)
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
	ft_putstr(buf);
}
