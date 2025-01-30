#include "../includes/minishell.h"

volatile sig_atomic_t	g_signal_status = 0;

void	m_close_fds(t_mini *mini)
{
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
	close(mini->backup_fd_in);
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	t_mini	mini;

	init_minishell(&mini, envp);
	while (1)
	{
		g_signal_status = 0;
		update_mini(&mini);
		mini.line = readline("minishell> ");
		if (m_is_input_null(&mini))
			break ;
		m_minishell_on(&mini);
	}
	m_close_fds(&mini);
	rl_clear_history();
	m_free_env_list(mini.env_list);
	return (mini.exit_status);
}
