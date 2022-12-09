/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:41:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/09 20:03:15 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# define TOKEN_ERROR -1

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

void			init_line(t_token_list *line);
void			token_insert(t_token_list *line, char *value, t_token_type type);
int				tokenize_line(t_token_list *args, char *input, int index, int i);
t_token_list	analize_line(t_token_list token_list, char *input);
int				unexpecte_token(t_token_type type, char *str);
void			free_tokens(t_token_list *token_list);
void			init_token_list(t_token_list *token_list);
#endif