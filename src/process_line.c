/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/03 23:37:03 by hanjiwon         ###   ########.fr       */
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

char	*parse_envp(char *key)
{
	printf("dgdg%s\n", key);
	return (key);
}
/*
char	*process_dquote(char *input, char *word)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = ft_strdup("");
	while (input[i])
	{
		if (input[i] == '$')
		{
			str = join_line(str, ft_substr(input, j, i - j));
			while (input[i] != ' ' || input[i])
				i++;
			str = join_line(str, ft_substr(input, j, i - j));
		}
	}
}*/

char	**process_line(char *input)
{printf("in process line = %s\n",input);
	char	*str;
	char	**cmds;
	int		i;
	int		j;
	int		index;

	i = 0;
	index = 0;
	str = ft_strdup("");
	while (input[i])
	{
		j = 0;
		if (input[i] == '\'')
		{
			str = join_line(str, ft_substr(input, index, i - index));
			i++;
			while (input[i + j] != '\'')
				j++;
			str = join_line(str, ft_substr(input, i, j));
			i += j + 1;
			index = i;
		}
		else if (input[i] == '"')
		{
			// process dquote
			str = join_line(str, ft_substr(input, index, i - index));
			i++;
			while (input[i + j] != '"')
				j++;
			str = join_line(str, ft_substr(input, i, j));
			i += j + 1;
			index = i;
		}
		else if (input[i] == ' ')
		{
			str = join_line(str, ft_substr(input, index, i - index));
			str = join_line(str, ft_strdup("'"));
			i++;
			j = i;
			index = i;
		}
		else
			i++;
	}
	printf("result: %s\n", str);
	str = join_line(str, ft_substr(input, index, i - index));
	cmds = ft_split(str, '\'');
	free(str);
	str = 0;
	return (cmds);
}
