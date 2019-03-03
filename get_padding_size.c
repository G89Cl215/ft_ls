/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_padding_size.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 16:35:28 by baavril           #+#    #+#             */
/*   Updated: 2019/03/03 14:35:29 by tgouedar         ###   ########.fr       */
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

int				integer_len(int nbr)
{
	int l;

	l = 1;
	while (nbr /= 10)
		++l;
	return (l);
}

static void		ft_get_size_ofsize(struct stat *sb)
{
	if (!(sb->st_mode & S_IFCHR) || !(sb->st_mode & S_IFBLK))
	{
		if (integer_len(sb->st_size) > g_padlen.size)
			g_padlen.size = integer_len(sb->st_size); 
	}
	else
	{
		if (integer_len(major(sb->st_rdev)) + 1 > g_padlen.size_maj)
			g_padlen.size_maj = integer_len(major(sb->st_rdev)) + 1;
		if (integer_len(minor(sb->st_rdev)) + 2 > g_padlen.size_min)
			g_padlen.size_min = integer_len(minor(sb->st_rdev)) + 2; 

	}
}

static void		ft_get_size_group_name(struct stat *sb, t_options option)
{
	struct group *grp;

	if ((grp = getgrgid(sb->st_gid)) != NULL && !(option.n))
	{
		if (g_padlen.grname == 0)
			g_padlen.grname = ft_strlen(grp->gr_name) + 2;
		if ((int)ft_strlen(grp->gr_name) + 2 > g_padlen.grname)
			g_padlen.grname = ft_strlen(grp->gr_name) + 2;
	}
	else
	{
		if (g_padlen.grname == 0)
			g_padlen.grname = integer_len(sb->st_gid) + 2;
		if (integer_len(sb->st_gid) + 2 > g_padlen.grname)
			g_padlen.grname = integer_len(sb->st_gid) + 2;
	}
}

static void		ft_get_size_pwname(struct stat *sb, t_options option)
{
	struct passwd	*pwd;

	if ((pwd = getpwuid(sb->st_uid)) != NULL && !(option.n))
	{
		if (g_padlen.pwname == 0)
			g_padlen.pwname = ft_strlen(pwd->pw_name) + 2;
		if ((int)ft_strlen(pwd->pw_name) + 2 > g_padlen.pwname)
			g_padlen.pwname = ft_strlen(pwd->pw_name) + 2;
	}
	else
	{
		if (g_padlen.pwname == 0)
			g_padlen.pwname = integer_len(sb->st_uid) + 2;
		if (integer_len(sb->st_uid) + 2 > g_padlen.pwname)
			g_padlen.pwname = integer_len(sb->st_uid) + 2;
	}
}

static void		ft_get_size_link(struct stat *sb)
{
	if (g_padlen.nlink == 0)
		g_padlen.nlink = integer_len(sb->st_nlink) + 1;
	if (integer_len(sb->st_nlink) + 1 > g_padlen.nlink)
		g_padlen.nlink = integer_len(sb->st_nlink) + 1;
}

void			ft_update_padding(t_flist *voyager, t_options option, struct stat *sb)
{
		ft_get_stats(voyager, sb);
		ft_get_size_link(sb);
		ft_get_size_pwname(sb, option);
		ft_get_size_group_name(sb, option);
		ft_get_size_ofsize(sb);
}
