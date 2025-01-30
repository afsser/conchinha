#include "../includes/parser.h"

static t_token	*m_find_last_arg(t_token *aux_list)
{
	t_token	*last_arg;

	last_arg = NULL;
	while (aux_list && aux_list->type == WORD)
	{
		last_arg = aux_list;
		aux_list = aux_list->next;
	}
	return (last_arg);
}

static t_token	*m_find_target_node(t_token *aux_list)
{
	t_token	*target_node;
	t_token	*tmp;

	tmp = aux_list;
	while (tmp && tmp->type != PIPE)
	{
		if (tmp->type == WORD && tmp->prev \
			&& (tmp->prev->type == DELIMITER \
			|| tmp->prev->type == FILENAME))
		{
			target_node = tmp;
			return (target_node);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

static void	m_relocate_word_node(t_token **token_list, t_token *front_node, \
	t_token *target_node)
{
	t_token	*next_node_front;

	target_node->prev->next = target_node->next;
	if (target_node->next)
		target_node->next->prev = target_node->prev;
	if (front_node->type != WORD && front_node == *token_list)
	{
		target_node->prev = (*token_list)->prev;
		if ((*token_list)->prev)
			(*token_list)->prev->next = target_node;
		target_node->next = front_node;
		front_node->prev = target_node;
		*token_list = target_node;
	}
	else
	{
		next_node_front = front_node->next;
		target_node->prev = front_node;
		target_node->next = next_node_front;
		front_node->next = target_node;
		target_node->next->prev = target_node;
	}
}

static t_token	**m_update_token_list_address(t_token **token_list, \
	t_token **new_address)
{
	*new_address = (*new_address)->next;
	token_list = new_address;
	return (token_list);
}

void	m_reorganize_tokens_if_redir(t_token **token_list)
{
	t_token	*aux_list;
	t_token	*front_node;
	t_token	*target_node;

	aux_list = *token_list;
	while (aux_list)
	{
		target_node = m_find_target_node(aux_list);
		if (aux_list->type != WORD \
			&& !m_is_redir(aux_list->type) && !target_node)
			break ;
		while (aux_list && aux_list->type != PIPE)
		{
			front_node = m_find_last_arg(*token_list);
			if (!front_node)
				front_node = *token_list;
			if (target_node)
				m_relocate_word_node(token_list, front_node, target_node);
			target_node = m_find_target_node(aux_list);
			aux_list = aux_list->next;
		}
		if (aux_list && aux_list->type == PIPE)
			token_list = m_update_token_list_address(token_list, &aux_list);
	}
}
