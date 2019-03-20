/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_padding_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:35:28 by baavril           #+#    #+#             */
/*   Updated: 2019/03/19 23:34:08 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <pwd.h>
#include <grp.h>
#include "ft_ls.h"
#include "libft.h"

extern t_padlen		g_padlen;

static void		ft_get_size_ofsize(struct stat *sb)
{
	if ((sb->st_mode & S_IFMT) != S_IFCHR
	&& (sb->st_mode & S_IFMT) != S_IFBLK)
	{
		if (integer_len(sb->st_size) > g_padlen.size)
			g_padlen.size = integer_len(sb->st_size);
	}
	else
	{
		if (integer_len(major(sb->st_rdev)) > g_padlen.size_maj)
			g_padlen.size_maj = integer_len(major(sb->st_rdev));
		if (integer_len(minor(sb->st_rdev)) > g_padlen.size_min)
			g_padlen.size_min = integer_len(minor(sb->st_rdev));
		if (g_padlen.size_min + g_padlen.size_maj + 2 > g_padlen.size)
			g_padlen.size = g_padlen.size_min + g_padlen.size_maj + 2;
	}
}

static void		ft_get_size_group_name(struct stat *sb, t_options option)
{
	struct group *grp;

	if ((grp = getgrgid(sb->st_gid)) != NULL && !(option.n))
	{
		if ((int)ft_strlen(grp->gr_name) + 2 > g_padlen.grname)
			g_padlen.grname = ft_strlen(grp->gr_name) + 2;
	}
	else
	{
		if (integer_len(sb->st_gid) + 2 > g_padlen.grname)
			g_padlen.grname = integer_len(sb->st_gid) + 2;
	}
}

static void		ft_get_size_pwname(struct stat *sb, t_options option)
{
	struct passwd	*pwd;

	if ((pwd = getpwuid(sb->st_uid)) != NULL && !(option.n))
	{
		if ((int)ft_strlen(pwd->pw_name) + 2 > g_padlen.pwname)
			g_padlen.pwname = ft_strlen(pwd->pw_name) + 2;
	}
	else
	{
		if (integer_len(sb->st_uid) > g_padlen.pwname)
			g_padlen.pwname = integer_len(sb->st_uid);
	}
}

static void		ft_get_size_link(struct stat *sb)
{
	if (integer_len(sb->st_nlink) + 1 > g_padlen.nlink)
		g_padlen.nlink = integer_len(sb->st_nlink) + 1;
}

int				ft_update_padding(t_options option, struct stat *sb)
{
	ft_get_size_link(sb);
	ft_get_size_pwname(sb, option);
	ft_get_size_group_name(sb, option);
	ft_get_size_ofsize(sb);
	return (sb->st_blocks);
}
