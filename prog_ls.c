/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_ls.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 16:35:59 by baavril           #+#    #+#             */
/*   Updated: 2019/02/12 08:17:29 by tgouedar         ###   ########.fr       */
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

int		option_l(int ac, char *av, struct dirent *dp, DIR *dir)
{
	struct stat 		sb;
	int					i;

	i = 0;
	while ((dp = readdir(dir)))
	{
		if (i >= 2)
		{
			stat(dp->d_name, &sb);
			printf("\n");
			printf("%s\n", dp->d_name);
			printf("Type de fichier :                ");
			printf("Numéro d'inœud :                   %ld\n", (long) sb.st_ino);
			printf("Mode :                             %lo (octal)\n",
					(unsigned long) sb.st_mode);
			printf("Nombre de liens :                  %ld\n", (long) sb.st_nlink);
			printf("Propriétaires :                    UID=%ld   GID=%ld\n",
					(long) sb.st_uid, (long) sb.st_gid);
			printf("Taille de bloc d’E/S :             %ld octets\n",
					(long) sb.st_blksize);
			printf("Taille du fichier :                %lld octets\n",
					(long long) sb.st_size);
			printf("Blocs alloués :                    %lld\n",
					(long long) sb.st_blocks);
			printf("Dernier changement d’état :        %s", ctime(&sb.st_ctime));
			printf("Dernier accès au fichier :         %s", ctime(&sb.st_atime));
			printf("Dernière modification du fichier:  %s", ctime(&sb.st_mtime));
		}
		i++;
	}
	closedir(dir);
	return (1);
}

int	main(int argc, char **argv)
{
	struct dirent 		*dp;
	struct stat 		sb;
	t_options 			options;
	DIR 				*dir;
	int					i;

	i = 1;
	options.l = 0;
	if (option(argc, argv, &options) == 1)	
	{
		while (argc >= i)
		{
			if ((dir = opendir(argv[i])))
			{
				if (options.l == 1)
					option_l(argc, *argv, dp, dir);
			}
			i++;
		}
	}
	else
	{
		while (argc >= 2)
		{
			if (!(dir = opendir(argv[i])))
				return (0);
			while ((dp = readdir(dir)))
				 printf("%s\n", dp->d_name);
			i++;
		}
	}
	return (1);
}
