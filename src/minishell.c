/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 03:11:32 by hyuncpar         ###   ########.fr       */
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
	//atexit(a);
	t_minishell	minishell;

	//minishell = NULL;
	check_arg(ac, av);
	init(&minishell, envp);	//TODO hyuntall->envp
	main_loop(&minishell);
	return (0);
}
