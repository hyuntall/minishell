#include "minishell.h"
#include "cmd.h"
#include "parse_tree.h"
#include "tokenization.h"

void	print_node(t_token *token);
void	print_parse_tree(t_parse_tree *parse_tree, int level);
void	print_tokenization_result(t_token *tokenization);