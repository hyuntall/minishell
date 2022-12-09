/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:49:28 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/09 20:03:03 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unexpecte_token(t_token_type type, char *str)
{
	printf("error %d %s\n", type, str);
	free(str);
	return (-1);
}
