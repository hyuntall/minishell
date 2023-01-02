/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_command.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:42:10 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 17:02:51 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"
#include "cmd.h"

/**
 * @brief 
 * 현재 redir 구조체 정보에 따라 입출력을 재지정한다.
 * @param redir 
 */
void	redirect(t_redir *redir)
{
	if (redir->in)
	{
		dup2(redir->in, 0);
		close(redir->in);
	}
	if (redir->out)
	{
		dup2(redir->out, 1);
		close(redir->out);
	}
}

/**
 * @brief 
 * 해당 명령어가 builtin 명령어인지 확인한다.
 * @param cmd_tbl 
 * @param cmd 
 * @return int 
 */
static int	check_builtin(t_cmd_tbl *cmd_tbl, const char *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd_tbl->max_element)
	{
		if (ft_strncmp(cmd_tbl->cmd[i].cmd, cmd, ft_strlen(cmd)) == 0)
			return (TRUE);
	}
	return (FALSE);
}

/**
 * @brief 
 * 해당 명령어가 존재하는지 확인
 * 존재하지 않으면 status_code 를 127로 설정한다.
 * @param minishell 
 * @param cmd 
 * @return char* 
 */
char	*check_cmd(t_minishell *minishell, char *cmd)
{
	int		i;
	char	*abs_path;

	i = -1;
	if (!access(cmd, X_OK))
		return (cmd);
	if (cmd[0] == '/')
		return (cmd);
	while (minishell->path[++i])
	{
		abs_path = ft_strjoin(minishell->path[i], cmd);
		if (!access(abs_path, X_OK))
		{
			free(cmd);
			return (abs_path);
		}
		free(abs_path);
	}
	minishell->status = 127;
	return (cmd);
}

/**
 * @brief 
 * 명령어를 실행한다.
 * 해당 명령어가 가능한 명령어인지 검사한 후에
 * 현재 redir 구조체에 따라서 입출력을 재지정한다.
 * 만약 현재 함수가 builtin 함수라면 따로 실행한다.
 * @param minishell 
 * @param cmds 
 */
void	exec_cmd(t_minishell *minishell, char **cmds)
{
	t_redir		*redir;
	t_cmd_tbl	*cmd_tbl;
	char		*cmd;

	cmd = check_cmd(minishell, cmds[0]);
	cmd_tbl = init_cmd_tbl();
	redir = minishell->redir;
	redirect(redir);
	if (check_builtin(cmd_tbl, cmd))
	{
		ft_execve(minishell, cmd_tbl, cmds);
		exit(1);
	}
	else
	{
		execve(cmd, cmds, envp_to_dptr(minishell->envp));
		perror(cmd);
		exit(1);
	}
}
