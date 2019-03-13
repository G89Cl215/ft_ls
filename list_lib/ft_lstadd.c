/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/14 15:36:59 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 18:55:28 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"

void	ft_flistadd(t_flist **alst, t_flist *new)
{
	new->next = *alst;
	*alst = new;
}