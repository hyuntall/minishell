/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting_exec.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/02 16:45:18 by hyuncpar          #+#    #+#             */
/*   Updated: 2023/01/02 17:04:08 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"
#include "cmd.h"

/**
 * @brief Set the redir object
 * finename과 리다이렉션 타입에 따라 입출력 정보를 redir 구조체에 저장한다.
 * @param minishell 
 * @param type 
 * @param filename 
 */
void	set_redir(t_minishell *minishell, t_token_type type, char *filename)
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
	{
		minishell->status = 1;
		perror(filename);
		exit(minishell->status);
	}
}

static int	arr_size(t_token *token)
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

/**
 * @brief 
 * 연결 리스트 상태의 명령어 집합을 투포인터로 변경한다.
 * execve 함수의 인자로 투포인터가 필요하기 때문.
 * @param token 
 * @return char** 
 */
char	**make_list_to_pointer(t_token *token)
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
