#include "../includes/builtin.h"

static void	cd_print_error(char *folder)
{
	int			length;
	char		*message_to_print;
	const char	*message[2] = {"ERROR: cd: '", \
								"': file or directory does not exist"};

	length = ft_strlen(message[0]) + ft_strlen(folder) \
						+ ft_strlen(message[1]) + 1;
	message_to_print = malloc(length);
	ft_strlcpy(message_to_print, message[0], length);
	ft_strlcat(message_to_print, folder, length);
	ft_strlcat(message_to_print, message[1], length);
	ft_putendl_fd(message_to_print, 2);
	free(message_to_print);
}

static int	cd_aux(char **args, t_env *env_list, char **path)
{
	char	*home;

	*path = NULL;
	if (args[1] && args[2])
	{
		ft_putendl_fd("ERROR: cd: Too many arguments", 2);
		return (1);
	}
	home = ft_strdup(m_get_env(env_list, "HOME"));
	if (!home[0])
	{
		ft_putendl_fd("ERROR: cd: HOME not defined", 2);
		free(home);
		return (1);
	}
	if (args[1] == NULL)
		*path = m_get_env(env_list, "HOME");
	else if (ft_strchr(args[1], '~'))
		*path = ft_strjoin(home, args[1] + 1);
	else
		*path = ft_strdup(args[1]);
	free(home);
	return (0);
}

static int	cd_change_directory(char *path, t_env *env_list)
{
	char	*oldpwd;

	oldpwd = getcwd(NULL, 0);
	if (oldpwd == NULL)
		oldpwd = m_get_env(env_list, "PWD");
	if (chdir(path) == -1)
	{
		cd_print_error(path);
		free(path);
		free(oldpwd);
		return (1);
	}
	exp_update_or_add_env(&env_list, "OLDPWD", oldpwd);
	free(oldpwd);
	return (0);
}

int	ft_cd(char **args, t_env *env_list)
{
	char	*path;

	if (cd_aux(args, env_list, &path) == 1)
		return (1);
	if (cd_change_directory(path, env_list) == 1)
		return (1);
	if (args[1] != NULL)
		free(path);
	path = getcwd(NULL, 0);
	exp_update_or_add_env(&env_list, "PWD", path);
	free(path);
	return (0);
}
