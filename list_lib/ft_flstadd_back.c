/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:21:10 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/15 13:56:51 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"

void	ft_flstadd_back(t_flist **alst, t_flist *new_back)
{
	t_flist	*voyager;

	if (!alst)
		return ;
	if (!(*alst))
		*alst = new_back;
	else
	{
		voyager = *alst;
		while (voyager->next)
			voyager = voyager->next;
		voyager->next = new_back;
	}
}
