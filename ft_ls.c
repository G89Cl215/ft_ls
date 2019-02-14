/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/09 19:08:33 by baavril           #+#    #+#             */
/*   Updated: 2019/02/14 08:57:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"
#include "libft/libft.h"

int	main(int argc, char **argv)
{
	t_options	options;
	t_list		*parsing_list;
	t_list		*tmp;

	ft_option(argc, argv, &options);
	parsing_list = NULL;
	if (!(parsing_list = ft_parsing_dir(argv)))
		dir_management(".", options);
	while (parsing_list)
	{
		tmp = parsing_list;
		parsing_list = parsing_list->next;
		dir_management(tmp->content, options);
		free(tmp->content);
		free(tmp);
	}
	return (0);
}
