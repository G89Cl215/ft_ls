/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 01:47:34 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 18:58:32 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"

void	ft_flistfree(t_flist **alst)
{
	t_flist	*next;

	while (alst && *alst)
	{
		next = (*alst)->next;
		ft_flistfreeone(alst);
		(*alst) = next;
	}
}
