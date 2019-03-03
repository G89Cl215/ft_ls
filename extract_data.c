/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:43:32 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/03 00:35:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_ls.h"
/*
uint8_t	ft_link(char *path, struct dirent **filedata, int flag)
{
	
}
*/

char	*ft_reconstruct_path(t_flist *voyager, int flag)
{
	char			*file;
	size_t			len_dir;

	len_dir = 0;
	if (ft_strcmp("/", voyager->path) && ft_strcmp(".", voyager->path))
		len_dir += ft_strlen(voyager->path);
	len_dir += ft_strlen((voyager->filedata)->d_name);
	if (((flag) && !(file = (char*)malloc(len_dir + 2 + voyager->flag)))
	|| !(file = (char*)malloc(len_dir + 2)))
		return (NULL);
	file[0] = '\0';
	if (ft_strcmp("/", voyager->path) && ft_strcmp(".", voyager->path))
	{
//		ft_putendl("yeeeeeeee");
//		ft_putendl(voyager->path);
		ft_strcat(file, voyager->path);
	}
	if (ft_strcmp(".", voyager->path))
		ft_strcat(file, "/\0");
	ft_strcat(file, (voyager->filedata)->d_name);
	if (flag && voyager->flag)
		ft_strcat(file, "/\0");
	else
		file[len_dir + 2] = '\0';
	return (file);
}

void	ft_get_stats(t_flist *voyager, struct stat *file_stat)
{
	char			*file;

//	ft_printf("%p ", *voyager);
//	ft_putendl(voyager->path);
	if (!(file = ft_get_file(voyager)))
		return ;  // retour plus profond de l'erreur ?
//	ft_putendl(file);
	if (lstat(file, file_stat) == -1)
	{
		perror("stat");
		exit(EXIT_SUCCESS);
	}
	free(file);
}
