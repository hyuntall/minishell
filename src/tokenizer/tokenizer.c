/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/27 17:15:40 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "testcode.h"

static int	is_valid_char(char c)
{
	return (c == '\'' || c == '"' || c == ' ' || c == '\\' || c == '$' \
			|| c == '|' || c == '&' || c == '>' || c == '<'  \
			|| c == '(' || c == ')' || c == '\n');
}

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
		if (end_index == TOKEN_ERROR)	//TODO minishell status change
		{
			free_tokens(token);
			return (token);
		}
		//print_node(token);
	}
	if (end_index - start_index)
		insert_token(&token, init_token(ft_substr(input, start_index, end_index - start_index), NORM));
	return (token);
}
