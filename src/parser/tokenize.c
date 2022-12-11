/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:36:45 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/11 15:14:33 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_quote(t_token_list *token_list, char *input, int i, t_token_type type)
{
	int		size;
	char	c;

	if (type == QUOT)
		c = '\'';
	else
		c = '"';
	size = 0;
	while (input[i + size + 1] != c)
		size++;
	token_insert(token_list, ft_substr(input, ++i, size), type);
	i += size + 1;
	return (i);
}

int	tokenize_oper(t_token_list *token_list, char *input, int i, t_token_type type)
{
	int		size;
	int		d_oper;
	char	c;

	if (type == PIPE)
	{
		c = '|';
		d_oper = DPIP;
	}
	else
	{
		c = '&';
		d_oper = DAND;
	}
	size = 0;
	while (input[i + size + 1] == c)
		size++;
	if (!size)
		token_insert(token_list, ft_substr(input, i, 1), type);
	else if (size == 1)
		token_insert(token_list, ft_substr(input, i, 2), d_oper);
	else
		return (unexpecte_token(type, ft_substr(input, i, size + 1)));
	return (i + size + 1);
}

int	tokenize_redir(t_token_list *token_list, char *input, int i, int type)
{
	int		size;
	int		d_oper;
	char	c;

	size = 0;
	if (type == RIGT)
	{
		c = '>';
		d_oper = DRGT;
	}
	else
	{
		c = '<';
		d_oper = DLFT;
	}
	while (input[i + size + 1] == '>')
		size++;
	if (!size)
		token_insert(token_list, ft_substr(input, i, 1), type);
	else if (size == 1)
		token_insert(token_list, ft_substr(input, i, 2), d_oper);
	else
		return (unexpecte_token(type, ft_substr(input, i, size + 1)));
	i += size + 1;
	return (i);
}

int	tokenize_etc(t_token_list *token_list, char *input, int i, int type)
{
	int		size;

	size = 1;
	if (type == SPCE)
		while (input[i + size] == ' ')
			size++;
	else if (type == BSLH)
		i++;
	else if (type == DOLR)
	{
		i++;
		while (input[i + size] && input[i + size] != ' ')
			size++;
		if (size == 1)
		{
			token_insert(token_list, ft_strdup("$"), NORM);
			return (i);
		}
	}
	token_insert(token_list, ft_substr(input, i, size), type);
	i += size;
	return (i);
}

int	tokenize_line(t_token_list *token_list, char *input, int index, int i)
{
	if (i - index)
		token_insert(token_list, ft_substr(input, index, i - index), NORM);
	if (input[i] == '\'')
		i = tokenize_quote(token_list, input, i, QUOT);
	else if (input[i] == '"')
		i = tokenize_quote(token_list, input, i, DQUT);
	else if (input[i] == ' ')
		i = tokenize_etc(token_list, input, i, SPCE);
	else if (input[i] == '\\')
		i = tokenize_etc(token_list, input, i, BSLH);
	else if (input[i] == '$')
		i = tokenize_etc(token_list, input, i, DOLR);
	else if (input[i] == '|')
		i = tokenize_oper(token_list, input, i, PIPE);
	else if (input[i] == '&')
		i = tokenize_oper(token_list, input, i, NORM);
	else if (input[i] == '>')
		i = tokenize_redir(token_list, input, i, RIGT);
	else if (input[i] == '<')
		i = tokenize_redir(token_list, input, i, LEFT);
	printf("%d\n", i);
	return (i);
}
