/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_loop.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 16:38:08 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/13 15:16:32 by hyuncpar         ###   ########.fr       */
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

void main_loop(void)
{
	char			*line;
	t_token_list	token_list;
	t_token			*token;
	//t_parse_tree	*parse_tree;

	while (read_line(&line))
	{
		add_history(line);
		check_line(&line); //TODO jiwon, false=> free
		token_list = analize_line(token_list, line);	//TODO
		free(line);
		if (!token_list.head)
			continue ;
		token = token_list.head;
		while (token)
		{
			printf("arg: %10s type: %10d len: %10zu\n", token->value, token->type, ft_strlen(token->value));
			if (token->type == 3)
				printf("<======= $: %s ========>\n", process_dquote(token->value));
			token = token->next;
		}

		//parse_tree = parse(token_list);
		//execute(parse_tree);	//TODO 
		//free (parse_tree);
	}



	/*while (read_line(&line))
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
			printf("arg: %10s type: %10d len: %10zu\n", arg->value, arg->type, ft_strlen(arg->value));
			arg = arg->next;
		}
		free_tokens(&args);
		free(line);
		line = NULL;
	}*/
	return ;
}
