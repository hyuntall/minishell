/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 00:13:37 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/29 00:01:27 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <readline/readline.h>
#include <readline/history.h>
#include <string.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include "../libft/libft.h"

#define FALSE 0
#define TRUE 1

typedef	struct s_redir t_redir;
typedef struct s_envp t_envp;

struct s_redir
{
	int		in;
	int		out;
	t_redir	*next;
	t_redir *prev;
};

struct s_envp
{
	char	*key;
	char	*value;
	t_envp	*next;
	int		cnt;
};

typedef struct s_minishell
{
	char 		**path;
	t_envp		*envp;
	t_redir		*redir;
	int			status;
}				t_minishell;

void	setting_signal(void);
void 	main_loop(t_minishell *minishell);
void	init(t_minishell *minishell, char *envp[]);
void	check_arg(int ac, char *av[]);

//envp
void	init_envp(t_envp **head, char **envp);
char    **envp_to_dptr(t_envp *head);
void    print_envp(t_minishell *minishell);
void	print_sort_envp(t_minishell *minishell);
void    insert_envp(t_envp **node, const char *key, const char *value);
void	export_error_message(char *msg);
// 이거 어따 놓지
void	input_heredoc(t_minishell *minishell, char *limit);
t_redir	*new_redir(void);
#endif
