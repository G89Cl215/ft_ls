/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:23:17 by baavril           #+#    #+#             */
/*   Updated: 2019/02/17 02:09:19 by tgouedar         ###   ########.fr       */
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

void			ft_display_file(t_list *voyager, t_options option)
{
	char		*file;

	if (voyager->content)
	{
		file = ((struct dirent*)(voyager->content))->d_name;
		if ((option.a) || *file != '.')
			(option.l) ? ft_longdisplay(voyager) : printf("%s\n", file);
	}
	//gestion de sortie d'erreur :file not found
	//else
}

uint8_t		ft_gettype(char *path, struct dirent **filedata)
{

	char			*file_name;
	DIR				*dirhandle;

	*filedata = NULL;
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
		return (0);
	while ((*filedata = readdir(dirhandle)))
	{
		if (!(ft_strcmp(file_name, (*filedata)->d_name)))
		{
			closedir(dirhandle);
			return ((*filedata)->d_type);
		}
	}
	closedir(dirhandle);
	return (0);
}

int			ft_parsing_dir(char **tab_dir, t_options option, t_list **dir_list)
{
	struct dirent	*dirdata;
	t_list			*file_list;
	t_list			*new_nod;
	int				i;
	int 			flag;
	uint8_t			type;

	i = 1;
	file_list = NULL;
	flag = (option.r) ? -1 : 1;
	if (!(tab_dir[i]))
		return (0);
	while (tab_dir[i])
	{
		type = ft_gettype(tab_dir[i], &dirdata);
		if (!(new_nod = ft_lstnew(dirdata, sizeof(*dirdata))))
			return (0);
		if (type == DT_REG)
		{
			if (!(file_list))
				file_list = new_nod;
			else
				(option.t) ? ft_sortins_time(&file_list, new_nod, flag)
					: ft_sortins_ascii(&file_list, new_nod, flag);
		}
		else
		{
			if (!(*dir_list))
				*dir_list = new_nod;
			else
				(option.t) ? ft_sortins_time(dir_list, new_nod, flag)
					: ft_sortins_ascii(dir_list, new_nod, flag);
		}
		i++;
	}
	flag = (*dir_list && (*dir_list)->next);
	flag = ((file_list)) ? 2 : flag;
	while (file_list)
	{
		new_nod = file_list;
		file_list = file_list->next;
		ft_display_file(new_nod, option);
		free(new_nod->content);
		free(new_nod);
	}
	return (flag);
}

int				dir_management(char *dir_name, t_options options, int flag)
{
	t_list	*dir_list;

	dir_list = NULL;
	if (!(dir_list = ft_read_stock_dir(dir_name, options)))
		return (0);
	if (flag == 1)
		printf("%s:\n", dir_name);
	else if (flag)
		printf("\n%s:\n", dir_name);
	ft_current(&dir_list, dir_name, options);
	return (1);
}
