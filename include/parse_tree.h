/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:44 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/16 18:23:11 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H

#include "tokenization.h"

typedef struct s_parse_tree t_parse_tree;

struct s_parse_tree
{
	t_parse_tree	*up;
	t_parse_tree	*left;
	t_parse_tree	*right;
	t_token			*token;
	t_token_type	type;
};

t_parse_tree *parser(t_token *tokenization);
void parse_token(t_parse_tree **parse_tree, t_token **tokenized, t_parse_tree *prev_tree);
t_parse_tree *init_parse_tree(void);
void set_new_node(t_parse_tree *new_node, t_parse_tree *prev_tree, t_token *find);
void get_left_node(t_parse_tree *parse_tree, t_token *token);
void insert_tree(t_parse_tree **parse_tree, t_token *find, t_parse_tree *prev_tree);
t_token *get_tail_token(t_token *token);
t_token *get_head_token(t_token *token);

void print_node(t_token *token);
void print_parse_tree(t_parse_tree *parse_tree, int level);
#endif