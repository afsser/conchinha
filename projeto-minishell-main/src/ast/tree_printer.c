#include "../includes/debug.h"

static void	print_tree(t_tree *root, int distance);

void	visualize_tree(t_tree *root)
{
	ft_printf(CYAN "Tree visualization:\n\n\n" RESET);
	print_tree(root, 0);
	ft_printf("\n\n");
}

static void	print_tree(t_tree *root, int distance)
{
	if (root == NULL)
		return ;
	distance += SPACES;
	print_tree(root->right, distance);
	print_right_branch(distance + 2, root->right);
	print_item(root, distance);
	print_left_branch(distance + 2, root->left);
	print_tree(root->left, distance);
}

void	print_distance(int distance)
{
	for (int i = SPACES; i < distance; i++)
		ft_printf(" ");
}

void	print_right_branch(int distance, t_tree *right)
{
	if (!right)
		return ;
	print_distance(distance);
	ft_printf("/\n");
}

void	print_left_branch(int distance, t_tree *left)
{
	if (!left)
		return ;
	print_distance(distance);
	ft_printf("\\\n");
}

void	print_item(t_tree *this_node, int distance)
{
	int	i;

	i = 0;
	print_distance(distance);
	if (this_node->type == COMMAND && this_node->command)
	{
		while (this_node->command_len)
		{
			ft_printf("%s ", this_node->command[i]);
			i++;
			this_node->command_len--;
		}
		ft_printf("\n");
	}
	else if (this_node->content)
		ft_printf("%s\n", this_node->content);
}
