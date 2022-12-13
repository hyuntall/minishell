/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 14:41:34 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/13 16:21:09 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
