/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:12 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/05 16:39:07 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char *av[])
{
	(void)ac;(void)av;
	setting_signal();
	handle_prompt();	//TODO func name bad
	return (0);
}
