/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/14 21:01:21 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

t_token	*tokenizer(char *input)
{
	//word split->skip space
	int		i;
	int		index;
	t_token	*ret;

	i = 0;
	index = 0;
	ret = NULL;
	while (input && input[i])
	{
		if (input [i] == '\'' || input[i] == '"' || input[i] == ' ' \
		|| input[i] == '\\' || input[i] == '$' || input[i] == '|' \
		|| input[i] == '&' || input[i] == '>' || input[i] == '<')
		{
			i = tokenize_line(&ret, input, index, i);
			index = i;
		}
		else
			i++;
		if (i == TOKEN_ERROR)	//TODO minishell status change
		{
			free_tokens(ret);
			return (ret);
		}
	}
	if (i - index)
		insert_token(&ret, init_token(ft_substr(input, index, i - index), NORM));
	return (ret);
}
