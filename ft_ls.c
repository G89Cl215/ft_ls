/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:08:33 by baavril           #+#    #+#             */
/*   Updated: 2019/02/11 16:47:32 by baavril          ###   ########.fr       */
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

t_list	*ft_stock_dir(struct dirent *dp, DIR *dir, t_list *buff_list)
{
	t_list	*dir_list;
	t_list	*new_nod;

	if (!(dir_list = (t_list*)malloc(sizeof(t_list))))
		return (NULL);
	dir_list = NULL;
	while ((dp = readdir(dir)))
	{
		if (!(new_nod = ft_lstnew(dp->d_name, ft_strlen(dp->d_name) + 1)))
			return (NULL);
		ft_lstadd_back(&dir_list, new_nod);
	}
	return (dir_list);
}

int	main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *dp;
	int i;
	t_options	options;
	t_list	*buff_list;
	t_list	*dir_list;

	i = 1;	
	if (!(buff_list = (t_list*)malloc(sizeof(t_list))))
		return (0);
	buff_list = NULL;
	if (option(argc, argv, &options) == 1)	
	{
		while (argc >= i)
		{
			if ((dir = opendir(argv[i])))
			{	
				if (!(dir_list = ft_stock_dir(dp, dir, buff_list)))
					return (0);
				if (options.a == 1)
					option_a(dir_list);
			//	if (options.R == 1)
			//		option_R(dir_list);
			}
			i++;
		}
	}
	else
	{
		closedir(dir);
		return (0);
	}
	return (0);
}
