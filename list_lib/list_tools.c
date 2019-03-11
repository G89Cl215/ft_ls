/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_tools.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 14:14:17 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 18:56:33 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdlib.h>
#include "ls_list.h"
#include "../libft/libft.h"

t_Rlist		*ft_newdir_nod(char *path, struct dirent *filedata)
{
	t_Rlist	*new_nod;

	if (!(new_nod = (t_Rlist*)ft_memalloc(sizeof(t_Rlist))))
		return (NULL);
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
	return (new_nod);
}
