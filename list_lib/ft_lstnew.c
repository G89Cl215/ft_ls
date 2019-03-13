/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:33:48 by baavril           #+#    #+#             */
/*   Updated: 2019/03/13 17:09:47 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"
#include "../libft/libft.h"
#include <stdlib.h>

t_flist		*ft_flistnew(char const *file_name)
{
	t_flist *new;

	if (!(new = (t_flist*)malloc(sizeof(*new))))
		return (NULL);
	if (file_name == NULL)
		new->file_name = NULL;
	else if (!(new->file_name = ft_strdup(file_name)))
		return (NULL);
	new->next = NULL;
	return (new);
}
