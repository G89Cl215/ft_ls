/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recmerge_sort.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 20:38:54 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 20:40:03 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ls_list.h"
#include <stdlib.h>

static void			ft_part_list(t_reclist *lst_start, t_reclist **new_head)
{
	t_reclist		*slow;
	t_reclist		*fast;

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

static t_reclist	*ft_merge_list(t_reclist *lst1, t_reclist *lst2,
							int (*ft_cmp)(t_reclist *, t_reclist*), int flag)
{
	t_reclist		*new_lst;

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

void				ft_recmerge_sort(t_reclist **lst,
							int (*ft_cmp)(t_reclist *, t_reclist*), int flag)
{
	t_reclist		*head;
	t_reclist		*mid;

	if ((*lst) && ((*lst)->next))
	{
		head = *lst;
		ft_part_list(*lst, &mid);
		ft_recmerge_sort(&head, ft_cmp, flag);
		ft_recmerge_sort(&mid, ft_cmp, flag);
		*lst = ft_merge_list(head, mid, ft_cmp, flag);
	}
}
