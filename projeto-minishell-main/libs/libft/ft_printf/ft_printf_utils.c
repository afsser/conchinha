/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 11:47:25 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:39:19 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	ft_print_char(int c)
{
	return (write(1, &c, 1));
}

int	ft_print_str(char *str)
{
	int	count;

	count = 0;
	if (str == NULL)
		return (count + write(1, "(null)", 6));
	while (*str != '\0')
		count += ft_print_char((int)*str++);
	return (count);
}

int	ft_print_nbr(long int nbr, int base, int upper)
{
	int		count;
	char	*symbols;

	count = 0;
	if (nbr < 0)
	{
		count += write(1, "-", 1);
		return (count + ft_print_nbr(-nbr, base, upper));
	}
	else if (nbr < base)
	{
		if (upper == 1)
			symbols = "0123456789ABCDEF";
		else
			symbols = "0123456789abcdef";
		return (ft_print_char(symbols[nbr]));
	}
	else
	{
		count += ft_print_nbr(nbr / base, base, upper);
		return (count + ft_print_nbr(nbr % base, base, upper));
	}
}

int	ft_print_pnbr(unsigned long nbr, int base, int upper)
{
	int		count;
	char	*symbols;

	count = 0;
	if (nbr < (unsigned long)base)
	{
		if (upper == 1)
			symbols = "0123456789ABCDEF";
		else
			symbols = "0123456789abcdef";
		return (ft_print_char(symbols[nbr]));
	}
	else
	{
		count += ft_print_pnbr(nbr / base, base, upper);
		return (count + ft_print_pnbr(nbr % base, base, upper));
	}
}

int	ft_print_pointer(unsigned long p)
{
	unsigned long	c;

	c = 0;
	if (p == 0)
		c = write(1, "(nil)", 5);
	else
	{
		c += write(1, "0x", 2);
		c += ft_print_pnbr(p, 16, 0);
	}
	return (c);
}
