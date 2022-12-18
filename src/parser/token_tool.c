/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_tool.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:59 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 00:14:00 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "tokenization.h"


t_token *get_head_token(t_token *token)
{
    while (token && token->prev)
        token = token->prev;
    return (token);
}


t_token *get_tail_token(t_token *token)
{
    while (token && token->next)
        token = token->next;
    return (token);
}