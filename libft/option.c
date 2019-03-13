/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:50:46 by tgouedar          #+#    #+#             */
/*   Updated: 2019/03/13 21:14:13 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "libft.h"

static int		ft_usage(void)
{
	ft_printf("usage: ./ft_ls [-%s] [file ...]", OPT);
	return (0);
}

static void		ft_taiga(char opt, t_options *options)
{
	if (opt == 'l')
		options->l = 1;
	if (opt == 'R')
		options->rec = 1;
	if (opt == 'r')
		options->r = 1;
	if (opt == 'a')
		options->a = 1;
	if (opt == 't')
		options->t = 1;
	if (opt == '1')
		options->e = 1;
	if (opt == 'n')
		options->n = 1;
	if (opt == 'g')
		options->g = 1;
	if (opt == 'o')
		options->o = 1;
	if (opt == 'F')
		options->f_acl = 1;
}

static int		ft_fill_option(char *arg, t_options *options)
{
	arg++;
	while (*arg && ft_isin(*arg, OPT))
	{
		ft_taiga(*arg, options);
		arg++;
	}
	if (*arg && !ft_isin(*arg, OPT))
		return (ft_usage());
	return (1);
}

int				ft_option(char ***av, t_options *options)
{
	options->t = 0;
	options->r = 0;
	options->rec = 0;
	options->l = 0;
	options->a = 0;
	options->e = 0;
	options->n = 0;
	options->g = 0;
	options->o = 0;
	options->f_acl = 0;
	(*av)++;
	while ((**av) && ***av == '-' && ((**av)[1]))
	{
		if (!(ft_fill_option(**av, options)))
			return (0);
		(*av)++;
	}
	return (1);
}
