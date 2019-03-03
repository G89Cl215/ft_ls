/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   crisis_room.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/26 16:31:39 by baavril           #+#    #+#             */
/*   Updated: 2019/03/03 14:15:31 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <time.h>
#include <stdio.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>
#include "libft/libft.h"
#include "libft/option.h"
#include "ft_ls.h"

void	ft_file_not_found(char *path, char *file_name)
{
	if (ft_strcmp(".", path))
		printf("ft_ls: %s/%s: No such file or directory\n", path, file_name);
	else
		printf("ft_ls: %s: No such file or directory\n", file_name);
}
