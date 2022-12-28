/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:42:41 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/27 18:19:35 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

#include "tokenization.h"

typedef enum e_lexer_type
{
    NOT_FIRST = PIPE | DPIP | DAND | PARENTHESIS_RIGHT
}t_lexer_type;

int lexer(t_minishell *minishell, t_token *token);
int check_first_token(t_token *token);
int check_parenthesis_lexer(t_token *token);
int check_right_parenthesis(t_token *token);
int matching_parenthesis(t_token *token);
int check_left_parenthesis(t_token *token);
int near_unexpected_token(t_token *token);

#endif