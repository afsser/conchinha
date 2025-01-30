#include "../includes/parser.h"

static char	*proc_special_dollar(char **dollar_position, t_mini *mini)
{
	char	*expansion;

	expansion = m_expansion_special_cases(*dollar_position, mini);
	*dollar_position += 2;
	return (expansion);
}

static char	*proc_regular_dollar(char **dollar_position, t_env *env_list)
{
	char	*cleaned_lexeme;
	char	*expansion;
	int		idx;

	cleaned_lexeme = m_clean_dollar(*dollar_position, &idx);
	if (m_get_env(env_list, cleaned_lexeme))
		expansion = ft_strdup(m_get_env(env_list, cleaned_lexeme));
	else
		expansion = ft_strdup("");
	free(cleaned_lexeme);
	*dollar_position += idx;
	return (expansion);
}

static char	*add_text_before_next_dollar(char *result, char **dollar_position)
{
	char	*next_dollar;
	char	*text_before_next_dollar;
	char	*temp;

	next_dollar = ft_strchr(*dollar_position, '$');
	if (next_dollar)
	{
		text_before_next_dollar = ft_substr(*dollar_position, 0, \
			next_dollar - *dollar_position);
		temp = ft_strjoin(result, text_before_next_dollar);
		free(text_before_next_dollar);
		*dollar_position = next_dollar;
	}
	else
	{
		temp = ft_strjoin(result, *dollar_position);
		*dollar_position = NULL;
	}
	return (temp);
}

char	*m_process_after_dollar(char *dollar_position, t_mini *mini)
{
	char	*result;
	char	*expansion;
	char	*temp;

	result = ft_strdup("");
	while (dollar_position)
	{
		if (m_is_special_cases_dollar(dollar_position))
			expansion = proc_special_dollar(&dollar_position, mini);
		else
			expansion = proc_regular_dollar(&dollar_position, mini->env_list);
		temp = ft_strjoin(result, expansion);
		free(result);
		free(expansion);
		result = add_text_before_next_dollar(temp, &dollar_position);
		free(temp);
	}
	return (result);
}

char	*m_set_split_quotes(char *lexeme)
{
	char	**split;
	char	*result;
	char	*new_str;
	char	*temp;
	int		i;

	split = split_by_quotes(lexeme);
	result = ft_strdup("");
	i = 0;
	while (split[i])
	{
		new_str = m_clean_qts(split[i]);
		temp = ft_strjoin_free(result, new_str);
		result = temp;
		i++;
	}
	free(split);
	return (result);
}
