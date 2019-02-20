/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:43:32 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/20 22:50:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_ls.h"

void	ft_get_stats(t_flist *voyager, struct stat *file_stat)
{
	char			*file;
	size_t			len_dir;
	size_t			len_add;

	len_dir = (ft_strcmp("/", voyager->path)) ? ft_strlen(voyager->path) : 0;
	len_add = ft_strlen((voyager->filedata)->d_name);
	if (!(file = (char*)malloc(len_add + len_dir + 2)))
		return ;
	file[0] = '\0';
	if (ft_strcmp("/", voyager->path))
		ft_strcat(file, voyager->path);
	ft_strcat(file, "/\0");
	ft_strcat(file, (voyager->filedata)->d_name);
	file[len_dir + len_add + 1] = '\0';
//	ft_putendl(file); improbable mais le get stat bug sur le lien /usr/lib/libgutenprint.2.lidyb... parce que c'est un lien ? Pourtant on en affiche d'autre ? l'histoire du lstat peut etre ? who knows... en tout cas on est encore une fois trois fois plus que le systeme... A mediter.
	if (stat(file, file_stat) == -1)
	{
		perror("stat");
		exit(EXIT_SUCCESS);
	}
	free(file);
}
