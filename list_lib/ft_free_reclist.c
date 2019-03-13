/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_reclist.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:38:00 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:38:01 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ls_list.h"
#include "../libft/libft.h"

int			ft_free_t_reclist(t_reclist **lst)
{
	t_reclist	*voyager;

	if (!(lst))
		return (0);
	voyager = *lst;
	while (voyager)
	{
		free(voyager->file_name);
		free(voyager->path);
		voyager = voyager->next;
		free(*lst);
		*lst = voyager;
	}
	return (1);
}
