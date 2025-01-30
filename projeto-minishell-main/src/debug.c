#include "../includes/debug.h"
#include "../includes/builtin.h"

int	list_size(t_token **parsed_list)
{
	int list_size;
	t_token *curr;

	list_size = 0;
	curr = *parsed_list;
	while (curr)
	{
		curr = curr->next;
		list_size++;
	}
	return (list_size);
}

// --debug
void	print_tokens(t_token **tokens)
{
	t_token	*current = *tokens;
	int		i = 0;

	while (current)
	{
		ft_printf("Token %i: %s (Type: %d)\n", i++, current->lexeme, current->type);
		current = current->next;
	}
}

// função para imprimir comandos parseados (parsed_list)
void	print_parsed_command(t_token *parsed_list)
{
	t_token	*current;
	int		i;

	current = parsed_list;
	while (current != NULL)
	{
		if (current->command != NULL)
		{
			i = 0;
			while (current->command[i] != NULL)
			{
				printf("Command: %s\n", current->command[i]);
				i++;
			}
		}
		current = current->next;
	}
}

// --debug
void	print_parsed_tokens(t_token **tokens)
{
	t_token *curr = *tokens;
	int position = 0;
	int x = 0;

	while (curr)
	{
		x = 0;
		if (curr->type == COMMAND)
		{
			while(x < curr->command_len)
			{
				fprintf(stderr, "| %2d  | %13s | %4d | %10p | %10p | %10p |\n", \
					position, curr->command[x], curr->type, curr->prev, curr, curr->next);
				// ft_printf("Parsed Token %i: %s (Type: %d)\n", position, current->command[x], current->type);
				x++;
			}
		}
		else
			fprintf(stderr, "| %2d  | %13s | %4d | %10p | %10p | %10p |\n", \
				position, curr->lexeme, curr->type, curr->prev, curr, curr->next);
			// ft_printf("Parsed Token %i: %s (Type: %d)\n", position, current->lexeme, current->type);
		position++;
		curr = curr->next;
	}
}

void	list_printer(t_token **parsed_list)
{
	int		parsed_list_len;
	// t_token	*curr;

	// curr = *parsed_list;
	parsed_list_len = list_size(parsed_list);
	fprintf(stderr, "List size: %d\n", parsed_list_len);
	fprintf(stderr, "List content:\n");
	fprintf(stderr, "|-----|---------------|------|------------|------------|------------|\n");
	fprintf(stderr, "| pos |    content    | type |    prev    |    curr    |    next    |\n");
	fprintf(stderr, "|-----|---------------|------|------------|------------|------------|\n");
	print_parsed_tokens(parsed_list);
	fprintf(stderr, "|-----|---------------|------|------------|------------|------------|\n\n");
	fflush(stderr);
}

// função para testar comandos builtin
// void	ft_debug_tests(t_mini *mini, t_token *parsed_list)
// {
// 	char **args;

// 	if (!parsed_list || !parsed_list->command)
// 		return ;
// 	args = parsed_list->command;
// 	if (ft_strcmp(parsed_list->command[0], "exit") == 0)
// 		m_exit(&mini);
// 	if (ft_strcmp(parsed_list->command[0], "env") == 0)
// 		m_env(mini->env_list);
// 	if (ft_strncmp(parsed_list->command[0], "echo", 4) == 0)
// 		ft_echo(args);
// 	if (ft_strcmp(parsed_list->command[0], "pwd") == 0)
// 		ft_pwd();
// 	if (ft_strncmp(parsed_list->command[0], "export", 6) == 0)
// 	{
// 		if (args[1])
// 			m_export(mini->env_list, args);
// 	}
// 	if (ft_strncmp(parsed_list->command[0], "unset", 5) == 0)
// 	{
// 		if (args[1])
// 			m_unset(mini->env_list, args);
// 	}
// }

void print_char_array(char **array) // debug
{
    int i = 0;
    while (array[i])
    {
        ft_printf("String %d: %s\n", i, array[i]);
        i++;
    }
}
