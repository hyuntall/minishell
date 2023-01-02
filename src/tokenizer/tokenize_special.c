/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_special.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 15:36:01 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 16:06:58 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "testcode.h"

/**
 * @brief 
 * pipe와 and 기호 토큰화
 * 해당 기호가 2개 연속으로 나타날 경우, double pipe 혹은 double and로 토큰화한다.
 * @param token 
 * @param input 
 * @param i 
 * @param type 
 * @return int 
 */
int	tokenize_oper(t_token **token, char *input, int i, t_token_type type)
{
	int		size;
	int		d_oper;
	char	c ;

	size = 1;
	if (type == PIPE)
	{
		c = '|';
		d_oper = DPIP;
	}
	else
	{
		c = '&';
		d_oper = DAND;
	}
	if (input[i + size] == c)
		insert_token(token, init_token(ft_substr(input, i, ++size), d_oper));
	else
		insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}

/**
 * @brief 
 * 리다이렉션 토큰화
 * 해당 기호가 2개 연속으로 나타날 경우, double left 혹은 double right로 토큰화한다.
 * @param token 
 * @param input 
 * @param i 
 * @param type 
 * @return int 
 */
int	tokenize_redir(t_token **token, char *input, int i, int type)
{
	int		size;
	int		d_oper;
	char	c;

	size = 1;
	if (type == RIGT)
	{
		c = '>';
		d_oper = DRGT;
	}
	else
	{
		c = '<';
		d_oper = DLFT;
	}
	if (input[i + size] == c)
		insert_token(token, init_token(ft_substr(input, i, ++size), d_oper));
	else
		insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}

/**
 * @brief 
 * 세미콜론 토큰화
 * 해당 기호가 2개 연속으로 나타날 경우 더블 세미콜론으로 토큰화한다.
 * @param token 
 * @param input 
 * @param i 
 * @return int 
 */
int	tokenize_semicolon(t_token **token, char *input, int i)
{
	int		size;

	size = 1;
	if (input[i + size] == ';')
		insert_token(token, init_token(ft_substr(input, i, ++size), DSEM));
	else
		insert_token(token, init_token(ft_substr(input, i, size), SEMC));
	i += size;
	return (i);
}

/**
 * @brief 
 * 괄호 및 개행문자 토큰화
 * @param token 
 * @param input 
 * @param i 
 * @return int 
 */
int	tokenize_prnth_or_newline(t_token **token, char *input, int i)
{
	if (input[i] == ')')
		insert_token(token, init_token(ft_strdup(")"), PARENTHESIS_RIGHT));
	else if (input[i] == '(')
		insert_token(token, init_token(ft_strdup("("), PARENTHESIS_LEFT));
	else
		insert_token(token, init_token(ft_strdup("\n"), NEW_LINE));
	return (++i);
}
