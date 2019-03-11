/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_data.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/09 16:20:59 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/09 16:22:19 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXTRACT_DATA_H
# define EXTRACT_DATA_H

void	ft_get_file_stats(char *file_name, struct stat *file_stat);
void	ft_get_stats(t_Rlist *voyager, struct stat *file_stat);

#endif
