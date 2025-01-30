/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 09:08:47 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:36:26 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/get_next_line.h"

char	*ft_str_join(char *str, char *buff)
{
	size_t	c;
	size_t	i;
	char	*new_str;

	if (!str)
	{
		str = (char *)malloc(sizeof(char));
		str[0] = '\0';
	}
	new_str = malloc(sizeof(char) * ((ft_strlen(str) + ft_strlen(buff)) + 1));
	if (new_str == NULL)
		return (NULL);
	c = -1;
	if (str)
		while (str[++c] != '\0')
			new_str[c] = str[c];
	i = 0;
	while (buff[i] != '\0')
		new_str[c++] = buff[i++];
	new_str[c] = '\0';
	free(str);
	return (new_str);
}
