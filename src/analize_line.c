/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/29 20:26:45 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "lexer.h"

t_token	*analize_line(t_minishell *minishell, char *input)
{
	t_token	*tokenized;
	t_token	*new_tokenized;

	if (!ft_strlen(input))
		return (NULL);
	input = ft_strjoin(input, "\n");
	tokenized = tokenizer(input);
	free(input);
	if (!tokenized)
		return (NULL);
	new_tokenized = link_token(minishell, tokenized);
	free_tokens(tokenized);
	if (lexer(minishell, new_tokenized) == FALSE)
	{
		minishell->status = 1;
		printf("minishell status 1\n");
		return (NULL);
	}
	return (new_tokenized);
}
