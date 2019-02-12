/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/15 13:12:10 by tgouedar          #+#    #+#             */
/*   Updated: 2018/11/15 16:13:23 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem))
{
	t_list	*new;
	t_list	*new_bot;

	if (lst)
	{
		if (!(new = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		new = (*f)(new);
		new_bot = new;
	}
	else
		return (NULL);
	while (lst->next)
	{
		lst = lst->next;
		if (!(new_bot = ft_lstnew(lst->content, lst->content_size)))
			return (NULL);
		new_bot = (*f)(new_bot);
		ft_lstadd_back(&new, new_bot);
	}
	return (new);
}
