/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstclear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:11:44 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:02:06 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_lstclear(t_list **lst, void (*del)(void*))
{
	t_list	*temp;

	if (lst == NULL || *lst == NULL)
		return ;
	while (*lst != NULL)
	{
		temp = *lst;
		*lst = (*lst)->next;
		ft_lstdelone(temp, del);
	}
}
