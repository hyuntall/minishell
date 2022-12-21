#include "testcode.h"

void print_node(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s(%d)\t", tmp->value, tmp->type);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_parse_tree(t_parse_tree *parse_tree, int level)
{
	printf("level%d root(%d)\t", level, parse_tree->type);
	print_node(parse_tree->token);
	if (parse_tree->original)
		printf("\toriginal : %s\n", parse_tree->original);
	if (parse_tree->left)
		print_parse_tree(parse_tree->left, level + 1);
	if (parse_tree->right)
		print_parse_tree(parse_tree->right, level + 1);
}

void	print_tokenization_result(t_token *tokenization)
{
	printf(">>tokenization result<<\n");
	t_token *token = tokenization;
	while (token)
	{
		printf("arg: %10s type: %10d len: %10zu\n", token->value, token->type, ft_strlen(token->value));
		if (token->type == 3)
			printf("<======= $: %s ========>\n", process_dquote(token->value));
		token = token->next;
	}
}
