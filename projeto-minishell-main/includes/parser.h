#ifndef PARSER_H
# define PARSER_H

// Libs
# include "minishell.h"
# include "tokenizer.h"
# include "debug.h"
# include "ast.h"

// Structs
typedef struct s_mini		t_mini;
typedef struct s_env_parse	t_env_parse;
typedef struct s_env		t_env;

struct s_env_parse
{
	char					*equal_sign;
	char					*name;
	char					*value;
	int						name_len;
};

struct s_env
{
	char					*name;
	char					*value;
	struct s_env			*prev;
	struct s_env			*next;
};

// Functions

char	*m_qts_and_expand(char *lexeme, t_mini *mini);
char	*m_get_env(t_env *env_list, const char *var_name);
void	m_free_env_list(t_env *env_list);
t_env	*m_create_env_list(char **envp);
t_env	*m_create_env_node(char *name, char *value);
void	m_add_node_env(t_env **head, t_env *new_node);

pid_t	m_get_pid(void); // função para expadir $$ -- não implementada
// função para setar e pegar o status do sinal ao chamar $?
char	*m_get_exit_status(t_mini *mini);
char	*m_clean_dollar(char *str, int *idx);
char	*m_get_expand_string(char *lexeme, t_mini *mini);
char	*ft_strjoin_free(char *s1, char *s2);
int		m_is_special_cases_dollar(char *lexeme);
char	*m_expansion_special_cases(char *dollar_position, t_mini *mini);
char	*m_process_after_dollar(char *dollar_position, t_mini *mini);

void	m_reorganize_tokens_if_redir(t_token **token_list);
void	m_add_post_redir_type(t_token **token_list);
int		m_is_redir(int token_type);

char	ft_is_quotes_type(char *lexeme, int *start, int *end);
char	**split_by_quotes(char *input);
char	*m_get_expand_split(char *lexeme, t_mini *mini);
char	*m_set_split_quotes(char *lexeme);
char	*m_clean_qts(char *lexeme);

#endif
