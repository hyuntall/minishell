/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:41:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/13 16:10:31 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# define TOKEN_ERROR -1

typedef enum	e_token_type
{
	NORM, // Normal
	SPCE, // Space
	QUOT, // Single Quote
	DQUT, // Double Quote
	BSLH, // Back Slash
	DOLR, // Dollar
	PIPE, // Pipe
	DPIP, // Double Pipe (Or Operator)
	DAND, // Double And (And Operator)
	SEMC, // Semi Colon
	DSEM, // Double Semi Colon
	RIGT, // Right (Over Write)
	DRGT, // Double Right (Append)
	LEFT, // Left (Stdin)
	DLFT, // Double Left (Heredoc)
	PARENTHESIS, // Parenthesis
	EROR  // Error
}			t_token_type;

typedef	struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
	struct s_token	*prev;
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
char			*process_dquote(char *str);
#endif