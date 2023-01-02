/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 15:49:18 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "testcode.h"

/**
 * @brief 
 * 토큰화가 필요한 문자인지 검사한다.
 * @param c 
 * @return int 
 */
static int	is_valid_char(char c)
{
	return (c == '\'' || c == '"' || c == ' ' || c == '\\' || c == '$' \
			|| c == '|' || c == '&' || c == '>' || c == '<' \
			|| c == '(' || c == ')' || c == '\n' || c == ';');
}

/**
 * @brief 
 * 입력받은 line을 토큰화하여 연결 리스트에 담아낸다.
 * 한 글자씩 검사하여 토큰화가 필요한 문자가 발견되면
 * 현재까지 검사한 인덱스 정보와 토큰을 담아낼 구조체를
 * tokenize_line 함수에 인자로 전달한다.
 * @param input 
 * @return t_token* 
 */
t_token	*tokenizer(char *input)
{
	int		end_index;
	int		start_index;
	t_token	*token;

	end_index = 0;
	start_index = 0;
	token = NULL;
	while (input && input[end_index])
	{
		if (is_valid_char(input[end_index]))
		{
			end_index = tokenize_line(&token, input, start_index, end_index);
			start_index = end_index;
		}
		else
			end_index++;
	}
	return (token);
}
