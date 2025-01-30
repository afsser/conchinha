#include "../includes/builtin.h"
#include "../includes/execution.h"

int	m_is_builtin(t_tree *tree_node)
{
	if (!tree_node || !tree_node->command)
		return (-1);
	if (ft_strcmp(tree_node->command[0], "echo") == 0)
		return (ECO);
	if (ft_strcmp(tree_node->command[0], "cd") == 0)
		return (CD);
	if (ft_strcmp(tree_node->command[0], "pwd") == 0)
		return (PWD);
	if (ft_strcmp(tree_node->command[0], "env") == 0)
		return (ENV);
	if (ft_strcmp(tree_node->command[0], "export") == 0)
		return (EXPORT);
	if (ft_strcmp(tree_node->command[0], "unset") == 0)
		return (UNSET);
	if (ft_strcmp(tree_node->command[0], "exit") == 0)
		return (EXIT);
	return (-1);
}

int	m_execute_builtin(t_tree *tree_node, t_mini *mini)
{
	char	**args;
	int		builtin;
	int		exit_status;

	args = tree_node->command;
	builtin = m_is_builtin(tree_node);
	if (builtin == -1)
		exit_status = 1;
	if (builtin == PWD)
		exit_status = ft_pwd();
	if (builtin == CD)
		exit_status = ft_cd(args, mini->env_list);
	if (builtin == ECO)
		exit_status = ft_echo(args);
	if (builtin == ENV)
		exit_status = m_env(mini->env_list);
	if (builtin == EXPORT)
		exit_status = m_export(mini->env_list, args);
	if (builtin == UNSET)
		exit_status = m_unset(mini->env_list, args);
	if (builtin == EXIT)
		exit_status = m_exit(&mini, args);
	return (exit_status);
}
