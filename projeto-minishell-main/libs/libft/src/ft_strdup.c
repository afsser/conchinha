/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 13:16:57 by lilmende          #+#    #+#             */
/*   Updated: 2024/11/29 19:44:09 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *s)
{
	char	*dst;

	dst = malloc(ft_strlen (s) + 1);
	if (dst == NULL)
		return (NULL);
	ft_strlcpy(dst, s, ft_strlen (s) + 1);
	return (dst);
}

char	*ft_strndup(const char *s, size_t n)
{
	char	*dst;

	dst = malloc(n + 1);
	if (!dst)
		return (NULL);
	ft_strlcpy(dst, s, n + 1);
	return (dst);
}
