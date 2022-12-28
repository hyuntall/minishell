/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 21:37:42 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/28 21:43:22 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    print_envp(t_minishell *minishell)
{
	t_envp  *envp;

	envp = minishell->envp;
	while (envp)
	{
		printf("%s=%s\n",envp->key,envp->value);
		envp = envp->next;
	}
}