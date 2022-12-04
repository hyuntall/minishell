/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/04 21:35:23 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*join_line(char *input, char *word)
{
	char	*str;

	str = ft_strjoin(input, word);
	if (!str)
		return (0);
	free(input);
	input = 0;
	free(word);
	word = 0;
	return (str);
}

int		parse_type(t_line *args, char *input, int index, int i)
{
	int		j;

	j = 0;
	if (i - index)
		arg_insert(args, ft_substr(input, index, i - index), NORM);
	if (input[i] == '\'')
	{
		while (input[i + j + 1] != '\'')
			j++;
		arg_insert(args, ft_substr(input, ++i, j), QUOT);
		i += j + 1;
	}
	else if (input[i] == '"')
	{
		while (input[i + j + 1] != '"')
			j++;
		arg_insert(args, ft_substr(input, ++i, j), DQUT);
		i += j + 1;
	}
	else if (input[i] == ' ')
	{
		while (input[i + j + 1] == ' ')
			j++;
		arg_insert(args, ft_substr(input, ++i, j), SPCE);
		i += j;
	}
	else if (input[i] == '\\')
	{
		arg_insert(args, ft_substr(input, ++i, 1), BSLH);
		i++;
	}
	else if (input[i] == '$')
	{
		while (input[i + j + 1] != ' ' && input[i + j + 1])
			j++;
		arg_insert(args, ft_substr(input, ++i, j), DOLR);
		i += j;
	}
	return (i);
}

void	process_line(t_line *args, char *input)
{
	int		i;
	int		index;

	i = 0;
	index = 0;
	while (input[i])
	{
		if (input [i] == '\'' || input[i] == '"' || input[i] == ' ' \
		|| input[i] == '\\' || input[i] == '$')
		{
			i = parse_type(args, input, index, i);
			index = i;
		}
		else
			i++;
	}
	if (i - index)
		arg_insert(args, ft_substr(input, index, i - index), NORM);
}
