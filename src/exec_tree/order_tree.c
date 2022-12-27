/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:57:15 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/27 01:14:28 by hanjiwon         ###   ########.fr       */
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
	}
	else
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		order_tree(minishell, left);
	}
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

void	here_doc(char *limit)
{
	char	*line;
	char	*temp;
	int		fd;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		line = readline("heredoc> ");
		if (!ft_strncmp(line, limit, ft_strlen(line)))
			break ;
		temp = line;
		line = ft_strjoin(temp, "\n");
		free(temp);
		temp = 0;
		ft_putstr_fd(line, fd);
		free(line);
		line = 0;
	}
	free(line);
	line = 0;
	close(fd);
}

void	redir(t_token_type type, char *filename)
{
	int	fd;

	if (type == RIGT)
	{
		fd = open(filename, O_RDWR | O_CREAT | O_TRUNC, 0777);
		dup2(fd, 1);
		close(fd);
	}
	else if (type == DRGT)
	{
		fd = open(filename, O_RDWR | O_CREAT | O_APPEND, 0777);
		dup2(fd, 1);
	}
	else if (type == LEFT)
	{
		fd = open(filename, O_RDWR, 0777);
		dup2(fd, 0);
	}
	else if (type == DLFT)
	{
		here_doc(filename);
		//fd = open("heredoc", O_RDWR | O_CREAT, 0777);
		//dup2(fd, 0);
		//close(fd);
		unlink("heredoc");
	}
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

void	order_tree(t_minishell *minishell, t_parse_tree *tree)
{
	t_token	*token;(void)token;
	t_cmd_tbl	*cmd_tbl;
	char	**arr;

	cmd_tbl = init_cmd_tbl();
	token = tree->token;
	if (tree->type == PIPE)
		pipeline(minishell, tree->left, tree->right);
	else if (tree->type == DAND)
		;
		//pipeline(minishell, tree->left, tree->right);
	else
	{
		arr = make_arr(tree->token);
		if (check_builtin(cmd_tbl, arr[0]))
		{
			ft_execve(minishell, cmd_tbl, arr);
			exit(1);
		}
		else
		{
			execve(check_cmd(minishell, arr[0]), arr, minishell->envp);
			perror(arr[0]);
			exit(1);	
		}
	}
}
