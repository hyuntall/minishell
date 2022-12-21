/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 20:30:36 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	a()
{
	printf("leaks test\n");
	system("leaks minishell");
}

int main(int ac, char *av[], char *envp[])
{
	//atexit(a);
	t_minishell	minishell;

	check_arg(ac, av);
	init(&minishell, envp);
	main_loop(&minishell);
	return (0);
}
