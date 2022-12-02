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

void	setting_signal(void);
void	handle_prompt(void);
char	**process_line(char *input);