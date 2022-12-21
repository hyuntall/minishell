/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   analize_line.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/02 16:42:09 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/21 21:21:01 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

t_token	*analize_line(t_minishell *minishell, char *input)
{(void)minishell;
	t_token	*tokenized;
	t_token	*new_tokenized;

	tokenized = tokenizer(input);
	if (!tokenized)
		return (NULL);
	new_tokenized = link_token(tokenized);
	free_tokens(tokenized);
	//lexer
	return (new_tokenized);
}
