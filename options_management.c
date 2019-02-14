/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   options_management.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/11 16:42:56 by baavril           #+#    #+#             */
/*   Updated: 2019/02/14 14:14:13 by tgouedar         ###   ########.fr       */
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

int		ft_print_new_dir(char *dir_name, t_list *voyager, t_options option)
{
	size_t	len_dir;
	size_t	len_add;
	char	*str;

	len_dir = ft_strlen(dir_name);
	len_add = ft_strlen(((struct dirent*)(voyager->content))->d_name);
	if (!(str = (char*)malloc(len_add + len_dir + 2))) //ce malloc fait des erreurs de contexte monstrueuses, ainsi que le printf qui suit
		return (0);
	str[0] = '\0';
	ft_strcat(str, dir_name);
	ft_strcat(str, "/");
	ft_strcat(str, ((struct dirent*)(voyager->content))->d_name);
	str[len_dir + len_add + 1] = '\0';
	printf("\n%s:\n", str); //ce printf
	dir_management(str, option);
	free(str);
	return (1);
}

int		ft_current(t_list **dir_list, char *dir_name, t_options option)
{
	t_list	*voyager;

	ft_display_file(dir_list, option);
	voyager = *dir_list;
	if (option.R)
	{
		while (voyager)
		{
			if ((((struct dirent*)(voyager->content))->d_type == DT_DIR) //ici il faut voir comment marchent les autres types de fichiers
			&& (ft_strcmp(((struct dirent*)(voyager->content))->d_name, "."))
			&& (ft_strcmp(((struct dirent*)(voyager->content))->d_name, ".."))
			&& (((option.a)
			|| *(((struct dirent*)(voyager->content))->d_name) != '.')))
				ft_print_new_dir(dir_name, voyager, option);
			voyager = voyager->next;
		}
	}
	ft_lstfree(dir_list);
	return (1);
}
