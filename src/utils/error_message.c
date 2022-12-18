/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_message.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 18:49:28 by hyuncpar          #+#    #+#             */
/*   Updated: 2022/12/19 00:14:22 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"

int	unexpecte_token(t_token_type type, char *str)
{
	printf("error %d %s\n", type, str);
	free(str);
	return (-1);
}
