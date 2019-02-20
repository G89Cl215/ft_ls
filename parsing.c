/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:23:17 by baavril           #+#    #+#             */
/*   Updated: 2019/02/20 22:41:48 by tgouedar         ###   ########.fr       */
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

uint8_t	ft_gettype(char *to_parse, struct dirent **filedata)
{
	char			*path;
	char			*file_name;
	DIR				*dirhandle;

	*filedata = NULL;
	if (!(file_name = ft_strrchr(to_parse, '/')))
	{
		file_name = to_parse;
		path = ".";
	}
	else
	{
		*file_name = '\0';
		file_name++;
		path = (*to_parse) ? to_parse : "/";
	}
	if (!(dirhandle = opendir(path)))
		return (0);
	while ((*filedata = readdir(dirhandle)))
	{
		if (!(ft_strcmp(file_name, (*filedata)->d_name)))
		{
			closedir(dirhandle);
			if ((*filedata)->d_type == DT_DIR && file_name != to_parse)
				*(--file_name) = '/';
			return ((*filedata)->d_type);
		}
	}
	closedir(dirhandle); //ici : gestion plus fine des erreurs, sinon on affiche le dossier courant :/
	return (0);
}

void	ft_verif_slash(char *dir_name)
{
	int		len;

	len = ft_strlen(dir_name) - 1;
	if (dir_name[len] == '/')
		dir_name[len] = '\0';
}

void	ft_parsing_display(t_flist *file_list, t_options option)
{
	t_flist	*tmp;

	while (file_list)
	{
		tmp = file_list;
		file_list = file_list->next;
		ft_display_file(tmp, option);
		free(tmp->path);
		free(tmp->filedata);
		free(tmp);
	}
}
t_flist		*ft_create_new_nod(char *path, struct dirent *filedata)
{
	t_flist	*new_nod;

	if (!(new_nod = (t_flist*)malloc(sizeof(t_flist))))
		return (NULL);
	if (filedata->d_type == DT_DIR || ft_strcmp(path, filedata->d_name))
	{
		if (!(new_nod->path = strdup(path)))
			return (NULL);
	}
	else if (!(new_nod->path = strdup(".")))
		return (NULL);
	if (!(new_nod->filedata = ft_memalloc(sizeof(struct dirent))))
		return (NULL);
	ft_memcpy(new_nod->filedata, filedata, sizeof(struct dirent));
	new_nod->next = NULL;
	return (new_nod);
}

int		ft_parsing_dir(char **tab_dir, t_options option, t_flist **dir_list)
{
	struct dirent	*filedata;
	t_flist			*file_list;
	t_flist			*new_nod;
	uint8_t			type;

	file_list = NULL;
	while (*(++tab_dir))
	{
		ft_verif_slash(*tab_dir);
		if (!(type = ft_gettype(*tab_dir, &filedata)))
			continue ;
		if (!(new_nod = ft_create_new_nod(*tab_dir, filedata)))
			return (0);
		if (type != DT_DIR)
			ft_sortins(new_nod, &file_list, option);
		else if ((type))
			ft_sortins(new_nod, dir_list, option);
	}
	type = ((file_list)) ? 2 : (*dir_list && (*dir_list)->next);
	ft_parsing_display(file_list, option);
	return (type);
}

int		dir_management(char *dir_name, t_options options, int flag)
{
	t_flist	*dir_list;

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
