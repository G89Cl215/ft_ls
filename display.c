/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/19 23:36:00 by baavril           #+#    #+#             */
/*   Updated: 2019/02/20 22:26:07 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft/libft.h"

void		ft_display_file(t_flist *voyager, t_options option)
{
	if ((voyager->filedata)
	&& ((option.a) || *((voyager->filedata))->d_name != '.'))
		(option.l) ? ft_longdisplay(voyager)
					: printf("%s\n", (voyager->filedata)->d_name);
	//gestion de sortie d'erreur :file not found
	//else
}

void	ft_longdisplay(t_flist *voyager)
{
	struct stat		sb;
	char			*timebuff;

	ft_get_stats(voyager, &sb);
	ft_get_chmod(sb);
	printf("%4d", sb.st_nlink);
	ft_get_passwd();
	ft_get_group_name(sb);
	timebuff = ctime(&(sb.st_mtime));
	ft_memmove(timebuff, timebuff + 4, ft_strlen(timebuff) - 4);
	timebuff[12] = '\0';
	if (!(sb.st_mode & S_IFCHR) || !(sb.st_mode & S_IFBLK))
		printf("%7lld ", sb.st_size);
	else
	{
		printf("%7d, ", major(sb.st_rdev));
		printf(", %7d ", minor(sb.st_rdev));
	}
	printf("%s ", timebuff);
	printf("%s\n", (voyager->filedata)->d_name);
}
