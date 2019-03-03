/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   padding_floats.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 19:42:05 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 20:24:21 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void
	ft_prec_float(char *str, int prec)
{
	int		point_str;
	int		ret;

	if (prec < 0)
		prec = 6;
	if ((point_str = ft_indice('.', str)) == (int)ft_strlen(str))
		return ;
	ret = (str[point_str + prec + 1] - '0' > 4);
	if (!(prec))
		point_str--;
	str[point_str + prec + 1] = '\0';
	while (ret && (point_str + prec) >= 0)
	{
		if (str[point_str + prec] == '.')
			prec--;
		ret += str[point_str + prec] - '0';
		str[point_str + prec] = (ret % 10) + '0';
		ret = (ret > 9 ? 1 : 0);
		prec--;
	}
	if ((ret) && (point_str + prec) < 0)
	{
		ft_memmove(str + 1, str, ft_strlen(str) + 1);
		str[0] = ret + '0';
	}
}

inline static void
	ft_exp_increment2(char *str, int ret, int exp_str, int flag)
{
	int len;

	len = ft_strlen(str) - 1;
	while ((ret) && len > exp_str)
	{
		ret += str[len] - '0';
		str[len--] = (ret + 10) % 10 + '0';
		if (flag == -1)
			ret = ((ret + 10) == 9 ? -1 : 0);
		if (flag == 1)
			ret = (ret > 9 ? 1 : 0);
		if (str[len - 1] == '-'
		&& str[len] == '0' && str[len + 1] == '0')
			str[len - 1] = '+';
	}
	if (str[len - 2] == '-' && str[len - 1] == '1'
			&& str[len] == '0' && str[len + 1] == '9')
	{
		str[len - 1] = '9';
		str[len] = '9';
		str[len + 1] = '\0';
	}
}

inline static void
	ft_exp_increment(char *str)
{
	int		exp_str;
	int		len;
	int		ret;
	int		flag;

	len = (int)ft_strlen(str) - 1;
	if ((exp_str = ft_indice('e', str)) == len)
		exp_str = ft_indice('E', str);
	ret = str[++exp_str] == '-' ? -1 : 1;
	flag = str[++exp_str] == '-' ? -1 : 1;
	ft_exp_increment2(str, ret, exp_str, flag);
	if ((ret) && len == exp_str)
	{
		ft_memmove(str + exp_str + 1, str + exp_str, len - exp_str + 1);
		if (str[len] == '9' && str[len + 1] == '9' && str[len - 1] == '+')
		{
			str[len] = '1';
			str[len + 1] = '0';
			ft_strcat(str, "0");
		}
		else
			str[exp_str + 1] = ret + '0';
	}
}

static void
	ft_overflow_unite_prec_scient(char *str, int prec, int len)
{
	ft_memmove(str + 2, str, len + 1);
	str[2] = str[0];
	str[0] = '1';
	str[1] = '.';
	ft_exp_increment(str);
	ft_prec_scient(str, prec);
}

void
	ft_prec_scient(char *str, int prec)
{
	int		point;
	int		e;
	int		len;
	int		ret;

	prec = (prec < 0) ? 6 : prec;
	len = (int)ft_strlen(str);
	if ((t_ul)(e = ft_indice('e', str)) == (t_ul)len)
		e = ft_indice('E', str);
	if (e == len)
		return ;
	point = (prec) ? prec + 2 : 1;
	ret = (prec) ? ((str[point] - '0') > 4) : ((str[point + 1] - '0') > 4);
	ft_memmove(str + point, str + e, len - e + 1);
	while ((ret) && point-- > 0)
	{
		(str[point] == '.') ? point-- : 1;
		str[point] = (ret + str[point] - '0') % 10 + '0';
		ret = ((str[point] == '0') && (ret)) ? 1 : 0;
	}
	if ((ret) && point < 0)
		ft_overflow_unite_prec_scient(str, prec, len);
}
