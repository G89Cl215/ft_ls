/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_revrelink.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 15:21:13 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 19:52:24 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"

void		ft_revrelink(t_Rlist *voyager, t_Rlist *new_nod)
{
	new_nod->prev = voyager->prev;
	new_nod->next = voyager;
	if (voyager->prev)
		(voyager->prev)->next = new_nod;
	voyager->prev = new_nod;
}
