/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:21:45 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/01/07 19:00:37 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CMD_H
# define CMD_H

#include "minishell.h"

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