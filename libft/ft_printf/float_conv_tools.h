/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_conv_tools.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgouedar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/18 21:26:30 by tgouedar          #+#    #+#             */
/*   Updated: 2019/02/08 15:31:57 by baavril          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_CONV_TOOLS_H
# define FLOAT_CONV_TOOLS_H

/*
** input given by va_arg
** floating point type represented as 3 sections
** of unsigned word (size 1, 2, 4, 8 bytes) :
** float = 4 bytes
** double = 8 bytes
** First section single bit for sign.
** Second is exponent of base 2
** Third = mantissa : significatn digits, in binary.
** main problem in printing float = base conversion.
** to solve : optimization division and modulo in 64 bits.
** trick to convert base properly : where the unit
** (where the radix to the power 0, where the floating point is positioned) =
**	point in a floating point number is the fundamental limit.
** left side of the point handed by itoa_base protocol.
** right side, fractional part, weirder :
** example ->
**	powers = 5 in base 10 for negative powers of 2 (1/2 = 0.5, 1/4 = 0.25).
** float strings : implement your own "bigint" type and all basic
** operations using both uint arrays and/or strings of digits in a given base
**	for as speedy and accurate arbitrary precision arithmetic.
** %e (exponential/scientific notation) and %f (decimal point notation).
*/

void	ft_strsum_dec(char *str, char *to_add);
void	ft_strdiv_2(char *str);
void	ft_trim_0(char *str, int s);
char	*ft_create_float(t_ull mant, int mant_length);
int		ft_reajust_zero(char *str);

#endif
