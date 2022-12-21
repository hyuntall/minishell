/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:41:34 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/21 17:27:13 by hyuncpar         ###   ########.fr       */
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
		value = getenv(token->value);
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

t_token	*aasda(t_token **new_tokenizer, t_token *token, t_token_type type)
{
	char			*str;
	char			*tmp;

	str = ft_strdup("");
	while (token && token->type != SPCE)
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
			if (token->type >= 11 && token->type <= 14)
			{
				token = token->next;
				if (token && token->type == SPCE)
					token = token->next;
				token = aasda(&new_tokenizer, token, type);
			}
			else
				token = aasda(&new_tokenizer, token, type);
		}
		else
			token = token->next;
	}
	printf("%s\n", new_tokenizer->value);
	return (new_tokenizer);
}
