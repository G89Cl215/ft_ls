/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/20 19:45:24 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/20 19:53:16 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

t_flist		*ft_create_new_nod(char *path, struct dirent *filedata)
{
	t_flist	*new_nod;

	if (!(new_nod = (t_flist*)malloc(sizeof(*o))))
		return (NULL);
	if ((ft_strcmp(path, filedata->d_name))
	&& !(new_nod->path = strdup(path)))
		return (NULL);
	else if (!(new_nod->path = strdup(".")))
		return (NULL);
	if (!(new_nod->filedata = ft_memalloc(sizeof(struct dirent))))
		return (NULL);
	ft_memcpy(new_nod->filedata, filedata, sizeof(struct dirent));
	new_nod->next = NULL;
	return (new_nod);
}
