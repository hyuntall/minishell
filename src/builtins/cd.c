/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:54:00 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/28 22:20:20 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

t_envp	*find_value(t_envp *head, char *key)
{
	while (head && ft_strncmp(head->key, key, ft_strlen(key) + 1))
		head = head->next;
	return (head);
}

void	update_path(t_envp **head, char *key, char *value)
{
	while (*head && ft_strncmp((*head)->key, key, ft_strlen(key) + 1))
		head = &((*head)->next);
	if (*head)
	{
		free((*head)->value);
		(*head)->value = ft_strdup(value);
	}
}

void	go_to_home(t_envp *envp)
{
	t_envp	*home;
	char	*currentpwd;

	home = find_value(envp, "HOME");
	if (!home)
		return ;
	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD", currentpwd);
	update_path(&envp, "PWD", home->value);
	free(currentpwd);
}

void	go_to_oldpwd(t_envp *envp)
{
	t_envp	*oldpwd;
	char	*currentpwd;

	oldpwd = find_value(envp, "OLDPWD");
	if (!oldpwd)
		return ;
	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD", currentpwd);
	update_path(&envp, "PWD", oldpwd->value);
	free(currentpwd);

}

void	go_to_new(t_envp *envp, char *path)
{
	char	*currentpwd;
	char	*new_path;

	new_path = NULL;
	//TODO new_path check
	currentpwd = getcwd(NULL, 0);
	if (!new_path)
		new_path = ft_strdup(path);
	update_path(&envp, "OLDPWD", currentpwd);
	update_path(&envp, "PWD", new_path);
	free(currentpwd);
	free(new_path);
}

void	cd(t_minishell *minishell, char **arr)
{
	printf(">>Before\nHOME=%s\nPWD=%s\nOLDPWD=%s\n", find_value(minishell->envp, "HOME")->value, find_value(minishell->envp, "PWD")->value, find_value(minishell->envp, "OLDPWD")->value);
	if (!arr[1])
		go_to_home(minishell->envp);
	else if (!ft_strncmp(arr[1], "-", 1))
		go_to_oldpwd(minishell->envp);
	else
		go_to_new(minishell->envp, arr[1]);
	printf(">>After\nHOME=%s\nPWD=%s\nOLDPWD=%s\n", find_value(minishell->envp, "HOME")->value, find_value(minishell->envp, "PWD")->value, find_value(minishell->envp, "OLDPWD")->value);
}
