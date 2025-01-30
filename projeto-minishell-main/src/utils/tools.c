#include "../../includes/minishell.h"

int	m_find_heredoc(t_token *parsed_list)
{
	t_token	*current;

	current = parsed_list;
	while (current)
	{
		if (current->type == REDIR_HEREDOC)
			return (1);
		current = current->next;
	}
	return (0);
}

int	m_handle_heredoc(t_token *parsed_list, t_mini *mini)
{
	if (!m_find_heredoc(parsed_list))
		return (0);
	if (m_heredoc(&parsed_list, mini) == -1 || g_signal_status == 130)
	{
		if (g_signal_status == 130)
			mini->exit_status = 130;
		else
			mini->exit_status = 1;
		m_free_tokens(&parsed_list);
		return (-1);
	}
	return (0);
}

t_token	*m_lexical_analysis(t_mini *mini)
{
	t_token	*token_list;
	t_token	*parsed_list;

	token_list = NULL;
	parsed_list = NULL;
	if (!m_check_line_input(mini->line))
		return (NULL);
	m_tokenize(&token_list, mini->line);
	if (token_list != NULL)
	{
		if (!m_validate_tokens(&token_list))
		{
			m_free_tokens(&token_list);
			return (NULL);
		}
	}
	m_parse_tokens(&token_list, &parsed_list, mini);
	m_free_tokens(&token_list);
	if (m_handle_heredoc(parsed_list, mini) == -1)
		return (NULL);
	return (parsed_list);
}
