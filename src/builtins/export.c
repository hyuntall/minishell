/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 03:13:06 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/27 03:42:43 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	ft_export(t_minishell *minishell, char **arr)
{
    if (!arr[1])
        sort_envp(minishell->envp);
    
}