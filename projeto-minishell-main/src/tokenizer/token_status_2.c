#include "../includes/tokenizer.h"

int	m_get_status_80(char c)
{
	if (c == '\'')
		return (81);
	else if (c == '\"')
		return (82);
	else if (m_is_special_char(c))
		return (83);
	else if (ft_isspace(c) || c == '\0')
		return (83);
	else if (!m_is_special_char(c))
		return (80);
	else
		return (-1);
}

int	m_get_status_81(char c)
{
	if (c == '\0')
		return (-1);
	else if (c == '\'')
		return (80);
	else if (c != '\'')
		return (81);
	else
		return (-1);
}

int	m_get_status_82(char c)
{
	if (c == '\0')
		return (-1);
	else if (c == '\"')
		return (80);
	else if (c != '\"')
		return (82);
	else
		return (-1);
}

int	m_status_needs_backtrack(int status)
{
	if (status == 41 \
			|| status == 62 \
			|| status == 72 \
			|| status == 83)
		return (1);
	return (0);
}

int	m_is_final_status(int status)
{
	return (status == 41
		|| status == 61 || status == 62 \
		|| status == 71 || status == 72 \
		|| status == 83);
}
