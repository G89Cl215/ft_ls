/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_time_cmp.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 16:51:43 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:21:27 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"
#include "../libft/libft.h"
#include "../ft_ls.h"
#include <sys/stat.h>

int		ft_flist_ascii_cmp(t_flist *lst1, t_flist *lst2)
{
	return (ft_strcmp(lst1->file_name, lst2->file_name));
}

int		ft_reclist_ascii_cmp(t_reclist *lst1, t_reclist *lst2)
{
	return (ft_strcmp(lst1->file_name, lst2->file_name));
}
