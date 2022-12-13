/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/04 21:36:48 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/13 14:18:49 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*token_new(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	token->value = value;
	token->type = type;
	token->next = NULL;
	token->prev = NULL;
	return (token);
}

void	token_insert(t_token_list *token_list, char *value, t_token_type type)
{
	t_token	*token;

	token = token_new(value, type);
	if (!token_list->head)
	{
		token_list->head = token;
		token_list->tail = token;
	}
	else
	{	
		token_list->tail->next = token;
		token->prev = token_list->tail;
		token_list->tail = token_list->tail->next;
		token_list->tail->next = NULL;
	}
}
