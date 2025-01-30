/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 18:53:40 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:20:22 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	little_len;
	size_t	big_len;
	size_t	i;

	little_len = ft_strlen(little);
	big_len = ft_strlen(big);
	if (little_len == 0 || (char *)big == (char *)little)
		return ((char *)big);
	if (len < little_len || *big == '\0' || big_len == 0)
		return (NULL);
	i = 0;
	while (i <= len - little_len)
	{
		if (ft_strncmp(&big[i], little, little_len) == 0)
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
