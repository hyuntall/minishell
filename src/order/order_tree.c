/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:57:15 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/18 21:37:43 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"

void	pipeline(t_minishell *minishell, t_parse_tree *left, t_parse_tree *right)
{
	int		fd[2];
	int		pipes;
	pid_t	pid;

	pipes = pipe(fd);
	pid = fork();
	if (pid > 0)
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
	int	flag;

	size = 0;
	flag = 1;
	while (token)
	{
		if (token->type != SPCE && flag)
		{
			size++;
			flag = 0;
		}
		else if (token->type == SPCE)
			flag = 1;
		token = token->next;
	}
	return (size);
}

// 옮겨야함
char	**make_arr(t_token *token)
{
	int		i;
	int		size;
	char	*str;
	char	*temp;
	char	**arr;

	i = 0;
	size = arr_size(token);
	arr = (char **)malloc(sizeof(char *) * (size + 1));
	while (i < size)
	{
		if (token->type == SPCE)
			token = token->next;
		str = ft_strdup("");
		while (token && token->type != SPCE)
		{
			temp = str;
			str = ft_strjoin(temp, process_token(token));
			free(temp);
			token = token->next;
		}
		arr[i++] = str;
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

void	order_tree(t_minishell *minishell, t_parse_tree *tree)
{
	t_token	*token;
	char	**arr;

	token = tree->token;
	if (tree->type == PIPE)
		pipeline(minishell, tree->left, tree->right);
	else if (tree->type == DAND)
		pipeline(minishell, tree->left, tree->right);
	else
	{
		arr = make_arr(tree->token);
		execve(check_cmd(minishell, arr[0]), arr, minishell->envp);
		perror(arr[0]);
		exit(1);
	}
}
