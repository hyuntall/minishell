/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_list.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:36:48 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/04 21:44:42 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_arg	*arg_new(char *value, int type)
{
	t_arg	*arg;

	arg = (t_arg *)malloc(sizeof(t_arg));
	if (!arg)
		return (0);
	arg->value = value;
	arg->type = type;
	arg->next = 0;
	return (arg);
}

void	arg_insert(t_line *line, char *value, int type)
{
	t_arg	*new_arg;

	new_arg = arg_new(value, type);
	if (!line->head)
	{
		line->head = new_arg;
		line->tail = new_arg;
	}
	else
	{	
		line->tail->next = new_arg;
		line->tail = line->tail->next;
		line->tail->next = 0;
	}
}
