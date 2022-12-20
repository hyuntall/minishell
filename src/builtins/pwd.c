/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:28 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 05:20:04 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	setting_cmd(t_cmd *cmd, char *command, int argc, char *option)
{
	cmd->cmd = command;
	cmd->argc = argc;
	cmd->opt = option;
}
t_cmd_tbl	*init_cmd_tbl(void)
{
	t_cmd_tbl	*cmd_tbl;
	
	cmd_tbl = (t_cmd_tbl *)malloc(sizeof(t_cmd_tbl));
	if (!cmd_tbl)
		exit(-1);	//TODO error message
	cmd_tbl->max_element = 7;
	cmd_tbl->cmd = (t_cmd *)malloc(sizeof(t_cmd) * cmd_tbl->max_element);
	if (!cmd_tbl->cmd)
		exit(-1);	//TODO error message
	setting_cmd(&cmd_tbl->cmd[0], ft_strdup("echo"), AC_ANY, "");
	cmd_tbl->cmd[0].func = echo;
	setting_cmd(&cmd_tbl->cmd[1], "cd", AC_LESS_1, "");
	cmd_tbl->cmd[1].func = cd;
	setting_cmd(&cmd_tbl->cmd[2], "pwd", AC_ZERO, "");
	cmd_tbl->cmd[2].func = pwd;
	setting_cmd(&cmd_tbl->cmd[3], "export", 0, "");
	cmd_tbl->cmd[3].func = ft_export;
	setting_cmd(&cmd_tbl->cmd[4], "unset", 0, "");
	cmd_tbl->cmd[4].func = unset;
	setting_cmd(&cmd_tbl->cmd[5], "env", 0, "");
	cmd_tbl->cmd[5].func = env;
	setting_cmd(&cmd_tbl->cmd[6], "exit", AC_ZERO, "");
	cmd_tbl->cmd[6].func = ft_exit;
	return (cmd_tbl);
}

/*void	ft_execve(t_minishell *minishell, t_cmd_tbl **cmd_tbl, char **arr)
{
	
}*/
void	echo(void)
{
	printf("echo\n");
}

void	cd(void)
{
	printf("cd\n");
}

void	pwd(void)
{
	printf("pwd\n");
}

void	ft_export(void)
{
	printf("ft_export\n");
}

void	unset(void)
{
	printf("unset\n");
}

void	env(void)
{
	printf("env\n");
}

void	ft_exit(void)
{
	printf("ft_exit\n");
}