/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:21:45 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 05:19:18 by jiwonhan         ###   ########seoul.kr  */
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
	void (*func)(void);
	int		argc;
	char	*opt;
}				t_cmd;

typedef struct s_cmd_tbl
{
	int		max_element;
	t_cmd	*cmd;
}				t_cmd_tbl;

void	echo(void);
void	cd(void);
void	pwd(void);
void	ft_export(void);
void	unset(void);
void	env(void);
void	ft_exit(void);

t_cmd_tbl	*init_cmd_tbl(void);

#endif