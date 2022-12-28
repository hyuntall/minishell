/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   setting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/09 20:59:14 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/28 18:49:59 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_arg(int ac, char *av[])
{
	if (ac != 1)
	{
		ft_putstr_fd("minishell: ", 2);
		ft_putstr_fd(av[1], 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		exit(-1);
	}
}

char **get_env_path(char **envp)
{
	char	**path;
	char	**temp;
	char	*tmp;

	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	path = ft_split(*envp + 5, ':');
	temp = path;
	while (*temp)
	{
		tmp = *temp;
		if (tmp[ft_strlen(tmp) - 1] != '/')
		{
			*temp = ft_strjoin(*temp, "/");
			free(tmp);
		}
		temp++;
	}
	return (path);
}

t_redir	*new_redir(void)
{
	t_redir	*new_redir;

	new_redir = malloc(sizeof(t_redir));
	new_redir->in = 0;
	new_redir->out = 0;
	new_redir->next = NULL;
	return (new_redir);
}

void	init(t_minishell *minishell, char *envp[])
{
	//minishell->envp = envp;
	minishell->path = get_env_path(envp);
	minishell->status = 0;
	init_envp(&(minishell->envp), envp);
	t_envp *tmp = minishell->envp;
	while (tmp)
	{
		printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
	setting_signal();
}
