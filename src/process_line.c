/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/05 18:19:27 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	process_line(t_line *args, char *input)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (input && input[i])
	{
		if (input [i] == '\'' || input[i] == '"' || input[i] == ' ' \
		|| input[i] == '\\' || input[i] == '$' || input[i] == '|' \
		|| input[i] == '&' || input[i] == '>' || input[i] == '<')
		{
			i = tokenize_line(args, input, index, i);
			index = i;
		}
		else
			i++;
	}
	if (i - index)
		arg_insert(args, ft_substr(input, index, i - index), NORM);
}
