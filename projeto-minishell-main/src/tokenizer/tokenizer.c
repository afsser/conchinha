#include "../includes/tokenizer.h"

int	m_is_special_char(char c)
{
	return (c == '|' \
				|| c == '<' || c == '>' \
				|| c == '\'' || c == '\"');
}

int	m_get_token_type(int status)
{
	if (status == 41)
		return (PIPE);
	else if (status == 62)
		return (REDIR_IN);
	else if (status == 61)
		return (REDIR_HEREDOC);
	else if (status == 72)
		return (REDIR_OUT);
	else if (status == 71)
		return (REDIR_APPEND);
	else if (status == 81)
		return (WORD);
	else if (status == 82)
		return (WORD);
	else if (status == 83)
		return (WORD);
	else
		return (UNKNOWN);
}

void	m_get_new_token(t_automat *aut, t_token **token_list, char *input)
{
	t_token	*new_token;

	if (m_status_needs_backtrack(aut->status))
	{
		aut->lexeme_len--;
		aut->i--;
	}
	aut->token_type = m_get_token_type(aut->status);
	if (aut->token_type == WORD)
		aut->lexeme = ft_substr(input, \
						(aut->i - (aut->lexeme_len - 1)), aut->lexeme_len);
	else
		aut->lexeme = NULL;
	new_token = m_create_token(aut->lexeme, aut->token_type);
	m_add_token(token_list, new_token);
	aut->lexeme_len = 0;
	aut->status = 1;
}

t_token	**m_tokenize(t_token **token_list, char *input)
{
	t_automat	aut;

	ft_bzero(&aut, sizeof(t_automat));
	aut.str_len = ft_strlen(input);
	aut.status = 1;
	while (aut.i <= aut.str_len)
	{
		aut.status = m_get_next_status(aut.status, input[aut.i]);
		if (aut.status != 1)
			aut.lexeme_len++;
		if (aut.status == -1)
		{
			m_free_tokens(token_list);
			break ;
		}
		if (m_is_final_status(aut.status))
			m_get_new_token(&aut, token_list, input);
		aut.i++;
	}
	return (token_list);
}
