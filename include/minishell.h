#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "tokenization.h"
// #include "parse_tree.h"

#include "../libft/libft.h"

#define FALSE 0
#define TRUE 1

typedef struct s_minishell
{
	char **path;
	char **envp;
	int	status;
}				t_minishell;

void	setting_signal(void);
void 	main_loop(void);
void	init(void);
void	check_arg(int ac, char *av[]);
#endif
