/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tree.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 17:44:44 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/09 17:54:53 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_TREE_H
# define PARSE_TREE_H

#include "minishell.h"

typedef struct s_parse_tree
{
	t_parse_tree	*up, *left, *right;
	t_token			*token;
	t_token_type	type;
	t_cmd_tbl		*tbl;	//TODO 
	char			*origin
}				t_parse_tree;

#endif