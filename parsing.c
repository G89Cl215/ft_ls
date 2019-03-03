/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:23:17 by baavril           #+#    #+#             */
/*   Updated: 2019/03/03 14:18:19 by tgouedar         ###   ########.fr       */
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

uint8_t	ft_gettype(char *to_parse, struct dirent **filedata, uint8_t flag)
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
	{
		ft_file_not_found(path, file_name);
		return (0);
	}
	while ((*filedata = readdir(dirhandle)))
	{
		if (!(ft_strcmp(file_name, (*filedata)->d_name)))
		{
			if ((*filedata)->d_type == DT_LNK && !(flag))
				ft_memmove(to_parse, path, ft_strlen(path) + 1);
			else if (((*filedata)->d_type == DT_DIR
			|| (*filedata)->d_type == DT_LNK) && file_name != to_parse)
				*(--file_name) = '/';
		//	ft_putendl(file_name);
		//	ft_putendl(to_parse);
			closedir(dirhandle);
			return ((*filedata)->d_type);
		}
	}
	closedir(dirhandle);
	ft_file_not_found(path, file_name);
	return (0);
}

int		ft_verif_slash(char *dir_name)

{
	int		len;

	if ((len = ft_strlen(dir_name) - 1)
	&& dir_name[len] == '/')
	{
		dir_name[len] = '\0';
		return (1);
	}
	return (0);
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

void		ft_get_root(uint8_t *type, struct dirent **filedata)
{
	DIR				*dirhandle;

	if (!(dirhandle = opendir("/")))
		return ;
	*filedata = readdir(dirhandle);
	*type = DT_DIR;
	closedir(dirhandle);
}

int		ft_parsing_dir(char **tab_dir, t_options option, t_flist **dir_list)
{
	struct dirent	*filedata;
	t_flist			*file_list;
	t_flist			*new_nod;
	uint8_t			type;
	uint8_t			flag;

	file_list = NULL;
	while (*tab_dir)
	{
		flag = ft_verif_slash(*tab_dir);
		if (!(ft_strcmp("/", *tab_dir)))
			ft_get_root(&type, &filedata);
		else if (!(type = ft_gettype(*tab_dir, &filedata, ((flag) || !(option.l)))))
		{
			tab_dir++;
			continue ;
		}
		if (!(new_nod = ft_create_new_nod(*(tab_dir++), filedata, flag)))
			return (0);
		if ((type == DT_DIR) || (type == DT_LNK && (flag == 1 || !(option.l))))
			ft_sortins(new_nod, dir_list, option);
		else
			ft_sortins(new_nod, &file_list, option);
//		ft_printf("parsing : %s, flag: %d\n", new_nod->path, flag);
	}
	type = ((file_list)) ? 2 : (*dir_list && (*dir_list)->next);
	ft_parsing_display(file_list, option);
//	ft_printf("%d\n", type);
	return (type);
}
