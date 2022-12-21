/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 16:50:32 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 17:54:37 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

void	echo(char **arr)
{
	int	i;
	
	if (!ft_strncmp(arr[1], "-n", ft_strlen(arr[1])))
	{
		i = 2;
		while (arr[i])
		{
			printf("%s", arr[i++]);
			if (arr[i])
				printf(" ");
		}
	}
	else
	{
		i = 1;
		while (arr[i])
		{
			printf("%s", arr[i++]);
			if (arr[i])
				printf(" ");
		}
		printf("\n");
	}
}
