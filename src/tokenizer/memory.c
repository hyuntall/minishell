/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:06 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 15:51:33 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

t_token	*init_token(char *value, int type)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	if (!token)
		return (NULL);
	ft_memset(token, 0, sizeof(t_token));
	token->value = value;
	token->type = type;
	return (token);
}

void	insert_token(t_token **head_token, t_token *new_token)
{
	if (!*head_token)
	{
		*head_token = new_token;
		return ;
	}
	while ((*head_token)->next)
		head_token = &((*head_token)->next);
	(*head_token)->next = new_token;
	new_token->prev = *head_token;
}

void	delete_token(t_token *token)
{
	token->prev->next = token->next;
	token->next->prev = token->prev;
	token->next = NULL;
	token->prev = NULL;
	free_tokens(token);
}

void	free_tokens(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token;
		token = token->next;
		free(tmp->value);
		free(tmp);
	}
}
