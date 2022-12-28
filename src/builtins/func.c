/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:28 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/28 22:36:20 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	unset(t_minishell *minishell, char **arr)
{
	printf("unset\n");
	(void)minishell;(void)arr;
}

void	ft_exit(t_minishell *minishell, char **arr)
{
	printf("ft_exit\n");
	(void)minishell;(void)arr;
}