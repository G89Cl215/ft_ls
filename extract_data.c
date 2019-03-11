/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:43:32 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 19:00:25 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "ft_ls.h"

void	ft_get_file_stat(char *file_name, struct stat *file_stat)
{
	if (lstat(file_name, file_stat) == -1)
	{
		perror("stat");
		exit(EXIT_SUCCESS);
	}
}

void	ft_get_stats(t_Rlist *voyager, struct stat *file_stat)
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
