/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:23:17 by baavril           #+#    #+#             */
/*   Updated: 2019/02/14 08:57:58 by tgouedar         ###   ########.fr       */
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

t_list		*ft_parsing_dir(char **tab_dir)
{
	t_list	*list_dir;
	t_list	*new_nod;
	int i;
	int j;

	j = 0;
	i = 1;
	list_dir = NULL;
	if (tab_dir[i] == NULL)
		return (NULL);
	while (tab_dir[i])
	{
		if (tab_dir[i][0] != '-')
		{
			if (!(new_nod = ft_lstnew(tab_dir[i], ft_strlen(tab_dir[i]) + 1)))
				return (0);
			ft_lstadd_back(&list_dir, new_nod);
		}
		i++;
	}
	return (list_dir);
}

int		dir_management(char *dir_name, t_options options)
{
	t_list			*dir_list;

	dir_list =NULL;	
	if (!(dir_list = ft_read_stock_dir(dir_name, options)))
		return (0);	
	ft_current(&dir_list, dir_name, options);
	return (1);
}
