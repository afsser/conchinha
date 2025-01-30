#ifndef DEBUG_H
# define DEBUG_H

# define SPACES 4
# define CYAN "\033[36m"
# define RESET "\033[0m"

//Libs
# include "minishell.h"
# include "parser.h"
# include "tokenizer.h"
# include "ast.h"

//Structs
typedef struct s_token		t_token;
typedef struct s_var_types	t_var_types;
typedef struct s_env		t_env;
typedef struct s_tree		t_tree;

struct s_var_types
{
	char	*content;
	char	**command;
	int		type;
	int		index;
	t_tree	*left;
	t_tree	*right;
	t_tree	*parent;
};

//functions to debug
void	print_parsed_tokens(t_token **tokens);
void	print_tokens(t_token **tokens);
void	list_printer(t_token **parsed_list);
int		list_size(t_token **parsed_list);
void	print_parsed_command(t_token *parsed_list);
void	print_char_array(char **array);

#endif