/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:59:14 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/14 19:31:40 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_arg(int ac, char *av[])
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(-1);
	}
}

void	init(t_minishell *minishell)
{
	minishell = malloc(sizeof(t_minishell));
	ft_memset(minishell, 0, sizeof(minishell));
	setting_signal();
}
