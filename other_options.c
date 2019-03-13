/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/13 21:42:46 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 21:43:14 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void		ft_option_f(t_reclist *voyager, struct stat *sb)
{
	if (voyager->type == DT_DIR)
		ft_strcat(voyager->file_name, "/");
	if ((sb->st_mode & S_IFMT) == S_IFREG)
		ft_strcat(voyager->file_name, "*");
}
