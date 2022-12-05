/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:08 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/05 16:38:59 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void handle_prompt(void)
{
	char		*line;
	const char	type[100][100] = {"NORM", "SPCE", "QUOT", "DQUT", "BSLH", "DOLR"};
	t_line		args;
	t_arg		*arg;

	while (read_line(&line))
	{
		add_history(line);
		if (check_line(&line) == FALSE)
		{
			free(line);
			line = NULL;
			continue ;
		}
		printf("input line = %s\n", line);   //TODO_check readline
		if (!line)
			continue ;
		init_line(&args);
		process_line(&args, line);
		arg = args.head;
		while (arg)
		{
			printf("cmd: %10s type: %10s\n", arg->value, type[arg->type]);
			arg = arg->next;
		}
		free(line);
		line = NULL;
	}
	return ;
}
