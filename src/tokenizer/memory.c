/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:06 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 00:14:09 by jiwonhan         ###   ########seoul.kr  */
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
