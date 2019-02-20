/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_long_display.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 00:57:02 by baavril           #+#    #+#             */
/*   Updated: 2019/02/20 19:59:28 by tgouedar         ###   ########.fr       */
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

void			ft_get_group_name(struct stat sb)
{
	struct group *grp;

	if ((grp = getgrgid(sb.st_gid)) != NULL)
		printf("  %s", grp->gr_name);
	else
		printf("  %u", sb.st_gid);
}

static int		ft_init_passwd(int bufsize)
{
	char			buffer[bufsize];
	struct passwd	pwd;
	struct passwd	*result;

	result = NULL;
	if (getpwuid_r(getuid(), &pwd, buffer, bufsize, &result) != 0 || !result)
		return (0);
	printf(" %s", pwd.pw_name);
	return (1);
}

int				ft_get_passwd(void)
{
	int	bufsize;

	if ((bufsize = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1)
		return (0);
	ft_init_passwd(bufsize);
	return (1);
}

void			ft_get_file_type(char *buf, struct stat sb)
{
	if (sb.st_mode & S_IFMT)
	{
		if (sb.st_mode & S_IFREG)
			buf[0] = '-';
		else if (sb.st_mode & S_IFDIR)
			buf[0] = 'd';
		else if (sb.st_mode & S_IFCHR)
			buf[0] = 'c';
		else if (sb.st_mode & S_IFBLK)
			buf[0] = 'b';
		else if (sb.st_mode & S_IFIFO)
			buf[0] = 'p';
		else if (sb.st_mode & S_IFLNK)
			buf[0] = 'l';
		else if (sb.st_mode & S_IFSOCK)
			buf[0] = 's';
	}
	else
		buf[0] = '-';
}

void			ft_get_chmod(struct stat sb)
{
	char buf[11];

	ft_get_file_type(buf, sb);
	buf[1] = (sb.st_mode & S_IRUSR) ? 'r' : '-';
	buf[2] = (sb.st_mode & S_IWUSR) ? 'w' : '-';
	buf[3] = (sb.st_mode & S_IXUSR) ? 'x' : '-';
	buf[4] = (sb.st_mode & S_IRGRP) ? 'r' : '-';
	buf[5] = (sb.st_mode & S_IWGRP) ? 'w' : '-';
	buf[6] = (sb.st_mode & S_IXGRP) ? 'x' : '-';
	buf[7] = (sb.st_mode & S_IROTH) ? 'r' : '-';
	buf[8] = (sb.st_mode & S_IWOTH) ? 'w' : '-';
	buf[9] = (sb.st_mode & S_IXOTH) ? 'x' : '-';
	buf[10] = '\0';
	printf("%s", buf);
}
