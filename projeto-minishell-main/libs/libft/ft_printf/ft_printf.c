/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/10 17:22:39 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:39:09 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/ft_printf.h"

int	ft_check(va_list ap, char c)
{
	int	count;

	count = 0;
	if (c == 'c')
		count += ft_print_char(va_arg(ap, int));
	else if (c == 's')
		count += ft_print_str(va_arg(ap, char *));
	else if (c == 'p')
		count += ft_print_pointer(va_arg(ap, unsigned long));
	else if (c == 'd' || c == 'i')
		count += ft_print_nbr((long)va_arg(ap, int), 10, 0);
	else if (c == 'u')
		count += ft_print_nbr((long)va_arg(ap, unsigned int), 10, 0);
	else if (c == 'x')
		count += ft_print_nbr((long)va_arg(ap, unsigned int), 16, 0);
	else if (c == 'X')
		count += ft_print_nbr((long)va_arg(ap, unsigned int), 16, 1);
	else if (c == '%')
		count += ft_print_char('%');
	else
		count += write(1, &c, 1);
	return (count);
}

int	ft_wth_mod(va_list ap, char s1, char s2)
{
	int	count;

	count = 0;
	if (s1 == '#')
		count += ft_mod_has(ap, s2);
	else if (s1 == ' ')
		count += ft_mod_spc(ap, s2);
	else if (s1 == '+')
		count += ft_mod_plus(ap, s2);
	return (count);
}

int	ft_mod(char c)
{
	if (c == ' ' || c == '+' || c == '#')
		return (1);
	return (0);
}

int	ft_printf(const char *s, ...)
{
	int		count;
	int		i;
	va_list	ap;

	count = 0;
	i = 0;
	if (!s)
		return (-1);
	va_start(ap, s);
	while (s[i] != '\0')
	{
		if (s[i] == '%' && ft_mod(s[i + 1]))
		{
			count += ft_wth_mod(ap, s[i + 1], s[i + 2]);
			i += 2;
		}
		else if (s[i] == '%' && !ft_mod(s[i + 1]))
			count += ft_check(ap, s[++i]);
		else
			count += write(1, &s[i], 1);
		i++;
	}
	va_end(ap);
	return (count);
}
