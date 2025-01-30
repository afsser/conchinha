/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:22:10 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:36:12 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./includes/get_next_line.h"

char	*ft_strread(int fd, char *str)
{
	char	*temp_buf;
	int		b;

	temp_buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!temp_buf)
		return (NULL);
	b = 1;
	while (!ft_strchr(str, '\n'))
	{
		b = read(fd, temp_buf, BUFFER_SIZE);
		if (b < 0)
		{
			free(temp_buf);
			return (NULL);
		}
		if (b == 0)
			break ;
		temp_buf[b] = '\0';
		str = ft_str_join(str, temp_buf);
	}
	free(temp_buf);
	return (str);
}

char	*ft_get_line(char *str)
{
	char	*line;
	int		i;
	int		j;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	line = (char *)malloc(sizeof(char) * (i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = str[j];
		j++;
	}
	line[j] = '\0';
	return (line);
}

char	*ft_reserv(char *str)
{
	char	*reserv;
	int		i;
	int		c;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	reserv = (char *)malloc(sizeof(char) * ((ft_strlen(str) - i) + 1));
	if (!reserv)
		return (NULL);
	c = 0;
	while (str[i])
		reserv[c++] = str[i++];
	reserv[c] = '\0';
	free(str);
	return (reserv);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*tmp;
	static char	*str;

	if (BUFFER_SIZE <= 0 || fd < 0)
		return (0);
	tmp = ft_strread(fd, str);
	if (!tmp)
	{
		free(str);
		str = NULL;
		return (NULL);
	}
	str = tmp;
	line = ft_get_line(str);
	str = ft_reserv(str);
	return (line);
}
