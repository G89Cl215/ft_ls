/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reclistadd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:38:26 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:38:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"

void		ft_reclistadd(t_reclist **alst, t_reclist *new_nod)
{
	if (!(*alst))
		*alst = new_nod;
	else
	{
		new_nod->next = *alst;
		*alst = new_nod;
	}
}
