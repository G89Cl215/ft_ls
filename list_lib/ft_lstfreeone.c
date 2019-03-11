/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfreeone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 01:47:36 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 18:56:08 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"
#include "../libft/libft.h"
#include <stdlib.h>

void	ft_flistfreeone(t_flist **alst)
{
	if (alst && *alst)
	{
		free((*alst)->file_name);
		ft_memdel((void**)alst);
	}
}
