/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   order_tree.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/15 17:57:15 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/07 18:54:03 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"
#include "cmd.h"

void	process_parent(t_minishell *minishell, \
t_parse_tree *right, pid_t pid, int *fd)
{
	int	status;

	dup2(fd[0], 0);
	close(fd[1]);
	close(fd[0]);
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		minishell->status = WEXITSTATUS(status);
	else if (WIFSIGNALED(status))
		minishell->status = WTERMSIG(status);
	order_tree(minishell, right);
}

/**
 * @brief 
 * pipe 연산 함수
 * 자식프로세스는 현재 minishell 구조체에 저장된 redir 상태의 이전 노드를 전달한다.
 * (구문 트리를 뒤에서부터 파싱했기 때문)
 */
void	pipeline(t_minishell *minishell, \
t_parse_tree *left, t_parse_tree *right)
{
	int		fd[2];
	int		pipes;(void)pipes;
	pid_t	pid;

	pipes = pipe(fd);
	pid = fork();
	if (pid)
		process_parent(minishell, right, pid, fd);
	else
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		minishell->redir = minishell->redir->prev;
		order_tree(minishell, left);
	}
}

/**
 * @brief 
 * and, or, semicolon 연산 함수
 * and의 경우 이전 명령어를 수행하는 자식프로세스의 종료 상태가 0이어야만 다음 명령어를 실행한다.
 * @param minishell 
 * @param tree 
 */
void	two_process(t_minishell *minishell, t_parse_tree *tree)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid)
	{
		waitpid(pid, &status, 0);
		if (WIFEXITED(status))
			minishell->status = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			minishell->status = WTERMSIG(status);
		if (tree->type == SEMC || tree->type == DPIP)
			order_tree(minishell, tree->right);
		else if (tree->type == DAND)
			if (!minishell->status)
				order_tree(minishell, tree->right);
	}
	else
		order_tree(minishell, tree->left);
}

/**
 * @brief 
 * 구문 트리를 전위 순회로 탐색하여 프로세스를 실행
 * 각각 pipe, and, or, semicolon 별로 처리를 해주고
 * 리다이렉션의 경우, 오른쪽 자식 노드의 value 값을 토대로 입출력 설정을 해준다.
 * 그 외에 경우 리프 노트라고 간주하여 함수를 실행한다.
 * @param minishell 
 * @param tree 
 */
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
		set_redir(minishell, tree->type, tree->right->token->value);
		order_tree(minishell, tree->left);
	}
	else
	{
		arr = make_list_to_pointer(tree->token);
		exec_cmd(minishell, arr);
	}
}
