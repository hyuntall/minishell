/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_normal.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:33:14 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 16:03:58 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "testcode.h"

int	is_special_symbol(char c)
{
	return (c == '\'' || c == '"' || c == ' ' || c == '\\' || c == '$' \
			|| c == '|' || c == '&' || c == '>' || c == '<' \
			|| c == '(' || c == ')');
}

/**
 * @brief 
 * quote 토큰화 함수
 * quote로 감싸진 문자열이 들어오면 quote 내부의 문자열을
 * quote 타입으로 토큰화한다.
 * @param token 
 * @param input 
 * @param i 
 * @param type 
 * @return int 
 */
int	tokenize_quote(t_token **token, char *input, int i, t_token_type type)
{
	int		size;
	char	c;

	if (type == QUOT)
		c = '\'';
	else
		c = '"';
	size = 0;
	while (input[i + size + 1] != c)
		size++;
	insert_token(token, init_token(ft_substr(input, ++i, size), type));
	i += size + 1;
	return (i);
}

/**
 * @brief 
 * space, back-slash, dollar 토큰화 함수
 * space의 경우 공백이 끝나는 부분까지 전부 하나의 토큰으로 토큰화한다.
 * back-slash의 경우 백슬래시 다음에 오는 하나의 문자만 토큰한다.
 * dollar의 경우, 뒤에 공백이 오거나 특별한 토큰이 오기 전까지 검사하여 토큰화한다.
 * 단, dollar 바로 뒤에 공백이거나 아무것도 없을 경우 normal 토큰으로 취급한다.
 * @param token 
 * @param input 
 * @param i 
 * @param type 
 * @return int 
 */
int	tokenize_etc(t_token **token, char *input, int i, int type)
{
	int		size;

	size = 1;
	if (type == SPCE)
		while (input[i + size] == ' ')
			size++;
	else if (type == BSLH)
		i++;
	else if (type == DOLR)
	{
		i++;
		while (input[i + size] && !is_special_symbol(input[i + size]))
			size++;
		if (size == 1)
		{
			insert_token(token, init_token(ft_strdup("$"), NORM));
			return (++i);
		}
		size--;
	}
	insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}
