/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstfree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/14 01:47:34 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/14 08:01:05 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstfree(t_list **alst)
{
	t_list	*next;

	while (alst && *alst)
	{
		next = (*alst)->next;
		ft_lstfreeone(alst);
		(*alst) = next;
	}
}
