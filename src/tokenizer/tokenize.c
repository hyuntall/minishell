/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 17:36:45 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/28 16:03:30 by hyuncpar         ###   ########.fr       */
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

	size = 1;
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
	if (input[i + size] == c)
		insert_token(token, init_token(ft_substr(input, i, ++size), d_oper));
	else
		insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}

int	tokenize_redir(t_token **token, char *input, int i, int type)
{
	int		size;
	int		d_oper;
	char	c;

	size = 1;
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
	if (input[i + size] == c)
		insert_token(token, init_token(ft_substr(input, i, ++size), d_oper));
	else
		insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}

int	tokenize_semicolon(t_token **token, char *input, int i)
{
	int		size;

	size = 1;
	if (input[i + size] == ';')
		insert_token(token, init_token(ft_substr(input, i, ++size), DSEM));
	else
		insert_token(token, init_token(ft_substr(input, i, size), SEMC));
	i += size;
	return (i);
}

int	is_special_symbol(char c)
{
	return (c == '\'' || c == '"' || c == ' ' || c == '\\' || c == '$' \
			|| c == '|' || c == '&' || c == '>' || c == '<' || c == '(' || c == ')');
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
		while (input[i + size] && !is_special_symbol(input[i + size]))
			size++;
		if (size == 1)
		{
			insert_token(token, init_token(ft_strdup("$"), NORM));
			return (++i);
		}
	}
	insert_token(token, init_token(ft_substr(input, i, size), type));
	i += size;
	return (i);
}

int	tokenize_prnth_or_newline(t_token **token, char *input, int i)
{
	if (input[i] == ')')
		insert_token(token, init_token(ft_strdup(")"), PARENTHESIS_RIGHT));
	else if (input[i] == '(')
		insert_token(token, init_token(ft_strdup("("), PARENTHESIS_LEFT));
	else
		insert_token(token, init_token(ft_strdup("\n"), NEW_LINE));
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
	else if (input[i] == '(' || input[i] == ')' || input[i] == '\n')
		i = tokenize_prnth_or_newline(token, input, i);
	else if (input[i] == ';')
		i = tokenize_semicolon(token, input, i);
	return (i);
}
