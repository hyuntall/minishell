/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/27 18:21:49 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/29 20:14:21 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	here_doc(char *limit)
{
	char	*line;
	char	*temp;
	int		fd;

	fd = open("heredoc", O_RDWR | O_CREAT | O_TRUNC, 0777);
	while (1)
	{
		line = readline("heredoc> ");
		if (ft_strlen(line) && !ft_strcmp(line, limit))
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

void	input_heredoc(t_minishell *minishell, char *limit)
{
	int	fd;

	here_doc(limit);
	fd = open("heredoc", O_RDWR | O_CREAT, 0777);
	minishell->redir->in = fd;
	unlink("heredoc");
}
