/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:36:45 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 15:55:51 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "testcode.h"

static int	is_normal_symbol(char c)
{
	return (c == '\'' || c == '"' || c == ' ' || c == '\\' || c == '$');
}

/**
 * @brief 
 * 일반 문자열로 해석되는 토큰으로 토큰화하는 함수
 * @param token 해당 문자열 구간을 토큰화하여 정보를 담아낼 구조체
 * @param input 첫 readline에서 입력받은 문자열
 * @param i 	현재 토큰화가 필요한 구간의 인덱스 정보
 * @return int 
 */
int	tokenize_normal(t_token **token, char *input, int i)
{
	if (input[i] == '\'')
		i = tokenize_quote(token, input, i, QUOT);
	else if (input[i] == '"')
		i = tokenize_quote(token, input, i, DQUT);
	else if (input[i] == ' ')
		i = tokenize_etc(token, input, i, SPCE);
	else if (input[i] == '\\')
		i = tokenize_etc(token, input, i, BSLH);
	else if (input[i] == '$')
		i = tokenize_etc(token, input, i, DOLR);
	return (i);
}

/**
 * @brief 
 * 특별한 연산이 필요한 토큰으로 토근화하는 함수
 * @param token 해당 문자열 구간을 토큰화하여 정보를 담아낼 구조체
 * @param input 첫 readline에서 입력받은 문자열
 * @param i 	현재 토큰화가 필요한 구간의 인덱스 정보
 * @return int 
 */
int	tokenize_special(t_token **token, char *input, int i)
{
	if (input[i] == '|')
		i = tokenize_oper(token, input, i, PIPE);
	else if (input[i] == '&')
		i = tokenize_oper(token, input, i, NORM);
	else if (input[i] == '>')
		i = tokenize_redir(token, input, i, RIGT);
	else if (input[i] == '<')
		i = tokenize_redir(token, input, i, LEFT);
	else if (input[i] == '(' || input[i] == ')' || input[i] == '\n')
		i = tokenize_prnth_or_newline(token, input, i);
	else if (input[i] == ';')
		i = tokenize_semicolon(token, input, i);
	return (i);
}

/**
 * @brief 
 * 토큰화가 필요한 문자가 발견되면, 그 전까지 토큰화 되지 않은 문자열은 normal 타입으로 토큰화한다.
 * 그 이후, 일반 문자열로 해석되는 토큰인지, 특별한 연산이 필요한 토큰인지 확인한다.
 * @param token 해당 문자열 구간을 토큰화하여 정보를 담아낼 구조체
 * @param input 첫 readline에서 입력받은 문자열
 * @param index 현재까지 토큰화가 완료된 구간의 인덱스 정보
 * @param i 	현재 토큰화가 필요한 구간의 인덱스 정보
 * @return int 
 */

int	tokenize_line(t_token **token, char *input, int index, int i)
{
	if (i - index)
		insert_token(token, \
		init_token(ft_substr(input, index, i - index), NORM));
	if (is_normal_symbol(input[i]))
		i = tokenize_normal(token, input, i);
	else
		i = tokenize_special(token, input, i);
	return (i);
}
