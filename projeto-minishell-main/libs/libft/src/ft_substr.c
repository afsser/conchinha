/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/03 00:08:24 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:27:08 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*dst;

	if (start >= ft_strlen(s) || len == 0)
	{
		dst = malloc(1);
		dst[0] = '\0';
		return (dst);
	}
	if (len > ft_strlen(s) - start)
		len = ft_strlen(s) - start;
	dst = malloc(len + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s + start, len + 1);
	dst[len] = '\0';
	return (dst);
}
