/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:03:11 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:04:12 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlenc(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

size_t	ft_sbstr_count(const char *s, char c)
{
	size_t	num_substrings;
	size_t	i;

	num_substrings = 0;
	i = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			num_substrings++;
			while (s[i] && s[i] != c)
				i++;
		}
		else
			i++;
	}
	return (num_substrings);
}

char	**ft_split(char const *s, char c)
{
	size_t	num_substrings;
	char	**result;
	size_t	i;

	num_substrings = ft_sbstr_count(s, c);
	result = (char **)malloc((num_substrings + 1) * sizeof(char *));
	if (!result)
		return (NULL);
	i = 0;
	while (num_substrings > 0)
	{
		while (*s == c)
			s++;
		result[i] = ft_substr(s, 0, ft_strlenc(s, c));
		if (!result[i])
			return (NULL);
		s += ft_strlenc(s, c);
		i++;
		num_substrings--;
	}
	result[i] = NULL;
	return (result);
}
