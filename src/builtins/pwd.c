/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:28 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 19:52:05 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	pwd(char **arr)
{
	char *path;

	(void)arr;
	path = getcwd(NULL, 0);
	if (!path)
		return ;
	printf("%s\n", path);
	free(path);
	path = NULL;
}
