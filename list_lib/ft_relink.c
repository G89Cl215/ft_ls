/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_relink.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:22:06 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:21:27 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"

void		ft_relink(t_reclist *voyager, t_reclist *new_nod)
{
	new_nod->prev = voyager;
	new_nod->next = voyager->next;
	if (voyager->next)
		(voyager->next)->prev = new_nod;
	voyager->next = new_nod;
}
