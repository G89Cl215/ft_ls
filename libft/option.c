/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/17 16:50:46 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/14 08:51:53 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "option.h"
#include "libft.h"

int		ft_help(void)
{
	ft_putstr("les options legits sont : ");
	ft_putendl(OPT);
	return (0);
}

int		ft_usage(char *arg)
{
	while (*arg && ft_isin(*arg, OPT))
		arg++;
	ft_putstr("illegal option : ");
	ft_putchar(*arg);
	ft_putchar('\n');
	ft_putstr("usage : ");
	ft_help();
	return (0);
}

int		ft_fill_option(char *arg, t_options *options)
{
	arg++;
	while (*arg && ft_isin(*arg, OPT))
	{
		if (*arg == 'l')
			options->l = 1;
		if (*arg == 'R')
			options->R = 1;
		if (*arg == 'r')
			options->r = 1;
		if (*arg == 'a')
			options->a = 1;
		if (*arg == 't')
			options->t = 1;
		arg++;
	}
	if (*arg && !ft_isin(*arg, OPT))
		return (0);
	return (1);
}

int		ft_option(int ac, char **av, t_options *options)
{
	int		i;

	i = 1;
	options->t = 0;
	options->r = 0;
	options->R = 0;
	options->l = 0;
	options->a = 0;
	while (i < ac)
	{
		if (av[i][0] == '-')
			ft_fill_option(av[i], options);
		i++;
	}
	return (1);
}
