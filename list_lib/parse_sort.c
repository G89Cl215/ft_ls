/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/03 16:25:19 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 19:37:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "../libft/libft.h"
#include "ls_list.h"
#include "../ft_ls.h"

int			ft_sortparse(t_flist **dir_list, t_options option)
{
	int		flag;

	flag = (option.r) ? -1 : 1;
	if (!(*dir_list))
		return (0);
	else
		(option.t) ? ft_fmerge_sort(dir_list, &ft_flist_time_cmp, flag)
					: ft_fmerge_sort(dir_list, &ft_flist_ascii_cmp, flag);
	return (1);
}
