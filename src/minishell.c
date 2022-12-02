#include "minishell.h"

int main(int ac, char *av[])
{
	(void)ac;(void)av;
	setting_signal();
	handle_prompt();	//TODO func name bad
	return (0);
}