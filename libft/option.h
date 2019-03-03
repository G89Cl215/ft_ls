/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:50:56 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/24 18:51:40 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPTION_H
# define OPTION_H

#include <stdbool.h>

# define OPT "lrRatnegoF"

typedef struct s_options
{
	bool l : 1;
	bool r : 1;
	bool R : 1;
	bool a : 1;
	bool t : 1;
	bool n : 1;
	bool e : 1;
	bool g : 1;
	bool o : 1;
	bool F : 1;
}				t_options;

#endif
