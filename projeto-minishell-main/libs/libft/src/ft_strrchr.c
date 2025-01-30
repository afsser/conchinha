/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:18:17 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:20:33 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char	*last;

	last = 0;
	while (*s != '\0')
	{
		if (*s == (unsigned char)c)
			last = s;
		s++;
	}
	if (c == '\0' || c == 1024)
		return ((char *)s);
	return ((char *)last);
}
