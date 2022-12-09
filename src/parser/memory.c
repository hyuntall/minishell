/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:06 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/09 19:55:46 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token_list *token_list)
{
	t_token	*token;
	t_token	*tmp;

	token = token_list->head;
	while (token)
	{
		tmp = token;
		token = tmp->next;
		free(tmp->value);
		free(tmp);
	}
}

void	init_token_list(t_token_list *token_list)
{
	token_list->head = 0;
	token_list->tail = 0;
}
