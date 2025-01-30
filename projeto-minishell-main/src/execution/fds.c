#include "../../includes/minishell.h"

void	m_init_redirect(t_redir *redir_fd)
{
	redir_fd->stdin_backup = dup(STDIN_FILENO);
	redir_fd->stdout_backup = dup(STDOUT_FILENO);
	redir_fd->stderr_backup = dup(STDERR_FILENO);
	redir_fd->current_fd = -1;
}

void	m_restore_redirect(t_redir *redir_fd)
{
	dup2(redir_fd->stdin_backup, STDIN_FILENO);
	dup2(redir_fd->stdout_backup, STDOUT_FILENO);
	dup2(redir_fd->stderr_backup, STDERR_FILENO);
	close(redir_fd->stdin_backup);
	close(redir_fd->stdout_backup);
	close(redir_fd->stderr_backup);
}

