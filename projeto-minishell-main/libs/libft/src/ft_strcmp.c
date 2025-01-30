/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/04 18:38:52 by lilmende          #+#    #+#             */
/*   Updated: 2024/11/04 18:39:24 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	len1;
	size_t	len2;
	size_t	min_len;
	int		result;

	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 < len2)
		min_len = len1;
	else
		min_len = len2;
	result = ft_memcmp(s1, s2, min_len);
	if (result != 0)
		return (result);
	return (len1 - len2);
}
