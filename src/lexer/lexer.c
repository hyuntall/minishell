/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:30:05 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/23 23:57:56 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "lexer.h"
#include "tokenization.h"

int check_first_token(t_token *token)
{
    if (token && (token->type == PIPE || token->type == DPIP \
         || token->type == DAND || token->type == PARENTHESIS_RIGHT))
    {
        error_lexical(token, token->value);
        return (FALSE);
    }
    return (TRUE);
}

int check_left_parenthesis(t_token *token)
{
    //left, right => word이면 error
    if (token->prev && token->prev->type == NORM \
        && token->next && token->next->type == NORM)
        return (FALSE);
    //left => 
    return (TRUE);
}

int matching_parenthesis(t_token *token)
{
    int cnt;

    cnt = 0;
    while (token)
    {
        if (token->type == PARENTHESIS_LEFT)
            ++cnt;
        else if (token->type == PARENTHESIS_RIGHT)
            --cnt;
        token = token->prev;
    }
    if (cnt < 0)
        return (FALSE);
    return (TRUE);
}

int check_right_parenthesis(t_token *token)
{
    if (matching_parenthesis(token) == FALSE)
        return (FALSE);
    return (TRUE);
}
int check_parenthesis_lexer(t_token *token)
{
    while (token)
    {
        if (token->type == PARENTHESIS_LEFT)
            if (check_left_parenthesis(token) == FALSE)
                return (FALSE);
        if (token->type == PARENTHESIS_RIGHT)
            if (check_right_parenthesis(token) == FALSE)
                return (FALSE);
        token = token->next;
    }
    return (TRUE);
}

int near_unexpected_token(t_token *token)
{
    if (check_first_token(token) == FALSE)
        return (FALSE);
    if (check_parenthesis_lexer(token) == FALSE)
        return (FALSE);
    return (TRUE);
}

int match_parenthesis_token(t_token *token)
{
    int cnt;

    cnt = 0;
    while (token)
    {
        if (token->type == PARENTHESIS_LEFT)
            ++cnt;
        else if (token->type == PARENTHESIS_RIGHT)
            --cnt;
        token = token->next;
    }
    if (cnt > 0)
    {
        not_match_token();
        return (FALSE);
    }
    return (TRUE);
}

int lexer(t_token *token)
 {
    // PIPE, AND, OR이 연속으로 나오는 경우 => near_unexpected_token에 추가
    if (near_unexpected_token(token) == FALSE)
        return (FALSE);
    if (match_parenthesis_token(token) == FALSE)
        return (FALSE);
    return (TRUE);
 }