#include "../includes/tokenizer.h"

static void	m_syntax_error_msg(t_token	*current)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd("unexpected syntax error near token '", STDERR_FILENO);
	if (current->type == PIPE)
		ft_putendl_fd("|'", STDERR_FILENO);
	if (current->type == REDIR_IN)
		ft_putendl_fd("<'", STDERR_FILENO);
	if (current->type == REDIR_OUT)
		ft_putendl_fd(">'", STDERR_FILENO);
	if (current->type == REDIR_APPEND)
		ft_putendl_fd(">>'", STDERR_FILENO);
	if (current->type == REDIR_HEREDOC)
		ft_putendl_fd("<<'", STDERR_FILENO);
}

int	m_validate_tokens(t_token **tokens)
{
	t_token	*current;

	current = *tokens;
	while (current != NULL)
	{
		if ((m_is_redir(current->type) \
			&& (current->next == NULL || current->next->type != WORD)) \
			|| (current->type == PIPE && (current->next == NULL \
			|| (current->next->type != WORD \
			&& !m_is_redir(current->next->type)))))
		{
			m_syntax_error_msg(current);
			return (0);
		}
		if (current->type == PIPE && (current->prev == NULL \
			|| current->prev->type != WORD))
		{
			m_syntax_error_msg(current);
			return (0);
		}
		current = current->next;
	}
	m_add_post_redir_type(tokens);
	return (1);
}
