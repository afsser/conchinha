/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:22:39 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:39:24 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	ft_mod_plus(va_list ap, char s2)
{
	int			count;
	long int	n;

	count = 0;
	n = (long)va_arg(ap, int);
	if ((s2 == 'd' || s2 == 'i') && (n >= 0))
	{
		count += write(1, "+", 1);
		count += ft_print_nbr(n, 10, 0);
	}
	else
		count += ft_print_nbr(n, 10, 0);
	return (count);
}

int	ft_mod_has(va_list ap, char s2)
{
	int			count;
	long int	n;

	count = 0;
	n = (long)va_arg(ap, int);
	if (n == 0)
		return (count += write(1, "0", 1));
	else
	{
		count += write(1, "0", 1);
		count += write(1, &s2, 1);
		if (s2 == 'x')
			count += ft_print_nbr((unsigned int)n, 16, 0);
		else if (s2 == 'X')
			count += ft_print_nbr((unsigned int)n, 16, 1);
	}
	return (count);
}

int	ft_mod_spc(va_list ap, char s2)
{
	int			count;
	long int	n;

	count = 0;
	if (s2 == 'd' || s2 == 'i')
	{
		n = (long)va_arg(ap, int);
		if (n >= 0)
			count += write(1, " ", 1);
		count += ft_print_nbr(n, 10, 0);
	}
	else if (s2 == 's')
		count += ft_print_str(va_arg(ap, char *));
	return (count);
}
