/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 19:52:43 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/16 12:49:46 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char		*tdst;
	const char	*tsrc;
	size_t		i;

	if (!dst && !src)
		return (0);
	tdst = (char *)dst;
	tsrc = (const char *)src;
	i = 0;
	while (i < n)
	{
		tdst[i] = tsrc[i];
		i++;
	}
	return (dst);
}
