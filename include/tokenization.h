/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hyuncpar <hyuncpar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 16:41:09 by jiwonhan          #+#    #+#             */
/*   Updated: 2023/01/02 16:29:07 by hyuncpar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKENIZATION_H
# define TOKENIZATION_H

# define TOKEN_ERROR -1

typedef	struct s_token t_token;

typedef enum	e_token_type
{
	SPCE, // Space
	NORM, // Normal
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
	NEW_LINE  // \n
}			t_token_type;

typedef enum e_special_symbols
{
	LOGICAL = DPIP | DAND,
	PIPE_SYMBOLS = PIPE,
	REDIRECTION = RIGT | DRGT | LEFT | DLFT,
	SEMICOLON = SEMC | DSEM
}			t_special_symbols;

struct s_token
{
	char			*value;
	t_token_type	type;
	t_token			*next;
	t_token			*prev;
};

// 라인 토큰화
t_token	*analize_line(t_minishell *minishell, char *input);
t_token	*tokenizer(char *input);
int		tokenize_line(t_token **token, char *input, int index, int i);
int		tokenize_quote(t_token **token, char *input, int i, t_token_type type);
int		tokenize_oper(t_token **token, char *input, int i, t_token_type type);
int		tokenize_redir(t_token **token, char *input, int i, int type);
int		tokenize_etc(t_token **token, char *input, int i, int type);
int		tokenize_semicolon(t_token **token, char *input, int i);
int		tokenize_prnth_or_newline(t_token **token, char *input, int i);

// 토큰 구문 분석
t_token	*link_token(t_minishell *minishell, t_token *token);
void	error_lexical(t_token *token, char *value);

// 토큰 구조체 생성 및 제거
t_token	*init_token(char *value, int type);
void	insert_token(t_token **head_token, t_token *new_token);
void	delete_token(t_token *token);
void	free_tokens(t_token *token);

// 어따놓지
int		is_redirection(t_token_type type);

//jiwon
t_token *get_head_token(t_token *token);
t_token *get_tail_token(t_token *token);
void	not_match_token(void);
#endif