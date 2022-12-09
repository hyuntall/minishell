/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/09 19:59:12 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[])
{
	//check_arg(ac, av)
	ac = 0;
	av = 0;
	//init() => signal, envp
	setting_signal();
	main_loop();
	return (0);
}
