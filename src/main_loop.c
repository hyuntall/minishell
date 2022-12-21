/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:08 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 17:08:06 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"
#include "parse_tree.h"

static char *read_line(char **line)
{
	*line = readline("minishell$ ");
	return (*line);
}

static char	check_quote(char *line)
{
	int	i = -1;
	char quote = 0;

	if (!line)
		return (0);
	while (line[++i])
	{
		if ((line[i] == '\\' && ((int)(ft_strlen(line)) - 1 != i + 1) && line[i + 1] == '\'') || \
			(line[i] == '\\' && ((int)(ft_strlen(line)) - 1 != i + 1) && line[i + 1] == '\"'))
		{
			++i;
			continue ;
		}
		if (line[i] == '\'' || line[i] == '"')
		{
			if (quote == 0)
				quote = line[i];
			else if (quote == '\'' && line[i] == '\'')
				quote = 0;
			else if (quote == '"' && line[i] == '"')
				quote = 0;
			else if (quote == '\'' && line[i] == '"')
				continue ;
			else if (quote == '"' && line[i] == '\'')
				continue ;
		}
	}
	return (quote);
}

static int check_line(char **line)
{
	//TODO NULL string, empty string
	if (ft_strlen(*line) == 0)
		return (0);

	//TODO blank string
	int i = -1;
	size_t blank_cnt = 0;
	while ((*line)[++i])
	{
		if ((*line)[i] == ' ')
			++blank_cnt;
	}
	if (blank_cnt == ft_strlen(*line))
		return (0);
	//TODO unclosed quotes
	char quote = check_quote(*line);
	while (quote)
	{
		*line = ft_strjoin(*line, "\n");
		*line = ft_strjoin(*line, readline("> "));
		//printf("join line = %s@\n", *line);
		quote = check_quote(*line);
	}
	return (1);
}

void	exev_line(t_minishell *minishell, t_parse_tree *parse_tree)
{
	pid_t	pid;

	pid = fork();
	waitpid(pid, NULL, 0);
	if (!pid)
		order_tree(minishell, parse_tree);
}

void main_loop(t_minishell *minishell)
{
	char			*line;
	t_token			*tokenization;
	t_parse_tree	*parse_tree;

	while (read_line(&line))
	{
		add_history(line);
		check_line(&line); //TODO jiwon, false=> free
		printf("input: %s\n", line);	//TODO
		tokenization = analize_line(minishell, line);	//TODO error처리를 위해 우선 minishell도 매개변수로 주었음
		free(line);
		if (!tokenization)
			continue ;
		
		printf(">>tokenization result<<\n");	//TODO
		t_token *token = tokenization;
		while (token)
		{
			printf("arg: %10s type: %10d len: %10zu\n", token->value, token->type, ft_strlen(token->value));
			token = token->next;
		}	//TODO tokenization result end
		
		//parse_tree = parser(tokenization);(void)parse_tree;
		//printf(">>parse tree result<<\n");	//TODO
		//print_parse_tree(parse_tree, 0);
		//exev_line(minishell, parse_tree);
		//free_tokens(parse_tree->token);
		//TODO parse tree result end
		//execute(parse_tree);	//TODO 
		//free (parse_tree);
	}
	return ;
}

void print_node(t_token *token)
{
	t_token *tmp;

	tmp = token;
	while (tmp)
	{
		printf("%s\t", tmp->value);
		tmp = tmp->next;
	}
	printf("\n");
}

void print_parse_tree(t_parse_tree *parse_tree, int level)
{
	printf("level%d root(%d)\t", level, parse_tree->type);
	print_node(parse_tree->token);
	if (parse_tree->original)
		printf("\toriginal : %s\n", parse_tree->original);
	if (parse_tree->left)
		print_parse_tree(parse_tree->left, level + 1);
	if (parse_tree->right)
		print_parse_tree(parse_tree->right, level + 1);
}