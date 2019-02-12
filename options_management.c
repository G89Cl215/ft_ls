/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:42:56 by baavril           #+#    #+#             */
/*   Updated: 2019/02/12 08:18:09 by tgouedar         ###   ########.fr       */
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


t_list	*ft_list_sort(t_list *dir_list)
{
	t_list *voyager;
	void	*tmp;

	voyager = dir_list;
	while (dir_list->next != NULL)
	{
		if (ft_strcmp((char*)(dir_list->content),
		(char*)(dir_list->next->content)) > 0)
		{
			tmp = dir_list->content;
			dir_list->content = dir_list->next->content;
			dir_list->next->content = tmp;
			dir_list = voyager;
		}
		else
			dir_list = dir_list->next;
	}
	dir_list = voyager;
	return (dir_list);
}

void	option_a(t_list *dir_list)
{
	t_list *voyager;

	voyager = ft_list_sort(dir_list);
	while (voyager)
	{
		printf("%s\n", (char*)voyager->content);
		voyager = voyager->next;
	}
}


