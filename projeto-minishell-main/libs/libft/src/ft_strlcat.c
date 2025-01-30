/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 18:16:20 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:14:37 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining_space;
	size_t	to_copy;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (dst_len >= size)
		return (size + src_len);
	remaining_space = size - dst_len - 1;
	to_copy = src_len;
	if (to_copy > remaining_space)
		to_copy = remaining_space;
	ft_memmove(dst + dst_len, src, to_copy);
	dst[dst_len + to_copy] = '\0';
	return (dst_len + src_len);
}
