/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:57:15 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/28 17:10:59 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"
#include "cmd.h"

void	pipeline(t_minishell *minishell, t_parse_tree *left, t_parse_tree *right)
{
	int		fd[2];
	int		pipes;(void)pipes;
	pid_t	pid;

	pipes = pipe(fd);
	pid = fork();
	wait(NULL);
	if (pid)
	{
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		waitpid(pid, NULL, 0);
		order_tree(minishell, right);
		exit(0);
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		minishell->redir = minishell->redir->prev;
		order_tree(minishell, left);
		exit(0);
	}
}

void	two_process(t_minishell *minishell, t_parse_tree *tree)
{
	pid_t	pid;

	pid = fork();
	if (pid)
	{
		if (tree->type == SEMC || tree->type == DPIP)
			order_tree(minishell, tree->right);
		else if (tree->type == DAND)
			;
	}
	else
		order_tree(minishell, tree->left);
}

int	arr_size(t_token *token)
{
	int	size;

	size = 0;
	while (token)
	{
		token = token->next;
		size++;
	}
	return (size);
}

void	redir(t_minishell *minishell, t_token_type type, char *filename)
{
	int	fd;

	if (type == RIGT)
	{
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		minishell->redir->out = fd;
	}
	else if (type == DRGT)
	{
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
		minishell->redir->out = fd;
	}
	else if (type == LEFT)
	{
		fd = open(filename, O_RDWR, 0777);
		minishell->redir->in = fd;
	}
	else
		fd = 0;
	if (fd == -1)
		perror(filename);
}

// 옮겨야함
char	**make_arr(t_token *token)
{
	int				i;
	int				size;
	char			**arr;

	i = 0;
	size = arr_size(token);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		arr[i] = token->value;
		token = token->next;
		i++;
	}
	arr[i] = NULL;
	return (arr);
}

// 옮겨야함
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
	return (cmd);
}

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

void	exec_cmd(t_minishell *minishell, char **cmd)
{
	t_redir	*redir;
	t_cmd_tbl	*cmd_tbl;

	cmd_tbl = init_cmd_tbl();
	redir = minishell->redir;
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
	if (check_builtin(cmd_tbl, cmd[0]))
	{
		ft_execve(minishell, cmd_tbl, cmd);
		exit(1);
	}
	else
	{
		execve(check_cmd(minishell, cmd[0]), cmd, minishell->envp);
		perror(cmd[0]);
		exit(1);
	}
}

void	order_tree(t_minishell *minishell, t_parse_tree *tree)
{
	t_token	*token;(void)token;
	char	**arr;

	token = tree->token;
	if (tree->type == PIPE)
		pipeline(minishell, tree->left, tree->right);
	else if (tree->type == DAND || tree->type == DPIP || tree->type == SEMC)
		two_process(minishell, tree);
	else if (is_redirection(tree->type))
	{
		redir(minishell, tree->type, tree->right->token->value);
		order_tree(minishell, tree->left);
	}
	else
	{
		arr = make_arr(tree->token);
		exec_cmd(minishell, arr);
	}
}
