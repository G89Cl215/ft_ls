/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:23:17 by baavril           #+#    #+#             */
/*   Updated: 2019/02/14 14:22:45 by tgouedar         ###   ########.fr       */
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
/*
t_list		*get_wildcard_files(char *path, t_list *file_list)
{
	DIR				*dirhandle;
	char			*file_name;
	t_list			*file_list;
	t_list			*to_sort;
	int				slash_nbr;
	int				flag;

	flag = (option.r) ? -1 : 1;
	slash = ft_indice('/', path);
	if (slash_nbr == ft_strlen(path))
	{
		while ((filedata = readdir(dirhandle)))
		{
			if (match(path, filedata->d_name) && (filedata->d_type == DT_REG) //ici il faut voir comment marchent les autres types de fichiers
			&& !(to_sort = ft_lstnew(filedata, sizeof(*filedata))))
				return (NULL);
			if (!(file_list))
				file_list = to_sort;
			else
				(option.t) ? ft_sortins_time(&file_list, to_sort, flag) :
				ft_sortins_ascii(&file_list, to_sort, flag);
			return (file_list);
		}
	}
	else
	{
		(path + slash) = '\0';
		file_name = path + slash + 1;
	}
	return ();
}*/

t_list		*get_file(char *path)
{
	DIR				*dirhandle;
	struct dirent	*filedata;
	char			*file_name;

	dirhandle = NULL;
	filedata = NULL;
	if (!(file_name = ft_strrchr(path, (int)('*'))))
		return (get_wildcard_files(path, NULL));
	if (!(file_name = ft_strrchr(path, (int)('/'))))
	{
		file_name = path;
		path = ".";
	}
	else
	{
		*file_name = '\0';
		file_name++;
	}
	if (!(dirhandle = opendir(path)))
		return (NULL);
	while ((filedata = readdir(dirhandle)))
	{
		if (!(ft_strcmp(file_name, filedata->d_name)))
			break ;
	}
	return (to_sort = ft_lstnew(filedata, sizeof(*filedata)));
}

void			ft_display_file(t_list *voyager, t_options option)
{
	while (voyager)
	{
		if ((option.a) || *(file->d_name) != '.')
			!(option.l) ? printf("%s\n", file->d_name) : /*ft_longdisplay(file)*/
				printf("loooooong, loooooong, fiiiiiiile : %s\n", file->d_name);
	}
}

t_list			*ft_parsing_dir(char **tab_dir)
{
	t_list	*list_dir;
	t_list	*new_nod;
	int		i;
	int		j;

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

int				dir_management(char *dir_name, t_options options)
{
	t_list	*dir_list;

	file = NULL;
	dir_list = NULL;
	if (!(dir_list = ft_read_stock_dir(dir_name, options)))
	{
		if (!(dir_list = get_file(dir_name)))
			return (0);//gestion de sortie d'erreur :file not found
		ft_display_file(file, options);
		ft_lstfree(&dir_list);
		return (1);
	}	
	ft_current(&dir_list, dir_name, options);
	return (1);
}
