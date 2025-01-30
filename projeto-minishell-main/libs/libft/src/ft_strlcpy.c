/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/25 18:42:58 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:14:44 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	len;
	size_t	i;

	len = 0;
	i = 0;
	if (size > 0)
	{
		while (src[i] != '\0' && len < size - 1)
		{
			dst[i] = src[i];
			i++;
			len++;
		}
		dst[i] = '\0';
		return (ft_strlen(src));
	}
	else
		return (ft_strlen(src));
}
