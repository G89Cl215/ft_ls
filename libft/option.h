/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:50:56 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/19 23:32:00 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

# include <stdbool.h>
# define OPT "Raglnort1"

typedef struct	s_options
{
	bool		l : 1;
	bool		r : 1;
	bool		rec : 1;
	bool		a : 1;
	bool		t : 1;
	bool		n : 1;
	bool		e : 1;
	bool		g : 1;
	bool		o : 1;
}				t_options;

#endif
