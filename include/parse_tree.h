/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:44 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/14 21:47:38 by hanjiwon         ###   ########.fr       */
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
void parse_token(t_parse_tree **parse_tree, t_token **head, t_parse_tree *prev_tree);
#endif