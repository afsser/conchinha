/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lilmende <lilmende@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 15:28:11 by lilmende          #+#    #+#             */
/*   Updated: 2024/09/01 15:02:36 by lilmende         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*lstnew;
	t_list	*temp;
	void	*result;
	t_list	*new_element;

	lstnew = NULL;
	temp = lst;
	while (temp != NULL)
	{
		result = f(temp->content);
		if (result != NULL)
		{
			new_element = ft_lstnew(result);
			if (new_element != NULL)
				ft_lstadd_back(&lstnew, new_element);
			else
				del(result);
		}
		temp = temp->next;
	}
	return (lstnew);
}
