#include "../includes/parser.h"
#include "../includes/debug.h" //------ debug

static char	*extract_quoted_segment(char *input, int *index)
{
	char	id_quote;
	int		start;
	int		end;

	id_quote = ft_is_quotes_type(input + *index, &start, &end);
	if (id_quote)
	{
		start += *index;
		end += *index;
		*index = end + 1;
		return (ft_strndup(&input[start], end - start + 1));
	}
	return (NULL);
}

static char	*extract_plain_segment(char *input, int *index)
{
	int	start;

	start = *index;
	while (input[*index] && input[*index] != '\'' && input[*index] != '\"')
		(*index)++;
	if (*index > start)
		return (ft_strndup(&input[start], *index - start));
	return (NULL);
}

char	**split_by_quotes(char *input)
{
	char	*segment;
	char	**result;
	int		res_index;
	int		index;

	res_index = 0;
	index = 0;
	result = malloc(sizeof(char *) * (ft_strlen(input) / 2 + 2));
	if (!result)
		return (NULL);
	while (input[index])
	{
		if (input[index] == '\'' || input[index] == '\"')
			segment = extract_quoted_segment(input, &index);
		else
			segment = extract_plain_segment(input, &index);
		if (segment)
			result[res_index++] = segment;
	}
	result[res_index] = NULL;
	return (result);
}

static char	*m_handle_token(char *token, t_mini *mini)
{
	char	*dollar_position;

	dollar_position = ft_strchr(token, '$');
	if (!dollar_position)
		return (m_clean_qts(token));
	dollar_position++;
	if ((ft_strchr(token, '\'') && !ft_strchr(token, '\"')) \
		|| (ft_strchr(token, '\'') && ft_strchr(token, '\"') \
		&& token[0] == '\''))
		return (m_clean_qts(token));
	else if (ft_strchr(token, '\"') \
		&& (!ft_isalnum(*dollar_position) && *dollar_position != '_' \
		&& *dollar_position != '?' && *dollar_position != '$'))
		return (m_clean_qts(token));
	return (m_get_expand_string(token, mini));
}

char	*m_get_expand_split(char *lexeme, t_mini *mini)
{
	char	**split;
	char	*result;
	char	*new_expanded;
	char	*temp;
	int		i;

	split = split_by_quotes(lexeme);
	result = ft_strdup("");
	i = 0;
	while (split[i])
	{
		new_expanded = m_handle_token(split[i], mini);
		temp = ft_strjoin_free(result, new_expanded);
		result = temp;
		i++;
	}
	free(split);
	return (result);
}
