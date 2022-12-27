/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/23 23:23:21 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "lexer.h"

t_token	*analize_line(t_minishell *minishell, char *input)
{
	t_token	*tokenized;
	t_token	*new_tokenized;

	tokenized = tokenizer(input);
	if (!tokenized)
		return (NULL);
	new_tokenized = link_token(tokenized);
	free_tokens(tokenized);
	if (lexer(new_tokenized) == FALSE)
	{
		minishell->status = -1;
		printf("minishell status -1\n");
		return (NULL);
	}
	return (new_tokenized);
}
