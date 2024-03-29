/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/29 02:53:15 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/29 03:03:10 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int check_variable_name(const char *name)
{
    if (!ft_isalpha(*name) && *name != '_')
        return (FALSE);
    while (*name)
    {
        if (!ft_isalpha(*name) && *name != '_' && !ft_isdigit(*name))
            return (FALSE);
        name++;
    }
    return (TRUE);
}

void	unset(t_minishell *minishell, char **arr)
{
    int i;

    i = 1;
    while (arr[i])
    {
        if (!check_variable_name(arr[i]))
            unset_error_message(arr[i]);
        else
            delete_envp(&(minishell->envp), arr[i]);
        ++i;
    }
}
