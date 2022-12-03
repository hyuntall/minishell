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

	while (line[++i])
	{
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

void	free_cmds(char **cmds)
{
	int		i;

	i = 0;
	while (cmds[i])
		free(cmds[i++]);
	free(cmds);
}

void handle_prompt(void)
{
	char 	*line;
	char	**cmds;
	int		i;

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
		//parser -> one string, unspecified special characters(\ ; )
		cmds = process_line(line);
		i = 0;
		while (cmds[i])
		{
			printf("cmd[%d]: %s\n", i, cmds[i]);
			i++;
		}
		free(cmds);
		free(line);
		line = NULL;
	}
	return ;
}
