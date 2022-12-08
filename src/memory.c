/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:06 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/08 18:51:15 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_line *line)
{
	t_arg	*arg;
	t_arg	*tmp;

	arg = line->head;
	while (arg)
	{
		tmp = arg;
		arg = tmp->next;
		free(tmp->value);
		free(tmp);
	}
}

void	init_line(t_line *line)
{
	line->head = 0;
	line->tail = 0;
}
