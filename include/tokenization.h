/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:41:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/09 17:37:58 by jiwonhan         ###   ########seoul.kr  */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

typedef enum	e_token_type
{
	NORM,
	SPCE,
	QUOT,
	DQUT,
	BSLH,
	DOLR,
	PIPE,
	DPIP,
	DAND,
	SEMC,
	DSEM,
	RIGT,
	DRGT,
	LEFT,
	DLFT, 
	EROR
}			t_token_type;

typedef	struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

typedef struct s_token_list
{
	t_token	*head;
	t_token	*tail;
}	t_token_list;

#endif