/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:37 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 01:34:37 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "../libft/libft.h"

#define FALSE 0
#define TRUE 1

typedef struct s_minishell
{
	char 		**path;
	char 		**envp;
	int			status;
}				t_minishell;

void	setting_signal(void);
void 	main_loop(t_minishell *minishell);
void	init(t_minishell *minishell, char *envp[]);
void	check_arg(int ac, char *av[]);
#endif
