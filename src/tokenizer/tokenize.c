/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:36:45 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/22 05:39:54 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "testcode.h"

int	tokenize_quote(t_token **token, char *input, int i, t_token_type type)
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
	insert_token(token, init_token(ft_substr(input, ++i, size), type));
	i += size + 1;
	return (i);
}

int	tokenize_oper(t_token **token, char *input, int i, t_token_type type)
{
	int		size;
	int		d_oper;
	char	c ;

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
		insert_token(token, init_token(ft_substr(input, i, 1), type));
	else if (size == 1)
		insert_token(token, init_token(ft_substr(input, i, 2), d_oper));
	else
		return (unexpecte_token(type, ft_substr(input, i, size + 1)));
	return (i + size + 1);
}

int	tokenize_redir(t_token **token, char *input, int i, int type)
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
	while (input[i + size + 1] == c)
		size++;
	if (!size)
		insert_token(token, init_token(ft_substr(input, i, 1), type));
	else if (size == 1)
		insert_token(token, init_token(ft_substr(input, i, 2), d_oper));
	else
		return (unexpecte_token(type, ft_substr(input, i, size + 1)));
	i += size + 1;
	return (i);
}

int	tokenize_etc(t_token **token, char *input, int i, int type)
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
			insert_token(token, init_token(ft_strdup("$"), NORM));
			return (i);
		}
	}
	insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}

int	tokenize_prnth(t_token **token, char *input, int i)
{
	if (input[i] == ')')
		insert_token(token, init_token(ft_strdup(")"), PARENTHESIS_RIGHT));
	else if (input[i] == '(')
		insert_token(token, init_token(ft_strdup("("), PARENTHESIS_LEFT));
	return (++i);
}

int	tokenize_line(t_token **token, char *input, int index, int i)
{
	if (i - index)
		insert_token(token, init_token(ft_substr(input, index, i - index), NORM));
	if (input[i] == '\'')
		i = tokenize_quote(token, input, i, QUOT);
	else if (input[i] == '"')
		i = tokenize_quote(token, input, i, DQUT);
	else if (input[i] == ' ')
		i = tokenize_etc(token, input, i, SPCE);
	else if (input[i] == '\\')
		i = tokenize_etc(token, input, i, BSLH);
	else if (input[i] == '$')
		i = tokenize_etc(token, input, i, DOLR);
	else if (input[i] == '|')
		i = tokenize_oper(token, input, i, PIPE);
	else if (input[i] == '&')
		i = tokenize_oper(token, input, i, NORM);
	else if (input[i] == '>')
		i = tokenize_redir(token, input, i, RIGT);
	else if (input[i] == '<')
		i = tokenize_redir(token, input, i, LEFT);
	else if (input[i] == '(' || input[i] == ')')
		i = tokenize_prnth(token, input, i);
	return (i);
}
