#include "../../includes/minishell.h"

void	m_heredoc_delete_files(t_mini *mini)
{
	char	filename[256];
	char	*suffix;

	mini->hdoc->suffix_doc--;
	while (mini->hdoc->suffix_doc >= 0)
	{
		suffix = ft_itoa(mini->hdoc->suffix_doc);
		strcpy(filename, "heredoc");
		strcat(filename, suffix);
		free(suffix);
		if (unlink(filename) == 0)
			ft_printf("Deleted %s successfully.\n", filename); // ----- debug
		else
			perror("Error deleting file");
		mini->hdoc->suffix_doc--;
	}
}
