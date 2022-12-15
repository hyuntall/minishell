/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:44 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/15 15:55:53 by jiwonhan         ###   ########seoul.kr  */
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
#endif