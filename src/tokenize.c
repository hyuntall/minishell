/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:36:45 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/05 18:20:22 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	tokenize_quote(t_line *args, char *input, int i, int type)
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
	arg_insert(args, ft_substr(input, ++i, size), type);
	i += size + 1;
	return (i);
}

int	tokenize_operator(t_line *args, char *input, int i, int type)
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
		arg_insert(args, ft_substr(input, i, 1), type);
	else if (size == 1)
		arg_insert(args, ft_substr(input, i, 2), d_oper);
	else
		arg_insert(args, ft_substr(input, i, size + 1), EROR);
	i += size + 1;
	return (i);
}

int	tokenize_redir(t_line *args, char *input, int i, int type)
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
		arg_insert(args, ft_substr(input, i, 1), type);
	else if (size == 1)
		arg_insert(args, ft_substr(input, i, 2), d_oper);
	else
		arg_insert(args, ft_substr(input, i, size + 1), EROR);
	i += size + 1;
	return (i);
}

int	tokenize_etc(t_line *args, char *input, int i, int type)
{
	int		size;
	char	c;

	size = 0;
	if (type == SPCE)
	{
		c = ' ';
		while (input[i + size + 1] == ' ')
			size++;
	}
	else if (type == BSLH)
	{
		c = '\\';
		size++;
	}
	else if (type == DOLR)
	{
		c = '$';
		while (input[i + size + 1] != ' ' && input[i + size + 1])
			size++;
	}
	arg_insert(args, ft_substr(input, ++i, size), type);
	i += size;
	return (i);
}

int	tokenize_line(t_line *args, char *input, int index, int i)
{
	int		j;

	j = 0;
	if (i - index)
		arg_insert(args, ft_substr(input, index, i - index), NORM);
	if (input[i] == '\'')
		i = tokenize_quote(args, input, i, QUOT);
	else if (input[i] == '"')
		i = tokenize_quote(args, input, i, DQUT);
	else if (input[i] == ' ')
		i = tokenize_etc(args, input, i, SPCE);
	else if (input[i] == '\\')
		i = tokenize_etc(args, input, i, BSLH);
	else if (input[i] == '$')
		i = tokenize_etc(args, input, i, DOLR);
	else if (input[i] == '|')
		i = tokenize_operator(args, input, i, PIPE);
	else if (input[i] == '&')
		i = tokenize_operator(args, input, i, NORM);
	else if (input[i] == '>')
		i = tokenize_redir(args, input, i, RIGT);
	else if (input[i] == '<')
		i = tokenize_redir(args, input, i, LEFT);
	return (i);
}