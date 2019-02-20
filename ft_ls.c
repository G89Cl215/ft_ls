/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:08:33 by baavril           #+#    #+#             */
/*   Updated: 2019/02/20 22:07:57 by tgouedar         ###   ########.fr       */
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

int	main(int argc, char **argv)
{
	t_options	options;
	t_flist		*parsing_list;
	t_flist		*tmp;
//	char		*dir_name;
	int			flag;

	flag = 0;
	parsing_list = NULL;
	ft_option(argc, argv, &options);
	if (!(flag = ft_parsing_dir(argv, options, &parsing_list))
	&& !(parsing_list))
		return (dir_management(".", options, 0));
	while (parsing_list)
	{
		tmp = parsing_list;
		dir_management(tmp->path, options, flag);
		parsing_list = parsing_list->next;
		flag++;
		free(tmp->filedata);
		free(tmp->path);
		free(tmp);
	}
	return (0);
}
