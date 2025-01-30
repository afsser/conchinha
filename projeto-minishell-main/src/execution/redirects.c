#include "../../includes/minishell.h"

static int	m_execute_redir_in(t_tree *current, t_redir *redir_fd)
{
	if (current->type == REDIR_IN || current->type == REDIR_HEREDOC)
		redir_fd->current_fd = open(current->right->content, O_RDONLY);
	if (redir_fd->current_fd == -1)
	{
		perror("minishell: input redirection");
		m_restore_redirect(redir_fd);
		return (1);
	}
	if (dup2(redir_fd->current_fd, STDIN_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(redir_fd->current_fd);
		m_restore_redirect(redir_fd);
		return (1);
	}
	close(redir_fd->current_fd);
	return (0);
}

static int	m_execute_redir_out_append(t_tree *current, t_redir *redir_fd)
{
	if (current->type == REDIR_OUT)
	{
		redir_fd->current_fd = \
			open(current->right->content, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	}
	else if (current->type == REDIR_APPEND)
		redir_fd->current_fd = \
			open(current->right->content, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (redir_fd->current_fd == -1)
	{
		perror("minishell: output redirection");
		m_restore_redirect(redir_fd);
		return (1);
	}
	if (dup2(redir_fd->current_fd, STDOUT_FILENO) == -1)
	{
		perror("minishell: dup2 error");
		close(redir_fd->current_fd);
		m_restore_redirect(redir_fd);
		return (1);
	}
	close(redir_fd->current_fd);
	return (0);
}

t_tree	*m_find_command_node(t_tree *node)
{
	t_tree	*current;

	current = node;
	if (current->left)
	{
		while (current->left && current->type != COMMAND)
			current = current->left;
	}
	return (current);
}

int	m_execute_all_redirs(t_redir *redir_fd, t_tree *node)
{
	t_tree	*current;
	int		status;

	status = 0;
	m_init_redirect(redir_fd);
	current = m_find_command_node(node);
	if (current->type == COMMAND)
		current = current->parent;
	while (current && m_is_redir(current->type))
	{
		if (current->type == REDIR_IN)
			status = m_execute_redir_in(current, redir_fd);
		else if (current->type == REDIR_HEREDOC)
			status = m_execute_redir_in(current, redir_fd);
		else if (current->type == REDIR_OUT)
			status = m_execute_redir_out_append(current, redir_fd);
		else if (current->type == REDIR_APPEND)
			status = m_execute_redir_out_append(current, redir_fd);
		current = current->parent;
		if (status == 1)
			return (1);
	}
	return (0);
}

int	m_handle_redir(t_tree *node, t_mini *mini, t_redir *redir_fd)
{
	t_tree	*cmd_node;
	int		status;

	status = 0;
	if (m_execute_all_redirs(redir_fd, node))
	{
		m_restore_redirect(redir_fd);
		return (1);
	}
	cmd_node = m_find_command_node(node);
	if (cmd_node->type != COMMAND)
	{
		m_restore_redirect(redir_fd);
		if (g_signal_status == 256)
			return (256);
		return (1);
	}
	g_signal_status = 0;
	if (m_is_builtin(cmd_node) != -1)
		status = m_execute_builtin(cmd_node, mini);
	else
		status = m_simple_command(cmd_node, mini);
	m_restore_redirect(redir_fd);
	return (status);
}
