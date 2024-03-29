/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:47:20 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/28 16:16:20 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"
#include "tokenization.h"
#include "testcode.h"

int  find_head_from_tail(t_token *tail, t_token **find, t_token_type type)
{
	int parenthesis_cnt = 0;

	while (tail)
	{
		if (tail->type == PARENTHESIS_LEFT)
			++parenthesis_cnt;
		else if (tail->type == PARENTHESIS_RIGHT)
			--parenthesis_cnt;
		if ((tail->type == type) && !parenthesis_cnt)
		{
			*find = tail;
			return (TRUE);
		}
		tail = tail->prev;
	}
	*find = NULL;
	return (FALSE);
}

int  find_head_from_head(t_token *head, t_token **find, t_token_type type)
{
	int parenthesis_cnt = 0;

	while (head)
	{
		if (head->type == PARENTHESIS_LEFT)
			++parenthesis_cnt;
		else if (head->type == PARENTHESIS_RIGHT)
			--parenthesis_cnt;
		if ((head->type == type) && !parenthesis_cnt)
		{
			*find = head;
			return (TRUE);
		}
		head = head->next;
	}
	*find = NULL;
	return (FALSE);
}

static void go_left_node(t_parse_tree **parse_tree)
{
	t_token         *next_tail;
	t_parse_tree    *prev_tree;

	prev_tree = *parse_tree;
	parse_tree = &((*parse_tree)->left);
	next_tail = get_tail_token((*parse_tree)->token);
	parse_token(parse_tree, &next_tail, prev_tree);
}

static void go_right_node(t_parse_tree **parse_tree)
{
	t_token         *next_tail;
	t_parse_tree    *prev_tree;

	prev_tree = *parse_tree;
	parse_tree = &((*parse_tree)->right);
	next_tail = get_tail_token((*parse_tree)->token);
	parse_token(parse_tree, &next_tail, prev_tree);
}

void parse_token(t_parse_tree **parse_tree, t_token **tail, t_parse_tree *prev_tree)
{
	t_token *find;
	
	check_parenthesis(parse_tree, tail);
	if (find_head_from_tail(*tail, &find, DPIP) == TRUE || find_head_from_tail(*tail, &find, DAND) == TRUE) //logical == and or
		insert_tree(parse_tree, find, prev_tree);
	else if (find_head_from_tail(*tail, &find, PIPE) == TRUE)
		insert_tree(parse_tree, find, prev_tree);
	else if (find_head_from_tail(*tail, &find, SEMC) == TRUE || find_head_from_tail(*tail, &find, DSEM) == TRUE)
		insert_tree(parse_tree, find, prev_tree);
	else if (find_head_from_head((get_head_token(*tail)), &find, RIGT) == TRUE || find_head_from_head((get_head_token(*tail)), &find, DRGT) == TRUE \
			|| find_head_from_head((get_head_token(*tail)), &find, LEFT) == TRUE || find_head_from_head((get_head_token(*tail)), &find, DLFT) == TRUE)
		insert_tree(parse_tree, find, prev_tree);
	else if (!(*parse_tree) && *tail)
	{
		*parse_tree = init_parse_tree();
		(*parse_tree)->token = get_head_token(*tail);
		*tail = NULL;
		return ;
	}
	else
		return ;
	go_left_node(parse_tree);
	go_right_node(parse_tree);
}


t_parse_tree *parser(t_token *token)
{
	t_parse_tree	*parse_tree;
	t_token			*tail;
	
	parse_tree = NULL;
	tail = get_tail_token(token);
	parse_token(&parse_tree, &tail, NULL);
	return (parse_tree);
}
