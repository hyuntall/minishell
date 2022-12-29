/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:08 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/29 20:23:30 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "testcode.h"	//TODO
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
		quote = check_quote(*line);
	}
	return (1);
}

void	exev_line(t_minishell *minishell, t_parse_tree *parse_tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	waitpid(pid, &status, 0);
	if (!pid)
		order_tree(minishell, parse_tree);
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = WTERMSIG(status);
}

void main_loop(t_minishell *minishell)
{
	char			*line;
	t_token			*tokenization;
	t_parse_tree	*parse_tree;

	while (read_line(&line))
	{
		add_history(line);
		check_line(&line);
		tokenization = analize_line(minishell, line);	//TODO error처리를 위해 우선 minishell도 매개변수로 주었음
		free(line);
		if (!tokenization)
			continue ;
		//print_tokenization_result(tokenization);//(void)parse_tree;//TODO
		//heredoc(minishell, tokenization);		//heredoc here??!!!!
		parse_tree = parser(tokenization);
		//(void)parse_tree;printf(">>parse tree result<<\n");print_parse_tree(parse_tree, 0);
		exev_line(minishell, parse_tree);
		//free_tokens(parse_tree->token);
		//TODO parse tree result end
		//execute(parse_tree);	//TODO 
		free (parse_tree);
	}
	return ;
}