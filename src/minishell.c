/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/09 21:23:04 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[])
{
	check_arg(ac, av);
	init();	//TODO hyuntall->envp
	main_loop();
	return (0);
}
