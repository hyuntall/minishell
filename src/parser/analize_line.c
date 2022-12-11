/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/09 20:34:41 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token_list	analize_line(t_token_list token_list, char *input)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	init_token_list(&token_list);
	while (input && input[i])
	{
		if (input [i] == '\'' || input[i] == '"' || input[i] == ' ' \
		|| input[i] == '\\' || input[i] == '$' || input[i] == '|' \
		|| input[i] == '&' || input[i] == '>' || input[i] == '<')
		{
			i = tokenize_line(&token_list, input, index, i);
			index = i;
		}
		else
			i++;
		if (i == TOKEN_ERROR)
		{
			free_tokens(&token_list);
			return (token_list);
		}
	}
	if (i - index)
		token_insert(&token_list, ft_substr(input, index, i - index), NORM);
	return (token_list);
}
