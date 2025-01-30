/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 17:03:29 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:15:24 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	u1;
	unsigned char	u2;

	i = 0;
	while (i < n)
	{
		if (s1[i] != s2[i])
		{
			u1 = (unsigned char)s1[i];
			u2 = (unsigned char)s2[i];
			if (u1 < u2)
				return (-1);
			else
				return (1);
		}
		if (s1[i] == '\0' || s2[i] == '\0')
			return (0);
		i++;
	}
	return (0);
}
