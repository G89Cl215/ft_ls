/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:08:33 by baavril           #+#    #+#             */
/*   Updated: 2019/03/02 20:33:14 by tgouedar         ###   ########.fr       */
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

	(void)argc;
	flag = 0;
	parsing_list = NULL;
	ft_option(&argv, &options);
	if (!(flag = ft_parsing_dir(argv, options, &parsing_list))
	&& !(parsing_list))
		return (dir_management(".", options, 0));
	tmp = parsing_list;
	while (tmp)
	{
		dir_management(tmp->path, options, flag);
		tmp = tmp->next;
		flag++;
	}
	ft_free_t_flist(&parsing_list);
	return (0);
}
