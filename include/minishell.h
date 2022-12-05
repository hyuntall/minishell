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
	DOLR,
	PIPE,
	DPIP,
	DAND,
	SEMC,
	DSEM,
	RIGT,
	DRGT,
	LEFT,
	DLFT,
	EROR
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
void	free_cmds(char **cmds);
void	init_line(t_line *line);
int		tokenize_line(t_line *args, char *input, int index, int i);
#endif
