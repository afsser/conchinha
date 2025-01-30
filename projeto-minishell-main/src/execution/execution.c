#include "../../includes/minishell.h"

void	m_free_everything(t_mini *mini)
{
	if (mini->line)
		free(mini->line);
	if (mini->env_list)
		m_free_env_list(mini->env_list);
	if (mini->tree)
		m_tree_cleaner(mini->tree);
	if (mini->hdoc->filename)
		free(mini->hdoc->filename);
	if (mini->hdoc)
		free(mini->hdoc);
	m_close_fds(mini);
}

int	is_directory(const char *path)
{
	struct stat	statbuf;

	if (stat(path, &statbuf) != 0)
		return (-1);
	return (S_ISDIR(statbuf.st_mode));
}

int	m_empty_cmd(void)
{
	ft_putendl_fd("minishell: command not found: ''", STDERR_FILENO);
	return (127);
}

int	m_validate_path(char *cmd_path, char **node_cmd, char **env)
{
	if (cmd_path == NULL)
	{
		ft_putstr_fd("minishell: command not found: ", STDERR_FILENO);
		ft_putendl_fd(node_cmd[0], STDERR_FILENO);
		free_cmd_array(env);
		return (127);
	}
	else if (is_directory(cmd_path) == 1)
	{
		ft_putstr_fd("minishell: ", STDERR_FILENO);
		ft_putstr_fd(cmd_path, STDERR_FILENO);
		ft_putendl_fd(" is a directory", STDERR_FILENO);
		free_cmd_array(env);
		return (126);
	}
	return (0);
}

int	m_execute_command(char **tree_node_cmd, t_mini *mini)
{
	int		status;
	char	*cmd_path;
	char	**env;

	status = 0;
	cmd_path = NULL;
	if (tree_node_cmd[0][0] == '\0')
		return (m_empty_cmd());
	env = m_env_list_to_array(mini->env_list);
	cmd_path = m_create_path(cmd_path, tree_node_cmd, env);
	status = m_validate_path(cmd_path, tree_node_cmd, env);
	if (status)
	{
		m_close_fds(mini);
		return (status);
	}
	else
	{
		if (execve(cmd_path, tree_node_cmd, env))
		{
			status = m_check_permissions(cmd_path);
			free(cmd_path);
			free_cmd_array(env);
			m_close_fds(mini);
			return (status);
		}
	}
	return (status);
}

int	m_sort_status(int status)
{
	if (WIFSIGNALED(status))
	{
		status = WTERMSIG(status);
		if (status == SIGINT)
			return (130);
		else if (status == SIGQUIT)
		{
			signal(SIGPIPE, SIG_IGN);
			return (131);
		}
	}
	else if (WIFEXITED(status))
		status = WEXITSTATUS(status);
	return (status);
}

int	m_simple_command(t_tree *node, t_mini *mini)
{
	pid_t	pid;
	int		status;

	pid = 0;
	status = -1;
	pid = fork();
	m_exec_signals(pid);
	if (pid == 0)
	{
		status = m_execute_command(node->command, mini);
		m_free_everything(mini);
		exit(status);
	}
	else
	{
		waitpid(pid, &status, 0);
		return (m_sort_status(status));
	}
	return (status);
}

int	m_exec_redir_command(t_tree *node, t_mini *mini)
{
	int	status;

	if (m_is_builtin(node) != -1)
	{
		status = m_execute_builtin(node, mini);
		ft_putendl_fd("minishell: builtin execution error", STDERR_FILENO);
		m_free_everything(mini);
		exit(status);
	}
	else
	{
		status = m_execute_command(node->command, mini);
		ft_putendl_fd("minishell: ext command execution error", STDERR_FILENO);
		exit(status);
	}
	return (status);
}

int	m_handle_fork_error(int *pipefd)
{
	close(pipefd[0]);
	close(pipefd[1]);
	return (1);
}

int	m_children_process(int *pipefd, t_tree *node, int pid_index, t_mini *mini)
{
	int	status;

	status = 0;
	if (pid_index == 0)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	else
	{
		close(pipefd[1]);
		dup2(pipefd[0], STDIN_FILENO);
		close(pipefd[0]);
	}
	status = m_execution(node, mini);
	m_free_everything(mini);
	exit(status);
}

int	m_fork_and_exec(int *pipefd, t_tree *node, int pid_index, t_mini *mini)
{
	pid_t	pid;

	pid = fork();
	if (pid < 0)
		return (-1);
	m_exec_signals(pid);
	if (pid == 0)
		m_children_process(pipefd, node, pid_index, mini);
	return (pid);
}

int	m_handle_pipe(t_tree *node, t_mini *mini)
{
	int		pipefd[2];
	int		status[2];
	pid_t	pid[2];

	if (!node || !node->left || !node->right)
		return (-1);
	if (pipe(pipefd) == -1)
	{
		ft_putendl_fd("minishell: pipe error", STDERR_FILENO);
		return (1);
	}
	pid[0] = m_fork_and_exec(pipefd, node->left, 0, mini);
	if (pid[0] < 0)
		return (m_handle_fork_error(pipefd));
	pid[1] = m_fork_and_exec(pipefd, node->right, 1, mini);
	if (pid[1] < 0)
		return (m_handle_fork_error(pipefd));
	close(pipefd[0]);
	close(pipefd[1]);
	waitpid(pid[0], &status[0], 0);
	waitpid(pid[1], &status[1], 0);
	status[1] = m_sort_status(status[1]);
	return (status[1]);
}

int	m_execution(t_tree *node, t_mini *mini)
{
	t_redir	redir_fd;
	int		exit_status;

	exit_status = 0;
	ft_bzero(&redir_fd, sizeof(t_redir));
	if ((node->type == COMMAND && m_is_builtin(node) == -1) && !node->parent)
		exit_status = m_simple_command(node, mini);
	else if (node->type == COMMAND && m_is_builtin(node) != -1)
		exit_status = m_execute_builtin(node, mini);
	else if (node->type == COMMAND)
		exit_status = m_execute_command(node->command, mini);
	else if (m_is_redir(node->type))
		exit_status = m_handle_redir(node, mini, &redir_fd);
	else if (node->type == PIPE)
		exit_status = m_handle_pipe(node, mini);
	if (g_signal_status == 130)
		exit_status = 130;
	return (exit_status);
}
