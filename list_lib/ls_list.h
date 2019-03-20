/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:08:10 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/15 13:57:02 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LIST_H
# define LS_LIST_H

# include "../libft/option.h"
# include <dirent.h>

typedef struct				s_flist
{
	char					*file_name;
	struct s_flist			*next;
}							t_flist;

typedef struct				s_chained_dir
{
	char					*file_name;
	char					*path;
	unsigned char			type;
	struct s_chained_dir	*prev;
	struct s_chained_dir	*next;
}							t_reclist;

t_reclist					*ft_newdir_nod(char *path, struct dirent *filedata);
void						ft_relink(t_reclist *voyager, t_reclist *new_nod);
void						ft_revrelink(t_reclist *voyager,
															t_reclist *new_nod);
int							ft_free_t_reclist(t_reclist **lst);

t_flist						*ft_flistnew(char const *content);
void						ft_flstadd(t_flist **alst, t_flist *new_nod);
void						ft_flstadd_back(t_flist **alst, t_flist *new_back);
void						ft_reclistadd(t_reclist **alst, t_reclist *new_nod);
void						ft_flistfree(t_flist **alst);
void						ft_flistfreeone(t_flist **alst);
int							ft_sortparse(t_flist **dir_list, t_options option);

void						ft_recmerge_sort(t_reclist **lst,
						int (*ft_cmp)(t_reclist *, t_reclist*), int flag);
void						ft_fmerge_sort(t_flist **lst,
						int (*ft_cmp)(t_flist *, t_flist*), int flag);
int							ft_flist_time_cmp(t_flist *lst1, t_flist *lst2);
int							ft_reclist_time_cmp(t_reclist *lst1,
															t_reclist *lst2);
int							ft_flist_ascii_cmp(t_flist *lst1, t_flist *lst2);
int							ft_reclist_ascii_cmp(t_reclist *lst1,
															t_reclist *lst2);

#endif
