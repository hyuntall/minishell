/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:41:34 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 16:33:06 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

/**
 * @brief 
 * $?의 경우 minishell 구조체에 저장된 상태코드로 치환한다.
 * 환경 변수 내에 존재하지 않는 키일 경우 공백으로 치환한다.
 * @param minishell 
 * @param key 
 * @return char* 
 */
char	*convert_key(t_minishell *minishell, char *key)
{
	char	*value;

	if (!ft_strcmp(key, "?"))
		value = ft_itoa(minishell->status);
	else
		value = getenv(key);
	free(key);
	if (!value)
		value = ft_strdup(" ");
	else
		value = strdup(value);
	return (value);
}

/**
 * @brief 
 * 큰 따옴표 처리 함수
 * 하... 이건... 함수 어케 줄이냐...
 * @param minishell 
 * @param str 
 * @return char* 
 */
char	*process_dquote(t_minishell *minishell, char *str)
{
	int		len;
	char	*target;
	char	*backup;
	char	*temp;

	target = ft_strchr(str, '$');
	if (!target)
		return (str);
	backup = ft_substr(str, 0, target - str);
	while (target)
	{
		len = 0;
		temp = backup;
		while (target[len + 1] && target[len + 1] != ' ' \
		&& target[len + 1] != '\'')
			len++;
		if (len)
			backup = ft_strjoin(temp, \
			convert_key(minishell, ft_substr(target, 1, len)));
		else
			backup = ft_strjoin(temp, "$");
		free(temp);
		if (!ft_strchr(target + len + 1, '$'))
		{
			temp = backup;
			backup = ft_strjoin(temp, target + len + 1);
			free(temp);
			break ;
		}
		target = ft_strchr(target + len + 1, '$');
	}
	return (backup);
}

/**
 * @brief 
 * dquote, dollar 토큰 처리 함수
 * @param minishell 
 * @param token 
 * @return char* 
 */
char	*process_token(t_minishell *minishell, t_token *token)
{
	char	*value;

	if (token->type == DOLR)
		token->value = convert_key(minishell, token->value);
	else if (token->type == DQUT)
	{
		value = process_dquote(minishell, token->value);
		if (!value)
			value = ft_strdup(" ");
		token->value = value;
	}
	return (token->value);
}

/**
 * @brief 
 * 토큰화된 line을 하나의 단어로 연결시켜주는 함수
 * double quote, dollar 토큰의 경우 process_token 함수를 통해 토큰 처리를 해준다.
 * @param minishell 
 * @param token 
 * @return t_token* 
 */
t_token	*link_words(t_minishell *minishell, t_token **new_tokenizer, \
t_token *token, t_token_type type)
{
	char			*str;
	char			*tmp;

	if (token->type == DQUT || token->type == DOLR)
		str = ft_strdup(process_token(minishell, token));
	else
		str = ft_strdup(token->value);
	token = token->next;
	while (token && token->type >= 1 && token->type <= 5)
	{
		if (token->type >= 11 && token->type <= 14)
			break ;
		tmp = str;
		if (token->type == DQUT || token->type == DOLR)
			str = ft_strjoin(tmp, process_token(minishell, token));
		else
			str = ft_strjoin(tmp, token->value);
		free(tmp);
		token = token->next;
	}
	insert_token(new_tokenizer, init_token(str, type));
	return (token);
}

/**
 * @brief 
 * 토큰화된 line을 단어별로 연결시켜주는 함수
 * dollar 토큰도 함께 해석한다.
 * ex) e'ch'o -> e, ch, o -> echo
 * ex) echo "hi $USER" -> hi, hyuncpar
 * @param minishell 
 * @param token 
 * @return t_token* 
 */
t_token	*link_token(t_minishell *minishell, t_token *token)
{
	t_token			*new_tokenizer;
	t_token_type	type;

	new_tokenizer = NULL;
	while (token)
	{
		if (token->type != SPCE)
		{
			type = token->type;
			if (token->type >= 1 && token->type <= 5)
				token = link_words(minishell, &new_tokenizer, token, type);
			else
			{
				insert_token(&new_tokenizer, \
				init_token(ft_strdup(token->value), type));
				token = token->next;
			}
		}
		else
			token = token->next;
	}
	return (new_tokenizer);
}
