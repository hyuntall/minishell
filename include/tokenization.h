/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:41:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/19 00:13:44 by jiwonhan         ###   ########seoul.kr  */
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
	PARENTHESIS, // Parenthesis
	EROR  // Error
}			t_token_type;

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
char	*process_dquote(char *str);
void	free_tokens(t_token *token);
int	unexpecte_token(t_token_type type, char *str);

//jiwon
t_token *get_head_token(t_token *token);
t_token *get_tail_token(t_token *token);

#endif