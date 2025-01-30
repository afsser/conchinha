#include "../../includes/minishell.h"

void	print_heredoc_message(t_hdoc *hdoc)
{
	char	*message[2];

	message[0] = "minishell: warning: here-document at line ";
	message[1] = "delimited by end-of-file (wanted `";
	ft_putstr_fd(message[0], STDERR_FILENO);
	ft_printf("%d ", hdoc->nb_line_del);
	// ft_putnbr_fd(mini->num_lines, STDERR_FILENO);
	ft_putstr_fd(message[1], STDERR_FILENO);
	ft_putstr_fd(hdoc->delimiter, STDERR_FILENO);
	ft_putstr_fd("')\n", STDERR_FILENO);
}

int	ft_create_file(const char *filename)
{
	int	fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0600);
	if (fd == -1)
		perror("Error creating temp file");
	return (fd);
}

int	heredoc_create_file(t_hdoc **hdoc)
{
	char	filename[256];
	char	*suffix;
	int		fd;

	if ((*hdoc)->suffix_doc == -1)
		(*hdoc)->suffix_doc = 0;
	suffix = ft_itoa((*hdoc)->suffix_doc);
	strcpy(filename, "heredoc");
	strcat(filename, suffix);
	free(suffix);
	fd = ft_create_file(filename);
	if (fd != -1)
		((*hdoc)->suffix_doc)++;
	if ((*hdoc)->filename)
		free((*hdoc)->filename);
	(*hdoc)->filename = ft_strdup(filename);
	return (fd);
}

char	*m_heredoc_get_delimiter(t_token *node, t_hdoc *hdoc)
{
	if (node == NULL || node->next == NULL)
		return (NULL);
	if (node->next->type == DELIMITER)
	{
		hdoc->nb_line_del = m_update_nb_lines(-1);
		ft_printf("delimiter: %s, n_line: %d\n", node->next->lexeme, hdoc->nb_line_del); // ---debug
		return (node->next->lexeme);
	}
	return (NULL);
}

void	m_sig_heredoc(int signal __attribute__((unused)))
{
	g_signal_status = 128 + SIGINT;
	m_update_nb_lines(1);
	ft_putendl_fd("", STDOUT_FILENO);
	close(STDIN_FILENO);
}

void	heredoc_signals(void)
{
	signal(SIGINT, m_sig_heredoc);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGPIPE, SIG_IGN);
}

int	m_init_heredoc(t_hdoc *hdoc, t_token *node)
{
	if (!hdoc)
	{
		perror("Error: hdoc is not initialized");
		return (1);
	}
	hdoc->exit_flag = 0;
	hdoc->history_block = NULL;
	hdoc->delimiter = m_heredoc_get_delimiter(node, hdoc);
	if (!hdoc->delimiter)
	{
		ft_putendl_fd("heredoc: syntax error", STDERR_FILENO);
		return (1);
	}
	hdoc->temp_fd = heredoc_create_file(&hdoc);
	if (hdoc->temp_fd == -1)
		return (1);
	heredoc_signals();
	return (0);
}

void	m_heredoc_update_node(t_token **node, t_hdoc *hdoc)
{
	if ((*node)->next->type == DELIMITER \
		&& ft_strcmp((*node)->next->lexeme, hdoc->delimiter) == 0)
	{
		free((*node)->next->lexeme);
		(*node)->next->lexeme = ft_strdup(hdoc->filename);
		// ft_printf("delimiter change. lexeme: %s\n", (*node)->next->lexeme); // ---debug
		g_signal_status = 256;
	}
}

int	m_heredoc( t_token **parsed_list, t_mini *mini)
{
	t_token	*current;
	t_hdoc	*hdoc;

	current = *parsed_list;
	while (current)
	{

		if (current->type == REDIR_HEREDOC)
		{
			hdoc = mini->hdoc;
			if (m_init_heredoc(hdoc, current))
				return (-1);
			m_aux_heredoc(hdoc, current, mini);
			if (mini->hdoc->exit_flag == 1)
				print_heredoc_message(hdoc);
			if (g_signal_status != 130)
				m_heredoc_update_node(&current, hdoc);
			close(hdoc->temp_fd);
			// ft_printf("heredoc: exec\n"); // ---debug
			m_exec_signals(1);
			if (g_signal_status == 130)
				return (-1);
		}
		current = current->next;
	}
	return (0);
}
