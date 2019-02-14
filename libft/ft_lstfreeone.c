/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfreeone.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 01:47:36 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/14 08:22:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	ft_lstfreeone(t_list **alst)
{
	if (alst && *alst)
	{
		free((*alst)->content);
		ft_memdel((void**)alst);
	}
}
