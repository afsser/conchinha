/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 11:20:59 by lilmende          #+#    #+#             */
/*   Updated: 2024/10/10 13:38:06 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include "../../includes/libft.h"

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char	*ft_str_join(char *s1, char *s2);
char	*ft_strread(int fd, char *str);
char	*ft_get_line(char *str);
char	*ft_reserv(char *str);
char	*get_next_line(int fd);

#endif
