/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_Rlist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:23:16 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 15:24:21 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls_list.h"
#include "../libft/libft.h"

int			ft_free_t_Rlist(t_Rlist **lst)
{
	t_Rlist	*voyager;

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
