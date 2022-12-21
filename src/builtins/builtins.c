/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 17:23:18 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 17:41:42 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "pwd.h"

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
	cmd_tbl->max_element = 1;
	cmd_tbl->cmd = (t_cmd *)malloc(sizeof(t_cmd) * cmd_tbl->max_element);
	if (!cmd_tbl->cmd)
		exit(-1);	//TODO error message
	setting_cmd(&cmd_tbl->cmd[0], ft_strdup("echo"), AC_ANY, "");
	cmd_tbl->cmd[0].func = echo;
	/*setting_cmd(&cmd_tbl->cmd[1], "cd", AC_LESS_1, "");
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
	cmd_tbl->cmd[6].func = ft_exit;*/
	return (cmd_tbl);
}

static int	check_builtin_arg(t_cmd *cmd, char **arr)
{
	int	argc = 0;
	while (arr[argc])
		argc++;
	//printf("%d\t%d\n", cmd->argc, argc);
	if ((cmd->argc == AC_ZERO && argc != 1) \
		|| (cmd->argc == AC_LESS_1 && argc > 2))
		return (FALSE);
	return (TRUE);
}

void	ft_execve(t_minishell *minishell, char **arr)
{
	int	i;
	i = -1;
	while (++i < minishell->cmd_tbl->max_element)
	{
		if (ft_strncmp(minishell->cmd_tbl->cmd[i].cmd, arr[0], ft_strlen(arr[0])) == 0)
		{
			if (check_builtin_arg(&minishell->cmd_tbl->cmd[i], arr))
				minishell->cmd_tbl->cmd[i].func(arr);
		}
	}
}
