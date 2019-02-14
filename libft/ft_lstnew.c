/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 13:33:48 by baavril           #+#    #+#             */
/*   Updated: 2019/02/13 14:21:49 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

t_list	*ft_lstnew(void const *content, size_t content_size)
{
	t_list *o;

	if (!(o = (t_list*)malloc(sizeof(*o))))
		return (NULL);
	if (content == NULL)
	{
		o->content = NULL;
		o->content_size = 0;
	}
	else
	{
		if (!(o->content = ft_memalloc(content_size)))
			return (NULL);
		ft_memcpy(o->content, content, content_size);
		o->content_size = content_size;
	}
	o->next = NULL;
	return (o);
}
