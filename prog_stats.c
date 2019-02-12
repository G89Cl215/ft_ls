/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prog_stats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 18:47:34 by baavril           #+#    #+#             */
/*   Updated: 2019/02/12 12:04:30 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft/libft.h"
#include "libft/option.h"
/*
   int	main(int argc, char **argv)
   {
   struct stat		sb;
   struct dirent	*dirdata;
   DIR				*dir;


   if (argc != 2)
   {
   fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
   exit(EXIT_FAILURE);
   }
   if (stat(argv[1], &sb) == -1)
   {
   perror("stat");
   exit(EXIT_SUCCESS);
   }
   if ((dir = opendir(argv[1])))
   {
   printf("opendir_reussite\n");
   dirdata = readdir(dir);
   if (dirdata->d_type == DT_REG)
   printf("Type de fichier :                  f\n");
   if (dirdata->d_type == DT_DIR)
   printf("Type de fichier :                  dir\n");
   if (dirdata->d_type == DT_FIFO)
   printf("Type de fichier :                  Fifo\n");
   if (dirdata->d_type == DT_SOCK)
   printf("Type de fichier :                  socket\n");
   if (dirdata->d_type == DT_CHR)
   printf("Type de fichier :                  chr\n");
   if (dirdata->d_type == DT_BLK)
   printf("Type de fichier :                  block\n");
   closedir(dir);
   }
   else
   printf("Type de fichier :                  f\n");
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

   exit(EXIT_SUCCESS);
   }*/


void	ft_print_dir(char *dir_name, t_options option)
{
	DIR 			*dirhandle;
	DIR 			*dir_nested;
	char			*str;
	struct stat		sb;
	struct dirent	*dirdata;

	if (!(dirhandle = opendir(dir_name)))
		return ;
	while ((dirdata = readdir(dirhandle)))
	{
		if ((option.a) || *(dirdata->d_name) != '.')
		{
			printf("%s\n", dirdata->d_name);
//			if (dirdata->d_type == DT_REG) 
//				printf("Type de fichier :                  f\n");
			if (dirdata->d_type == DT_DIR)
			{
			//	printf("Type de fichier :                  dir\n");
				
			//	printf("%d\n", option.R);
				if ((option.R))
				{
					str = ft_strdup(dir_name);
					ft_strcat(str, "/");
					ft_strcat(str, dirdata->d_name);
					ft_print_dir(str, option);
				}
			}
			if (dirdata->d_type == DT_FIFO)
				printf("Type de fichier :                  Fifo\n");
			if (dirdata->d_type == DT_SOCK)
				printf("Type de fichier :                  socket\n");
			if (dirdata->d_type == DT_CHR)
				printf("Type de fichier :                  chr\n");
			if (dirdata->d_type == DT_BLK)
				printf("Type de fichier :                  block\n");
		}
		if ((option.l) && stat(dirdata->d_name, &sb) == -1)
		{
			perror("stat");
			exit(EXIT_SUCCESS);
		}
		else if ((option.l))
		{
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
	}
	closedir(dirhandle);
}

int		main(int ac, char **av)
{
	t_options		option;

	ft_option(ac, av, &option);
	printf("%d\n", option.a);
   	ft_print_dir(".", option);
	return (0);
}
