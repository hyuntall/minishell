/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:13:06 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/29 02:54:18 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

static int check_variable_name(const char *name)
{
	if (!ft_isalpha(*name) && *name != '_')
		return (FALSE);
	while (*name && *name != '=')
	{
		if (!ft_isalpha(*name) && *name != '_' && !ft_isdigit(*name))
			return (FALSE);
		name++;
	}
	return (TRUE);
}

void    split_key_value(t_envp *envp, char *str)
{
	char    *key;
	char    *value;
	char    *sign;

	sign = ft_strchr(str, '=');
	if (sign)
	{
		key = ft_substr(str, 0, ft_strlen(str) - ft_strlen(sign));
		value = ft_substr(sign, 1, ft_strlen(sign) - 1);
	}
	else
	{
		key = ft_strdup(str);
		value = NULL;
	}
	insert_envp(&envp, key, value);
	free(key);
	free(value);
}

void	ft_export(t_minishell *minishell, char **arr)
{
	int    i;

	i = 1;
	if (!arr[1])
	{
		print_sort_envp(minishell);
		return ;
	}
	while (arr[i])
	{
		if (!check_variable_name(arr[i]))
			export_error_message(arr[i]);
		else
			split_key_value(minishell->envp, arr[i]);
		++i;
	}
	printf("export result(%d)\n", minishell->envp->cnt);
	t_envp *node = minishell->envp;
	while (node)
	{
		printf("%s=%s\n", node->key, node->value);
		node = node->next;
	}
}