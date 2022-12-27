/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/23 20:30:05 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/27 18:01:23 by hyuncpar         ###   ########.fr       */
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
static int	is_redirection(t_token_type type)
{
	if (type == LEFT || type == RIGT || type == DLFT || type == DRGT)
		return (TRUE);
	return (FALSE);
}

static int	is_special_token(t_token_type type)
{
	if (type == LEFT || type == RIGT || type == DLFT || type == DRGT \
	|| type == PIPE || type == DPIP || type == DAND || type == NEW_LINE \
	|| type == PARENTHESIS_LEFT || type == PARENTHESIS_RIGHT)
		return (TRUE);
	return (FALSE);
}

static int	is_logical(t_token_type type)
{
	// bash에서는 PIPE, AND, OR 다음에 개행이면 추가 입력 받아야되게 나와서 일단 에러처리
	if (type == PIPE || type == DPIP || type == DAND || type == NEW_LINE)
		return (TRUE);
	return (FALSE);
}

int near_unexpected_token(t_token *token)
{
	// 리다이렉션 다음에 스페셜 토큰이면 오류 || 논리연산 다음에 논리연산이면 오류
	if ((is_redirection(token->type) && is_special_token(token->next->type)) \
	|| (is_logical(token->type) && is_logical (token->next->type)))
	{
		error_lexical(token, token->next->value);
		return (FALSE);
	}
	/*if (check_first_token(token) == FALSE)
        return (FALSE);*/
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
	while (token->type != NEW_LINE)
	{
		// PIPE, AND, OR이 연속으로 나오는 경우 => near_unexpected_token에 추가
		if (near_unexpected_token(token) == FALSE)
			return (FALSE);
		if (match_parenthesis_token(token) == FALSE)
			return (FALSE);
		token = token->next;
	}
	free(token->value);
	token->prev->next = NULL;
	return (TRUE);
}