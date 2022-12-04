#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include "../libft/libft.h"

#define FALSE 0
#define TRUE 1

enum	e_type
{
	NORM,
	SPCE,
	QUOT,
	DQUT,
	BSLH,
	DOLR
};

typedef	struct s_arg
{
	char			*value;
	int				type;
	struct s_arg	*next;
}	t_arg;

typedef struct s_line
{
	t_arg	*head;
	t_arg	*tail;
}	t_line;

void	setting_signal(void);
void	handle_prompt(void);
void	process_line(t_line *line, char *input);
void	arg_insert(t_line *line, char *value, int type);
#endif