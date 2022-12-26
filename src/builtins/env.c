/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:03:32 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/27 03:05:34 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	env(t_minishell *minishell, char **arr)
{
    int i;

    (void)arr;
    i = -1;
    while (minishell->envp[++i])
        printf("%s\n", minishell->envp[i]);
}