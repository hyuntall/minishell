/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:21:45 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/27 03:02:19 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "minishell.h"

#define AC_ZERO		200		//명령어 인자 개수가 0인 경우
#define AC_LESS_1	201		// 명령어 인자 개수가 0 또는 1인 경우
#define AC_ANY		202		// 명령어 인자 개수가 제한 없는 경우(echo)

typedef struct s_cmd
{
	char	*cmd;
	void (*func)(t_minishell *minishell, char **arr);
	int		argc;
	char	*opt;
}				t_cmd;

typedef struct s_cmd_tbl
{
	int		max_element;
	t_cmd	*cmd;
}				t_cmd_tbl;

void	echo(t_minishell *minishell, char **arr);
void	cd(t_minishell *minishell, char **arr);
void	pwd(t_minishell *minishell, char **arr);
void	ft_export(t_minishell *minishell, char **arr);
void	unset(t_minishell *minishell, char **arr);
void	env(t_minishell *minishell, char **arr);
void	ft_exit(t_minishell *minishell, char **arr);

t_cmd_tbl	*init_cmd_tbl(void);
void	ft_execve(t_minishell *minishell, t_cmd_tbl *cmd_tbl, char **arr);
#endif