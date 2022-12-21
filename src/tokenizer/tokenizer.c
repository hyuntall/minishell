/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/21 21:07:05 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

t_token	*tokenizer(char *input)
{
	int		i;
	int		index;
	t_token	*token;

	i = 0;
	index = 0;
	token = NULL;
	while (input && input[i])
	{
		if (input [i] == '\'' || input[i] == '"' || input[i] == ' ' \
		|| input[i] == '\\' || input[i] == '$' || input[i] == '|' \
		|| input[i] == '&' || input[i] == '>' || input[i] == '<' \
		|| input[i] == '(' || input[i] == ')')
		{
			i = tokenize_line(&token, input, index, i);
			index = i;
		}
		else
			i++;
		if (i == TOKEN_ERROR)	//TODO minishell status change
		{
			free_tokens(token);
			return (token);
		}
	}
	if (i - index)
		insert_token(&token, init_token(ft_substr(input, index, i - index), NORM));
	return (token);
}
