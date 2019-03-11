/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ls_list.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 16:08:10 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/11 18:58:06 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LS_LIST_H
# define LS_LIST_H
# include "../libft/option.h"

typedef struct		s_flist
{
	char			*file_name;
	struct s_flist	*next;
}					t_flist;

typedef struct		s_chained_dir
{
	struct dirent			*filedata;
	char					*path;
	struct s_chained_dir	*prev;
	struct s_chained_dir	*next;
}					t_Rlist;

t_Rlist		*ft_newdir_nod(char *path, struct dirent *filedata);
void		ft_relink(t_Rlist *voyager, t_Rlist *new_nod);
void		ft_revrelink(t_Rlist *voyager, t_Rlist *new_nod);
int			ft_free_t_Rlist(t_Rlist **lst);

t_flist		*ft_flistnew(char const *content);
void		ft_flistadd(t_flist **alst, t_flist *new);
void		ft_flistadd_back(t_flist **alst, t_flist *new_back);
void		ft_flistfree(t_flist **alst);
void		ft_flistfreeone(t_flist **alst);
void		ft_sortparse(t_flist *new_nod, t_flist **dir_list, t_options option);


#endif
