#include "../../includes/minishell.h"

int	m_check_permissions(char *cmd_path)
{
	if (access(cmd_path, X_OK) == -1 \
	|| access(cmd_path, R_OK | W_OK) == -1)
	{
		ft_putstr_fd("minishell: permission denied: ", STDERR_FILENO);
		ft_putendl_fd(cmd_path, STDERR_FILENO);
		return (126);
	}
	return (0);
}
