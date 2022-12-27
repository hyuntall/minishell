/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:41:34 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/27 17:35:04 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

char	*process_dquote(char *str)
{
	int		len;
	char	*target;
	char	*key;
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
		while(target[len + 1] && target[len + 1] != ' ' && target[len + 1] != '\'')
			len++;
		if (len)
		{
			key = ft_substr(target, 1, len);
			if (getenv(key))
				backup = ft_strjoin(temp, getenv(key));
			else
				backup = ft_strjoin(temp, " ");
			free(key);
		}
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

char	*process_token(t_token *token)
{
	char	*value;

	if (token->type == DOLR)
	{
		value = ft_strdup(getenv(token->value));
		if (!value)
			value = ft_strdup(" ");
		token->value = value;
	}
	else if (token->type == DQUT)
	{
		value = process_dquote(token->value);
		if (!value)
			value = ft_strdup(" ");
		token->value = value;
	}
	return (token->value);
}

t_token	*link_words(t_token **new_tokenizer, t_token *token, t_token_type type)
{
	char			*str;
	char			*tmp;

	if (token->type == DQUT || token->type == DOLR)
		str = ft_strdup(process_token(token));
	else
		str = ft_strdup(token->value);
	token = token->next;
	while (token && token->type >= 1 && token->type <= 5)
	{
		if (token->type >= 11 && token->type <= 14)
			break ;
		tmp = str;
		if (token->type == DQUT || token->type == DOLR)
			str = ft_strjoin(tmp, process_token(token));
		else
			str = ft_strjoin(tmp, token->value);
		free(tmp);
		token = token->next;
	}
	insert_token(new_tokenizer, init_token(str, type));
	return (token);
}

int	valid_lexical(t_token_type type, t_token *token)
{
	t_token_type	cur_type;

	cur_type = token->type;
	if (type == PIPE && cur_type != PIPE && cur_type >= 5 && cur_type <= 16)
		return (0);
	else if (type == DPIP && cur_type >= 5 && cur_type <= 16)
		return (0);
	else if (type == DAND && cur_type >= 5 && cur_type <= 16)
		return (0);
	else if (type == LEFT && cur_type >= 5 && cur_type <= 16)
		return (0);
	else if (type == DLFT && cur_type >= 5 && cur_type <= 16)
		return (0);
	else if (type == RIGT && cur_type >= 5 && cur_type <= 16)
		return (0);
	else if (type == DRGT && cur_type >= 5 && cur_type <= 16)
		return (0);
	return (1);
}

t_token	*link_token(t_token *token)
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
				token = link_words(&new_tokenizer, token, type);
			else
			{
				insert_token(&new_tokenizer, init_token(ft_strdup(token->value), type));
				token = token->next;
			}
		}
		else
			token = token->next;
	}
	return (new_tokenizer);
}
