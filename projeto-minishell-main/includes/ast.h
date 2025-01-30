#ifndef AST_H
# define AST_H

// Libs
# include "minishell.h"
# include "parser.h"
# include "tokenizer.h"

// Structs
typedef struct s_tree	t_tree;
typedef struct s_token	t_token;

// Structs
struct s_tree
{
	char				*content;
	char				**command;
	int					command_len;
	int					type;
	int					index;
	t_tree				*left;
	t_tree				*right;
	t_tree				*parent;
};

// Functions
t_tree	*m_binary_tree(t_tree *root, t_token **parsed_list);
void	m_grow_tree(t_tree *root, t_token **joint);
t_tree	*m_tree_builder(t_token *parsed_list);
void	m_tree_cleaner(t_tree *tree_node);
void	m_allocate_command(t_tree **root, t_token *parsed_list);
int		m_is_redir(int token_type);

//---------------------------------------------------------------------Debug
void	visualize_tree(t_tree *root);
void	print_item(t_tree *this_node, int distance);
void	print_left_branch(int distance, t_tree *left);
void	print_right_branch(int distance, t_tree *right);

#endif
