#include "../../includes/minishell.h"

void	check_and_reset_num_lines(void)
{
	char		*message[3];
	int			nb_lines;
	// const long long int	safety_limit = LLONG_MAX - 1000;
	const int	safety_limit = INT_MAX - 1000;

	nb_lines = m_update_nb_lines(-1);
	message[0] = "minishell: warning: ";
	message[1] = "Number of lines is approaching the limit.";
	message[2] = " Resetting counter.\n";
	if (nb_lines >= safety_limit)
	{
		ft_putstr_fd(message[0], STDERR_FILENO);
		ft_putstr_fd(message[1], STDERR_FILENO);
		m_update_nb_lines(0);
	}
}

