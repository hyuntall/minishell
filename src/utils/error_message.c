/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:49:28 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/27 17:38:44 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

int	unexpecte_token(t_token_type type, char *str)
{
	printf("error %d %s\n", type, str);
	free(str);
	return (-1);
}

void	error_lexical(t_token *token, char *value)
{
	ft_putstr_fd("minishell: syntax error near unexpected token `", 2);
	if (ft_strncmp(value, "\n", 1))
		ft_putstr_fd(value, 2);
	else
		ft_putstr_fd("newline", 2);
	ft_putstr_fd("'\n", 2);
	free_tokens(token);
}

void	not_match_token(void)
{
		ft_putstr_fd("minishell: syntax error not match token\n", 2);
	return ;
}