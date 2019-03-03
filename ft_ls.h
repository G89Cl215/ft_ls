/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:43:46 by baavril           #+#    #+#             */
/*   Updated: 2019/03/03 16:48:26 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

#include <dirent.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include "ft_ls.h"
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

#define MONTHS_LIMIT_INF -15811200
#define MONTHS_LIMIT_SUP 15811200

typedef struct		s_chained_file
{
	struct dirent			*filedata;
	char					*path;
	int						flag;
	struct s_chained_file	*prev;
	struct s_chained_file	*next;
}					t_flist;

typedef struct		s_padlen
{
	int		nlink;
	int		pwname;
	int		grname;
	int		size;
	int		size_min;
	int		size_maj;
}					t_padlen;

extern	t_padlen	g_padlen;

t_flist		*ft_read_stock_dir(char *dir_name, t_options option);
t_flist		*ft_stock_dir(struct dirent *dp, DIR *dir, t_flist *buff_list);
void		ft_sortins(t_flist *new_nod, t_flist **dir_list, t_options option);
void		ft_sortins_time(t_flist **lst_start, t_flist *to_sort, int flag);
void		ft_sortins_ascii(t_flist **lst_start, t_flist *to_sort);
int			ft_current(t_flist **dir_list, char *dir_name, t_options option);
int			ft_parsing_dir(char **av, t_options option, t_flist **dir_list);
int			dir_management(char *to_print, t_options options, int flag);
int			ft_central_opt_management(t_flist *dir_list, t_options options);
char		*ft_reconstruct_path(t_flist *voyager, int flag);
void		ft_display_file(t_flist *voyager, t_options option);
void		ft_longdisplay(t_flist *voyager, t_options option);
int			ft_print_new_dir(char *dir_name, char *next_dir, t_options option);

void		ft_get_stats(t_flist *voyager,  struct stat *file_stat);
void		ft_get_chmod(struct stat *sb, char *buf, t_flist *voyager);
char		ft_get_file_type(struct stat *sb);
void		ft_get_passwd(struct stat *sb, t_options option);
void		ft_get_group_name(struct stat *sb, t_options option);

void		ft_update_padding(t_flist *voyager, t_options option, struct stat *sb);

char		*ft_get_file(t_flist *voyager);

t_flist		*ft_create_new_nod(char *path, struct dirent *filedata, int flag);
void		ft_relink(t_flist *voyager, t_flist *new_nod);
void		ft_revrelink(t_flist *voyager, t_flist *new_nod);
int			ft_free_t_flist(t_flist **lst);

void		ft_file_not_found(char *path, char *file_name);

#endif
