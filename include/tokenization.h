/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:41:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/21 21:09:57 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# define TOKEN_ERROR -1

typedef	struct s_token t_token;

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
	PARENTHESIS_LEFT, // Parenthesis
	PARENTHESIS_RIGHT,
	EROR  // Error
}			t_token_type;

typedef enum e_special_symbols
{
	LOGICAL = DPIP | DAND,
	PIPE_SYMBOLS = PIPE,
	REDIRECTION = RIGT | DRGT | LEFT | DLFT
}			t_special_symbols;

struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

t_token	*analize_line(t_minishell *minishell, char *input);
t_token	*tokenizer(char *input);
int	tokenize_quote(t_token **token, char *input, int i, t_token_type type);
int	tokenize_oper(t_token **token, char *input, int i, t_token_type type);
int	tokenize_redir(t_token **token, char *input, int i, int type);
int	tokenize_etc(t_token **token, char *input, int i, int type);
int	tokenize_line(t_token **token, char *input, int index, int i);
t_token	*init_token(char *value, int type);
void	insert_token(t_token **head_token, t_token *new_token);
void	delete_token(t_token *token);
char	*process_dquote(char *str);
void	free_tokens(t_token *token);
int	unexpecte_token(t_token_type type, char *str);

t_token	*link_token(t_token *token);
void	redir(t_token_type type, char *filename);
//jiwon
t_token *get_head_token(t_token *token);
t_token *get_tail_token(t_token *token);

#endif