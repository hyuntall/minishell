/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:37 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/27 18:44:05 by hyuncpar         ###   ########.fr       */
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

typedef	struct s_redir t_redir;

struct s_redir
{
	int		in;
	int		out;
	t_redir	*next;
};

typedef struct s_minishell
{
	char 		**path;
	char 		**envp;
	t_redir		*redir;
	int			status;
}				t_minishell;

void	setting_signal(void);
void 	main_loop(t_minishell *minishell);
void	init(t_minishell *minishell, char *envp[]);
void	check_arg(int ac, char *av[]);

// 이거 어따 놓지
void	input_heredoc(t_minishell *minishell, char *limit);
void	init_redir(t_minishell *minishell);
#endif
