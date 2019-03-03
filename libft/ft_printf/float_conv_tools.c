/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conv_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 18:23:40 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/02 19:40:25 by tgouedar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_strsum_dec(char *str, char *to_add)
{
	int		ret;
	int		point_str;
	int		point_to_add;
	int		i;

	point_str = ft_indice('.', str);
	point_to_add = ft_indice('.', to_add);
	i = ft_strlen(to_add) - point_to_add - 1;
	ret = 0;
	while (i > 0)
	{
		ret += str[point_str + i] + to_add[point_to_add + i] - 2 * '0';
		str[point_str + i] = (ret % 10) + '0';
		ret = (ret > 9 ? 1 : 0);
		i--;
	}
	i = point_to_add - 1;
	while (i >= 0)
	{
		ret += str[--point_str] + to_add[i--] - 2 * '0';
		str[point_str] = (ret % 10) + '0';
		ret = (ret > 9 ? 1 : 0);
	}
	if (ret)
		str[--point_str] = ret % 10 + '0';
}

void	ft_strdiv_2(char *str)
{
	int		i;
	int		len;
	int		ret;
	int		div;

	i = 0;
	len = ft_strlen(str);
	ret = 0;
	while ((str[i] == '0' || str[i] == '.') && i < len)
		i++;
	while (i < len)
	{
		if (str[i] != '.')
		{
			div = str[i] - '0';
			str[i] = div / 2 + ret + '0';
			ret = div % 2 ? 5 : 0;
		}
		i++;
	}
}

void	ft_trim_0(char *str, int s)
{
	int i;

	i = ft_strspn(str, "0");
	if (str[i] == '.')
		i--;
	if (s)
		i--;
	if (i > 0)
		ft_memmove(str, str + i, ft_strlen(str + i) + 1);
	if (s)
		str[0] = '-';
}

char	*ft_create_float(t_ull mant, int mant_length)
{
	char	*str;
	char	*pow_2;

	if (!(str = ft_strnew(10000))
			|| !(pow_2 = ft_strnew(114)))
	{
		ft_memdel((void**)&str);
		return (NULL);
	}
	ft_memset(str, '0', 10000);
	ft_memset(pow_2, '0', 114);
	str[5000] = '.';
	pow_2[0] = '1';
	pow_2[1] = '.';
	while (mant_length >= 0)
	{
		mant_length--;
		if (((t_ull)1 << mant_length) & mant)
			ft_strsum_dec(str, pow_2);
		ft_strdiv_2(pow_2);
	}
	free(pow_2);
	return (str);
}

/*
** Cette fonction renvoie l'exposant en notation scientifique
** et travaille sur le float contenu dans le char* pour le ramener
** en notation scientifique
*/

int		ft_reajust_zero(char *str)
{
	int		i;
	int		j;
	int		s;

	i = ft_strspn(str, "-0");
	s = (str[i] == '.' ? -1 : 1);
	if (s > 0 && (j = ft_indice('.', str)))
	{
		if (j != 1)
		{
			ft_memmove(str + j, str + j + 1, ft_strlen(str) - j);
			ft_memmove(str + i + 1, str + i, ft_strlen(str + i));
			str[i + 1] = '.';
		}
		j -= i;
	}
	else if ((j = i + ft_strspn(str + i + 1, "0") + 1))
	{
		if ((t_ul)j == ft_strlen(str))
			return (0);
		str[0] = str[j];
		str[1] = '.';
		ft_memmove(str + 2, str + j + 1, ft_strlen(str + j));
	}
	return (s * --j);
}
