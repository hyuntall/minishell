/*
cc -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include readline_test.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>

void	handler(int sig)
{
	if (sig != SIGINT)
		return ;
	write(STDOUT_FILENO, "\n", 1);
	if (rl_on_new_line() == -1)
		exit (1);
	rl_replace_line("", 1);
	rl_redisplay();
}

int main(void)
{
	char *line;
	int ret;

	signal(SIGINT, handler);
	while (1)
	{
		line = readline("input> ");
		if (!line)
			return (1);
		ret = strcmp(line, "break");
		add_history(line);
		if (ret)
			printf("output> %s\n", line);
		free(line);
		line = NULL;
		if (!ret)
			break;
	}
	return (0);
}