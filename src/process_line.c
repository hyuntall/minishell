/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/02 21:16:50 by hyuncpar         ###   ########.fr       */
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

char	**process_line(char *input)
{
	char	*str;
	char	**cmds;
	int		i;
	int		j;
	int		isquote;

	i = 0;
	j = 0;
	isquote = 0;
	str = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '\'')
		{
			str = join_line(str, ft_substr(input, j, i - j));
			i++;
			j = i;
			isquote = 1 - isquote;
		}
		else if (input[i] == '"')
		{
			// process dquote
		}
		else if (input[i] == ' ' && !isquote)
		{
			str = join_line(str, ft_substr(input, j, i - j));
			str = join_line(str, ft_strdup("'"));
			i++;
			j = i;
		}
		else
			i++;
	}
	str = join_line(str, ft_substr(input, j, i - j));
	cmds = ft_split(str, '\'');
	free(str);
	str = 0;
	return (cmds);
}
