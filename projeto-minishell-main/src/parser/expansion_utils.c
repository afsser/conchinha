#include "../includes/parser.h"

pid_t	m_get_pid(void)
{
	return (8888);
}

char	*m_get_exit_status(t_mini *mini)
{
	return (ft_itoa(mini->exit_status % 256));
}

char	*m_clean_dollar(char *str, int *idx)
{
	int		len;
	char	*var_name;

	len = 0;
	*idx = 0;
	while (str[len + 1] && (ft_isalnum(str[len + 1]) || str[len + 1] == '_'))
	{
		if (str[len + 1] == ' ' || str[len + 1] == '\"' || str[len + 1] == '$')
			break ;
		len++;
	}
	*idx = len + 1;
	var_name = ft_substr(str, 1, len);
	return (var_name);
}

char	*ft_strjoin_free(char *s1, char *s2)
{
	char	*result;

	result = ft_strjoin(s1, s2);
	if (s1)
		free(s1);
	if (s2)
		free(s2);
	return (result);
}
