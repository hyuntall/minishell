/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/18 20:33:09 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	a()
{
	printf("?????\n");
	system("leaks minishell");
}

int main(int ac, char *av[], char *envp[])
{
	atexit(a);
	t_minishell	minishell;

	//minishell = NULL;
	check_arg(ac, av);
	init(&minishell, envp);	//TODO hyuntall->envp
	main_loop(&minishell);
	return (0);
}
