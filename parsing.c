/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 12:23:17 by baavril           #+#    #+#             */
/*   Updated: 2019/03/13 21:45:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <limits.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft/libft.h"
#include "list_lib/ls_list.h"
#include <sys/acl.h>
#include <sys/xattr.h>

int				ft_gettype(char *to_parse)
{
	struct stat		file_stat;

	if (lstat(to_parse, &file_stat) == -1)
	{
		ft_printf("ft_ls: %s: No such file or directory\n", to_parse);
		return (0);
	}
	return (file_stat.st_mode & S_IFMT);
}

int				ft_link_target(char *to_parse)
{
	struct stat		file_stat;

	if (stat(to_parse, &file_stat) == -1)
	{
		perror("stat");
		return (0);
	}
	return (file_stat.st_mode & S_IFMT);
}

void			ft_parsing_display(t_flist *file_list, t_options option)
{
	t_flist			*tmp;
	struct stat		sb;

	if (ft_sortparse(&file_list, option))
		return ;
	tmp = file_list;
	if (((option.l) || (option.n) || (option.g) || (option.o)) && (tmp))
	{
		ft_get_file_stat(tmp->file_name, &sb);
		ft_update_padding(option, &sb);
		tmp = tmp->next;
	}
	while (file_list)
	{
		tmp = file_list;
		file_list = file_list->next;
		ft_parse_display(tmp->file_name, option);
		free(tmp->file_name);
		free(tmp);
	}
}

int				ft_parsing_dir(char **tab_dir, t_options option,
														t_flist **dir_list)
{
	t_flist			*file_list;
	t_flist			*new_nod;
	int				type;

	file_list = NULL;
	while (*tab_dir)
	{
		if (!(type = ft_gettype(*tab_dir)))
		{
			tab_dir++;
			continue ;
		}
		if (!(new_nod = ft_flistnew(*tab_dir)))
			return (0);
		if ((type == S_IFLNK) && !(option.l))
			type = ft_link_target(*tab_dir);
		if (type == S_IFDIR)
			ft_flistadd(dir_list, new_nod);
		else
			ft_flistadd(&file_list, new_nod);
		tab_dir++;
	}
	type = ((file_list)) ? 2 : (*dir_list && (*dir_list)->next);
	ft_parsing_display(file_list, option);
	return (type);
}
