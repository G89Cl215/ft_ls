/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:43:46 by baavril           #+#    #+#             */
/*   Updated: 2019/02/17 02:09:20 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include "libft/libft.h"

/*
** I. The options that we have to do.
** 
**	-l : List in long format. If the output is to a terminal, a total sum for
** all the file sizes is output on a line before the long listing.
**
**	-R : Recursively list subdirectories encountered.
**
**	-a : Include directory entries whose names begin with a dot (.).
**
**	-r : Reverse the order of the sort to get reverse lexicographical order or
**		the oldest entries first (or largest files last, if combined with sort
**		by size.
**
**	-t : Sort by time modified (most recently modified first) before sorting the
**		operands by lexicographical order.
**
** II. Bonus that could be done.
**
**	ACL : to check;
**
**	-u : Use time of last access, instead of last modification of the file for
**		sorting (-t) or long printing (-l).
**
**	-f : Output is not sorted.  This option turns on the -a option.
**
**	-g : This option is only available for compatibility with POSIX; it is used
**		to display the group name in the long (-l) format output (the owner name
**		is suppressed).
**
**	-d : Directories are listed as plain files (not searched recursively).
**
**	-G : Enable colorized output. This option is equivalent to defining CLICOLOR
**		in the environment.
**
*/

t_list		*ft_stock_dir(struct dirent *dp, DIR *dir, t_list *buff_list);
int			ft_current(t_list **dir_list, char *dir_name, t_options option);
int			ft_parsing_dir(char **tab_dir, t_options option, t_list **dir_list);
t_list		*ft_stock_dir(struct dirent *dp, DIR *dir, t_list *buff_list);
int			dir_management(char *dir_name, t_options options, int flag);
int			ft_central_opt_management(t_list *dir_list, t_options options);
t_list		*ft_read_stock_dir(char *dir_name, t_options option);
void		ft_sortins_time(t_list **lst_start, t_list *to_sort, int flag);
void		ft_sortins_ascii(t_list **lst_start, t_list *to_sort, int flag);
void		ft_longdisplay(t_list *voyager);
int			ft_print_new_dir(char *dir_name, char *next_dir, t_options option);






#endif
