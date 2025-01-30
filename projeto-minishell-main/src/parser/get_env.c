#include "../includes/parser.h"

// criar nó de variável de ambiente
t_env	*m_create_env_node(char *name, char *value)
{
	t_env	*new_node;

	new_node = malloc(sizeof(t_env));
	if (!new_node)
		return (NULL);
	new_node->name = ft_strdup(name);
	if (!value)
		new_node->value = NULL;
	else
		new_node->value = ft_strdup(value);
	new_node->prev = NULL;
	new_node->next = NULL;
	return (new_node);
}

void	m_add_node_env(t_env **head, t_env *new_node)
{
	t_env	*temp;

	if (!*head)
		*head = new_node;
	else
	{
		temp = *head;
		while (temp->next)
			temp = temp->next;
		temp->next = new_node;
		new_node->prev = temp;
	}
}

// função para criar lista com envp
t_env	*m_create_env_list(char **envp)
{
	int			i;
	t_env		*env_list;
	t_env_parse	temp;
	t_env		*new_node;

	i = 0;
	env_list = NULL;
	while (envp[i])
	{
		temp.equal_sign = ft_strchr(envp[i], '=');
		if (temp.equal_sign)
		{
			temp.name_len = temp.equal_sign - envp[i];
			temp.name = ft_substr(envp[i], 0, temp.name_len);
			temp.value = ft_strdup(temp.equal_sign + 1);
			new_node = m_create_env_node(temp.name, temp.value);
			m_add_node_env(&env_list, new_node);
			free(temp.name);
			free(temp.value);
		}
		i++;
	}
	return (env_list);
}

// Função para encontrar uma variável na lista encadeada
char	*m_get_env(t_env *env_list, const char *var_name)
{
	t_env	*current;

	current = env_list;
	while (current)
	{
		if (ft_strcmp(current->name, var_name) == 0)
			return (current->value);
		current = current->next;
	}
	return (NULL);
}

void	m_free_env_list(t_env *env_list)
{
	t_env	*current;
	t_env	*next;

	current = env_list;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current->value);
		free(current);
		current = next;
	}
}
