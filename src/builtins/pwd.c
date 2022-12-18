/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:28 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 02:34:39 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

t_cmd_tbl	**init_cmd_tbl(void)
{
	t_cmd_tbl **cmd_tbl;
	
	cmd_tbl = (t_cmd_tbl **)calloc(sizeof(t_cmd_tbl *), 1);
	*cmd_tbl = (t_cmd_tbl *)calloc(sizeof(t_cmd_tbl), 1);
	
	cmd_tbl[0]->cmd = ft_strdup("echo");
	cmd_tbl[0]->func = echo;
	cmd_tbl[0]->argc = AC_ANY;
	
	return (cmd_tbl);
	//*tbl[1] = {"cd", cd, AC_LESS_1, ""};
	
	/*t_cmd_tbl cmd_tbl[] = 
	{
		{"echo", echo, AC_ANY, "-n"},
		{"cd", cd, AC_LESS_1, ""},
		{"pwd", pwd, AC_ZERO, ""},
		{"export", ft_export, 0, ""},
		{"unset", unset, 0, ""},
		{"env", env, 0, ""},
		{"exit", ft_exit, AC_ZERO, ""}
	};*/

}

void	ft_execve(t_minishell *minishell, t_cmd_tbl **cmd_tbl, char **arr)
{
	
}
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