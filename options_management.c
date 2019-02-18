/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:42:56 by baavril           #+#    #+#             */
/*   Updated: 2019/02/18 17:59:12 by tgouedar         ###   ########.fr       */
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

/*void	ft_get_group_name()
{
	int bufsize;
	struct group name;
	int i;
	int j;

	i = 0;
	j = 0;
	if ((bufsize = sysconf(_SC_GETGR_R_SIZE_MAX)) == -1)
		abort();
	while (name.gr_mem[i][j])
	{
		ft_putchar(name.gr_mem[i][j++]);
	}
}*/

void	ft_get_passwd()
{
	int bufsize;
	struct passwd pwd, *result = NULL;

	if ((bufsize = sysconf(_SC_GETPW_R_SIZE_MAX)) == -1)
		abort();

	char buffer[bufsize];
	if (getpwuid_r(getuid(), &pwd, buffer, bufsize, &result) != 0 || !result)
		abort();
	printf(" ");
	printf("%s", pwd.pw_name);
}

void ft_get_file_type(char *buf, struct stat sb)
{
	if (sb.st_mode & S_IFMT)
	{
		if (sb.st_mode & S_IFREG)
			buf[0] = '-';
		else if (sb.st_mode & S_IFDIR)	
			buf[0] = 'd';
	}
}

void	ft_get_chmod(struct stat sb)
{
	char buf[12];

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
	printf("%s", buf);
}

int		ft_print_new_dir(char *dir_name, char *next_dir, t_options option)
{
	size_t	len_dir;
	size_t	len_add;
	char	*str;

	len_dir = ft_strlen(dir_name);
	len_add = ft_strlen(next_dir) - ((len_dir) ? 0 : 1);
	if (!(str = (char*)malloc(len_add + len_dir + 2)))
		return (0);
	str[0] = '\0';
	if (*dir_name)
	{
		ft_strcat(str, dir_name);
		ft_strcat(str, "/");
	}
	ft_strcat(str, next_dir);
	str[len_dir + len_add + 1] = '\0';
	printf("\n%s:\n", str);
	dir_management(str, option, 0);
	free(str);
	return (1);
}

void	ft_longdisplay(t_list *voyager)
{
	struct stat		sb;
	char			*timebuff;
	char			*file;

	file = ((struct dirent*)(voyager->content))->d_name;
		if (stat(file, &sb) == -1)
			{
				perror("stat");
				exit(EXIT_SUCCESS);
			}
			ft_get_chmod(sb);
			printf("%4d", sb.st_nlink);
			ft_get_passwd();
		//	ft_get_group_name();
			timebuff = ctime(&(sb.st_mtime));
			ft_memmove(timebuff, timebuff + 4, ft_strlen(timebuff) - 4);
			timebuff[12] = '\0';
			printf("%6lld ", sb.st_size);
			printf("%s ", timebuff);
			printf("%s\n", file);
}

int		ft_current(t_list **dir_list, char *dir_name, t_options option)
{
	t_list			*voyager;
	struct stat		sb;

	voyager = *dir_list;
	if ((option.l))
	{
		if (stat(((struct dirent*)(voyager->content))->d_name, &sb) == -1)
		{
			perror("stat");
			exit(EXIT_SUCCESS);
		}
		printf("total %lld\n", sb.st_size);//a revoir -> il faut la somme de tout les fichiers a l'interieur du dossier	
	}
	while (voyager)
	{
		if ((option.a) || *(((struct dirent*)(voyager->content))->d_name) != '.')
			(option.l) ? ft_longdisplay(voyager)
			: printf("%s\n", ((struct dirent*)(voyager->content))->d_name);
		voyager = voyager->next;
	}
	if (option.R)
	{
		voyager = *dir_list;
		while (voyager)
		{
			if ((((struct dirent*)(voyager->content))->d_type == DT_DIR)
			&& (ft_strcmp(((struct dirent*)(voyager->content))->d_name, "."))
			&& (ft_strcmp(((struct dirent*)(voyager->content))->d_name, ".."))
			&& (((option.a)
			|| *(((struct dirent*)(voyager->content))->d_name) != '.')))
				ft_print_new_dir(dir_name, ((struct dirent*)(voyager->content))->d_name, option);
			voyager = voyager->next;
		}
	}
	ft_lstfree(dir_list);
	return (1);
}
