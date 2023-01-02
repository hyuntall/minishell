/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 16:09:54 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "lexer.h"

/**
 * @brief 
 * 입력받은 line을 토큰화하고, 구문 분석을 진행한다.
 * tokenizer: line 토큰화
 * line_token: 공백을 기준으로 일반 문자열로 해석되는 토큰끼리 연결
 * lexer: 구문 분석
 * @param minishell 히어독 정보를 담기 위한 미니쉘 구조체
 * @param input 입력받은 line
 * @return t_token* 
 */
t_token	*analize_line(t_minishell *minishell, char *input)
{
	t_token	*tokenized;
	t_token	*new_tokenized;

	if (!ft_strlen(input))
		return (NULL);
	input = ft_strjoin(input, "\n");
	tokenized = tokenizer(input);
	free(input);
	if (!tokenized)
		return (NULL);
	new_tokenized = link_token(minishell, tokenized);
	free_tokens(tokenized);
	if (lexer(minishell, new_tokenized) == FALSE)
	{
		minishell->status = 1;
		printf("minishell status 1\n");
		return (NULL);
	}
	return (new_tokenized);
}
