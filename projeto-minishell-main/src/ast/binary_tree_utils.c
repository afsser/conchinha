#include "../includes/ast.h"

void	m_tree_cleaner(t_tree *tree_node)
{
	if (tree_node)
	{
		m_tree_cleaner(tree_node->left);
		m_tree_cleaner(tree_node->right);
		if (tree_node->content)
			free(tree_node->content);
		if (tree_node->command)
			free_cmd_array(tree_node->command);
		free(tree_node);
		tree_node = NULL;
	}
}

void	m_grow_tree(t_tree *root, t_token **joint)
{
	t_token	*right;
	t_token	*left;

	right = NULL;
	left = NULL;
	if (!root || !*joint)
		return ;
	right = (*joint)->next;
	if (right)
		right->prev = NULL;
	if ((*joint)->prev)
		left = (*joint)->prev;
	if (left)
		left->next = NULL;
	root->type = (*joint)->type;
	if ((*joint)->lexeme)
		root->content = ft_strdup((*joint)->lexeme);
	root->right = m_tree_builder(right);
	root->left = m_tree_builder(left);
}
