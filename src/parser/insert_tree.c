#include "minishell.h"
#include "parse_tree.h"
#include "tokenization.h"

t_parse_tree *init_parse_tree(void)
{
	t_parse_tree *ret;

	ret = (t_parse_tree *)malloc(sizeof(t_parse_tree));
	ft_memset(ret, 0, sizeof(t_parse_tree));
	ret->type = NORM;
	return (ret);
}

void set_new_node(t_parse_tree *new_node, t_parse_tree *prev_tree, t_token *find)
{
	new_node->up = prev_tree;
	new_node->token = find;
	new_node->type = find->type;
}

static void	set_left_token(t_token *token, t_token *find)
{
	if (!token)
		return ;
	while (token && (token->next != find))
		token = token->next;
	if (token)
		token->next = NULL;
}

void get_left_node(t_parse_tree *parse_tree, t_token *token)
{
	parse_tree->left = init_parse_tree();
	parse_tree->left->up = parse_tree;
	parse_tree->left->token = get_head_token(token);
	if (parse_tree->left->token == token)	//token's prev == NULL
		parse_tree->left->token = NULL;
	parse_tree->left->type = NORM;
	set_left_token(parse_tree->left->token, token);	//left->token의 이후 연결 끊기
	token->prev = NULL;	//사용한 token 연결 끊기
}

void    get_right_node(t_parse_tree *parse_tree, t_token *token)
{
	parse_tree->right = init_parse_tree();
	parse_tree->right->up = parse_tree;
	parse_tree->right->token = token->next;
	parse_tree->right->token->prev = NULL;
	parse_tree->right->type = NORM;
	token->next = NULL;
}

void insert_tree(t_parse_tree **parse_tree, t_token *find, t_parse_tree *prev_tree)
{
	t_parse_tree    *new_tree;

	new_tree = init_parse_tree();   //new command 노드 만들어주기
	set_new_node(new_tree, prev_tree, find);    //new node에 이전 parse tree에 연결
	//new node의 left, right node 생성
	get_left_node(new_tree, find);
	get_right_node(new_tree, find);
	//parse tree를 new_node까지 반영하기
	if (parse_tree && *parse_tree)
	{
		free(*parse_tree);
		*parse_tree = NULL;
	}
	*parse_tree = new_tree;

}