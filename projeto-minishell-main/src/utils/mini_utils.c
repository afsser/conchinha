#include "../../includes/minishell.h"

void	init_minishell(t_mini *mini, char **envp)
{
	ft_bzero(mini, sizeof(t_mini));
	mini->line = NULL;
	mini->num_lines = 0;
	mini->env_list = m_create_env_list(envp);
	mini->tree = NULL;
	mini->backup_fd_in = dup(STDIN_FILENO);
	tcgetattr(STDIN_FILENO, &mini->term);
	mini->hdoc = malloc(sizeof(t_hdoc));
	ft_bzero(mini->hdoc, sizeof(t_hdoc));
	mini->hdoc->temp_fd = 0;
	mini->hdoc->suffix_doc = -1;
	mini->hdoc->filename = NULL;
	m_update_nb_lines(0);
}

int	m_minishell_on(t_mini *mini)
{
	t_token	*parsed_list;

	if (g_signal_status == 130)
	{
		mini->exit_status = 130;
		g_signal_status = 0;
	}
	parsed_list = m_lexical_analysis(mini);
	if (!parsed_list)
	{
		if (g_signal_status == 130)
			mini->exit_status = 130;
		else
			mini->exit_status = 1;
		return (mini->exit_status);
	}
	mini->tree = m_binary_tree(mini->tree, &parsed_list);
	mini->exit_status = m_execution(mini->tree, mini);
	m_tree_cleaner(mini->tree);
	return (mini->exit_status);
}

int	m_update_nb_lines(int num)
{
	static int	nb_lines;

	if (num == -1)
		return (nb_lines);
	if (num == 0)
		nb_lines = num;
	else
		nb_lines += num;
	return (nb_lines);
}
