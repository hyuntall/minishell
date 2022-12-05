/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:06 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/05 16:38:41 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_cmds(char **cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
}

void	init_line(t_line *line)
{
	line->head = 0;
	line->tail = 0;
}
