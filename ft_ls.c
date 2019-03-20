/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:08:33 by baavril           #+#    #+#             */
/*   Updated: 2019/03/19 23:32:34 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "option.h"
#include "ft_ls.h"
#include "libft.h"

t_padlen	g_padlen = {.nlink = 0, .pwname = 0,
	.grname = 0, .size = 0, .size_min = 0, .size_maj = 0};

int	main(int argc, char **argv)
{
	t_options	options;
	t_flist		*parsing_list;
	t_flist		*tmp;
	int			flag;

	(void)argc;
	flag = 0;
	parsing_list = NULL;
	if (!(ft_option(&argv, &options)))
		return (1);
	if (!(flag = ft_parsing_dir(--argv, options, &parsing_list))
	&& !(parsing_list))
		return (dir_management(".", options, 0));
	tmp = parsing_list;
	while (tmp)
	{
		dir_management(tmp->file_name, options, flag);
		tmp = tmp->next;
		flag++;
	}
	ft_flistfree(&parsing_list);
	return (0);
}
