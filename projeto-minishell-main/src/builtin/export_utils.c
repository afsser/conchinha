#include "../includes/builtin.h"

void	m_add_node_sorted(t_env **sorted, t_env *new_node)
{
	t_env	*current;

	if (!*sorted || ft_strcmp(new_node->name, (*sorted)->name) < 0)
	{
		new_node->next = *sorted;
		*sorted = new_node;
		return ;
	}
	current = *sorted;
	while (current->next && ft_strcmp(new_node->name, current->next->name) > 0)
	{
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
}

void	m_print_sorted_env(t_env *env_list)
{
	t_env	*sorted;
	t_env	*current;
	t_env	*new_node;
	t_env	*temp;

	sorted = NULL;
	current = env_list;
	while (current)
	{
		new_node = m_create_env_node(current->name, current->value);
		m_add_node_sorted(&sorted, new_node);
		current = current->next;
	}
	temp = sorted;
	while (temp)
	{
		if (temp->value)
			ft_printf("declare -x %s=\"%s\"\n", temp->name, temp->value);
		else
			ft_printf("declare -x %s\n", temp->name);
		temp = temp->next;
	}
	m_free_env_list(sorted);
}
