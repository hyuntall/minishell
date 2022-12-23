/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:42:41 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/23 23:19:10 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "tokenization.h"

typedef enum e_lexer_type
{
    NOT_FIRST = PIPE | DPIP | DAND | PARENTHESIS_RIGHT
}t_lexer_type;

int lexer(t_token *token);
int check_first_token(t_token *token);
int check_parenthesis_lexer(t_token *token);
int check_right_parenthesis(t_token *token);
int matching_parenthesis(t_token *token);
int check_left_parenthesis(t_token *token);

#endif