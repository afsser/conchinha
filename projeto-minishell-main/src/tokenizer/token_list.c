#include "../includes/tokenizer.h"

void	free_cmd_array(char **command)
{
	int	i;

	i = 0;
	if (!command || !*command)
		return ;
	while (command[i])
	{
		free(command[i]);
		i++;
	}
	free(command);
}

void	m_free_tokens(t_token **tokens)
{
	t_token	*current;
	t_token	*next;

	if (tokens && *tokens)
	{
		current = *tokens;
		while (current != NULL)
		{
			next = current->next;
			if (current->lexeme)
				free(current->lexeme);
			if (current->command)
				free_cmd_array(current->command);
			free(current);
			current = next;
		}
		*tokens = NULL;
	}
}

t_token	*m_create_token(char *lexeme, int type)
{
	t_token	*token;

	token = ft_calloc(sizeof(t_token), 1);
	if (!token)
		return (NULL);
	if (lexeme)
	{
		token->lexeme = ft_strdup(lexeme);
		free(lexeme);
	}
	token->type = type;
	token->quote = -1;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

t_token	*m_find_last_token(t_token *token_ptr)
{
	if (!token_ptr)
	{
		ft_putendl_fd("Tokenization Error -> No last knot in the list", 2);
		return (NULL);
	}
	while (token_ptr->next != NULL)
		token_ptr = token_ptr->next;
	return (token_ptr);
}

void	m_add_token(t_token **token_list, t_token *new_token)
{
	t_token	*last_token;

	if (!(*token_list))
		*token_list = new_token;
	else
	{
		last_token = m_find_last_token(*token_list);
		last_token->next = new_token;
		new_token->prev = last_token;
	}
}
