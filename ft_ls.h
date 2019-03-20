/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: baavril <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/04 11:43:46 by baavril           #+#    #+#             */
/*   Updated: 2019/03/19 23:10:38 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include <dirent.h>
# include <sys/types.h>
# include <sys/stat.h>
# include "libft/option.h"
# include "list_lib/ls_list.h"

# define MONTHS_LIMIT_INF -15811200
# define MONTHS_LIMIT_SUP 15811200

typedef struct		s_padlen
{
	int				nlink;
	int				pwname;
	int				grname;
	int				size;
	int				size_min;
	int				size_maj;
}					t_padlen;

extern t_padlen		g_padlen;

t_reclist			*ft_read_stock_dir(char *dir_name, t_options option);
t_reclist			*ft_stock_dir(struct dirent *dp, DIR *dir,
														t_reclist *buff_list);
void				ft_sortins(t_reclist *new_nod, t_reclist **dir_list,
															t_options option);
int					ft_current(t_reclist **dir_list, char *dir_name,
															t_options option);
int					ft_parsing_dir(char **av, t_options option,
															t_flist **dir_list);
int					dir_management(char *to_print, t_options options, int flag);
int					ft_central_opt_management(t_reclist *dir_list,
															t_options option);
void				ft_display_file(t_reclist *voyager, t_options option);
void				ft_longdisplay(t_reclist *voyager, t_options option);
void				ft_parse_display(char *file_name, t_options option);
int					ft_print_new_dir(char *dir_name, char *next_dir,
															t_options option);

void				ft_get_stats(t_reclist *voyager, struct stat *file_stat);
void				ft_get_file_stat(char *file_name, struct stat *sb);
void				ft_get_chmod(struct stat *sb, char *buf,
															t_reclist *voyager);
char				ft_get_file_type(struct stat *sb);
void				ft_get_passwd(struct stat *sb, t_options option);
void				ft_get_group_name(struct stat *sb, t_options option);
void				ft_clock(struct stat *sb);

int					ft_update_padding(t_options option, struct stat *sb);

char				*ft_get_file(t_reclist *voyager);
int					ft_get_permission(char *dir_name);
int					ft_append_str(int str, int size);
int					ft_append_str2(char *str, int size);
void				ft_print_total(off_t total, int flag);

#endif
