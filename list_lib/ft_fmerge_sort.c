/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fmerge_sort.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 17:57:32 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/16 16:39:30 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"
#include <stdlib.h>

static void		ft_part_list(t_flist *lst_start, t_flist **new_head)
{
	t_flist		*slow;
	t_flist		*fast;

	if (!(lst_start) || !(lst_start->next))
	{
		*new_head = NULL;
		return ;
	}
	slow = lst_start;
	fast = lst_start->next;
	while (fast)
	{
		fast = fast->next;
		if (fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
	}
	*new_head = slow->next;
	slow->next = NULL;
}

static t_flist	*ft_merge_list(t_flist *lst1, t_flist *lst2,
								int (*ft_cmp)(t_flist *, t_flist*), int flag)
{
	t_flist		*new_lst;

	if (!(lst1))
		return (lst2);
	if (!(lst2))
		return (lst1);
	if ((flag * ft_cmp(lst1, lst2)) > 0)
	{
		new_lst = lst1;
		new_lst->next = ft_merge_list(lst1->next, lst2, ft_cmp, flag);
	}
	else
	{
		new_lst = lst2;
		new_lst->next = ft_merge_list(lst1, lst2->next, ft_cmp, flag);
	}
	return (new_lst);
}

void			ft_fmerge_sort(t_flist **lst, int (*ft_cmp)(t_flist *, t_flist*)
																	, int flag)
{
	t_flist		*head;
	t_flist		*mid;

	if ((*lst) && ((*lst)->next))
	{
		head = *lst;
		ft_part_list(*lst, &mid);
		ft_fmerge_sort(&head, ft_cmp, flag);
		ft_fmerge_sort(&mid, ft_cmp, flag);
		*lst = ft_merge_list(head, mid, ft_cmp, flag);
	}
}
