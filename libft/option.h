/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:50:56 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/10 17:01:09 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

//# include "libft.h"

# define OPT "lrRat"

typedef struct s_options
{
	unsigned int l : 1;
	unsigned int r : 1;
	unsigned int R : 1;
	unsigned int a : 1;
	unsigned int t : 1;
}				t_options;

#endif
