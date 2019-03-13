/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_newdir_nod.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:11:28 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:25:10 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "ls_list.h"
#include "../libft/libft.h"

t_reclist		*ft_newdir_nod(char *path, struct dirent *filedata)
{
	t_reclist	*new_nod;

	if (!(new_nod = (t_reclist*)malloc(sizeof(t_reclist))))
		return (NULL);
	if (filedata->d_type == DT_DIR || ft_strcmp(path, filedata->d_name))
	{
		if (!(new_nod->path = ft_strdup(path)))
			return (NULL);
	}
	else if (!(new_nod->path = ft_strdup(".")))
		return (NULL);
	if (!(new_nod->file_name = ft_strdup(filedata->d_name)))
		return (NULL);
	new_nod->type = filedata->d_type;
	new_nod->prev = NULL;
	new_nod->next = NULL;
	return (new_nod);
}
