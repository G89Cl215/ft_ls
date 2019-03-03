/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:14:17 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/03 17:18:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/option.h"
#include "ft_ls.h"

t_flist		*ft_create_new_nod(char *path, struct dirent *filedata, int flag)
{
	t_flist	*new_nod;

//	ft_printf("path: %s\n", path);
	if (!(new_nod = (t_flist*)ft_memalloc(sizeof(t_flist))))
		return (NULL);
	new_nod->flag = flag;
	if (filedata->d_type == DT_DIR || ft_strcmp(path, filedata->d_name))
	{
		if (!(new_nod->path = ft_strdup(path)))
			return (NULL);
	}
	else if (!(new_nod->path = ft_strdup(".")))
		return (NULL);
	if (!(new_nod->filedata = ft_memalloc(sizeof(struct dirent))))
		return (NULL);
	ft_memcpy(new_nod->filedata, filedata, sizeof(struct dirent));
	new_nod->prev = NULL;
	new_nod->next = NULL;
//	ft_printf("new_node:  %s\t%p\n", new_nod->path, new_nod);
	return (new_nod);
}

void		ft_relink(t_flist *voyager, t_flist *new_nod)
{
	new_nod->prev = voyager;
	new_nod->next = voyager->next;
	if (voyager->next)
		(voyager->next)->prev = new_nod;
	voyager->next = new_nod;
}

void		ft_revrelink(t_flist *voyager, t_flist *new_nod)
{
	new_nod->prev = voyager->prev;
	new_nod->next = voyager;
	if (voyager->prev)
		(voyager->prev)->next = new_nod;
	voyager->prev = new_nod;
}

int			ft_free_t_flist(t_flist **lst)
{
	t_flist	*voyager;

	if (!(lst))
		return (0);
	voyager = *lst;
	while (voyager)
	{
		free(voyager->filedata);
		free(voyager->path);
		voyager = voyager->next;
		free(*lst);
		*lst = voyager;
	}
	return (1);
}
