/*
cc -lreadline -L/usr/local/opt/readline/lib -I/usr/local/opt/readline/include signal_test.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>

void	handler(int sig)
{
	//printf("signal : %d\n", sig);
	if (sig == SIGINT)
	{
		write(STDOUT_FILENO, "\n", 1);
		if (rl_on_new_line() == -1)
			exit (1);
		rl_replace_line("", 1);
		rl_redisplay();
	}
	else if (sig == SIGTERM)
	{
		printf("exit\n");
		exit (-1);
	}
	else
		return ;
}

void	setting_signal()
{
	struct termios term;
	tcgetattr(STDIN_FILENO, &term);
	term.c_lflag &= ~(ECHOCTL);
	tcsetattr(STDIN_FILENO, TCSANOW, &term);
	
	signal(SIGINT, handler);	// CTRL + C
	signal(SIGTERM, handler);	// CTRL + D
	signal(SIGQUIT, handler);	// CTRL + /
}

int main(void)
{
	char *line;
	int ret;

	setting_signal();
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