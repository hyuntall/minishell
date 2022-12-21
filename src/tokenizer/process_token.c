/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:41:34 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/21 16:54:51 by hyuncpar         ###   ########.fr       */
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

t_token	*link_token(t_token *token)
{
	t_token			*new_tokenizer;
	char			*str;
	char			*tmp;
	t_token_type	type;

	new_tokenizer = NULL;
	while (token)
	{
		if (token->type != SPCE)
		{
			str = ft_strdup("");
			type = token->type;
			while (token && token->type != SPCE)
			{
				tmp = str;
				if (token->type >= 11 && token->type <= 14)
				{
					token = token->next;
					if (token && token->type == SPCE)
						token = token->next;
				}
				if (token->type == DQUT || token->type == DOLR)
					str = ft_strjoin(tmp, process_token(token));
				else
					str = ft_strjoin(tmp, token->value);
				free(tmp);
				token = token->next;
			}
			insert_token(&new_tokenizer, init_token(str, type));
		}
		else
			token = token->next;
	}
	return (new_tokenizer);
}
