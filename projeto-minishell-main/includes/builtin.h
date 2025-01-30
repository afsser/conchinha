#ifndef BUILTIN_H
# define BUILTIN_H

//Libs
# include "minishell.h"

# define INT_MIN -2147483648
# define INT_MAX  2147483647
# ifndef PATH_MAX
#  define PATH_MAX 4096
# endif

enum e_builtin
{
	NO_BUILTIN,
	PWD,
	CD,
	ECO,
	ENV,
	EXPORT,
	UNSET,
	EXIT
};

// functions builtins
int		ft_pwd(void);
int		ft_cd(char **args, t_env *env_list);
int		ft_echo(char **args);
int		m_env(t_env *env_list);
int		m_export(t_env *env_list, char **args);
int		m_unset(t_env *env_list, char **args);
int		m_exit(t_mini **mini, char **args);
int		m_is_builtin(t_tree *tree_node);
int		m_execute_builtin(t_tree *node, t_mini *mini);
void	m_print_sorted_env(t_env *env_list);
void	exp_update_or_add_env(t_env **env_list, char *name, char *value);

#endif
