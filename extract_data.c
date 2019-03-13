/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/18 20:43:32 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:31:18 by tgouedar         ###   ########.fr       */
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

void	ft_get_stats(t_reclist *voyager, struct stat *file_stat)
{
	char			*file;

	if (!(file = ft_get_file(voyager)))
		return ;
	if (lstat(file, file_stat) == -1)
	{
		perror("stat");
		exit(EXIT_SUCCESS);
	}
	free(file);
}
