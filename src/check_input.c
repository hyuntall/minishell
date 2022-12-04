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

void	init_line(t_line *line)
{
	line->head = 0;
	line->tail = 0;
}

void handle_prompt(void)
{
	char		*line;
	const char	type[100][100] = {"NORM", "SPCE", "QUOT", "DQUT", "BSLH", "DOLR"};
	int			i;
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
		//parser -> one string, unspecified special characters(\ ; )
		init_line(&args);
		process_line(&args, line);
		arg = args.head;
		while (arg)
		{
			printf("cmd: %10s type: %10s\n", arg->value, type[arg->type]);
			arg = arg->next;
		}
		i = 0;
		free(line);
		line = NULL;
	}
	return ;
}
