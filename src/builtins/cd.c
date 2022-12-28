/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/24 23:54:00 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/28 21:10:45 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "cmd.h"

/*char	*find_value(char **envp, char *find)
{
	int	i;
	int	j;

	i = -1;
	while (envp[++i])
		if (!ft_strncmp(envp[i], find, ft_strlen(find)))
		{
			j = -1;
			while (find[++j] && envp[i][j] && find[j] == envp[i][j]) ;
			return (&envp[i][j]);
		}
	return (NULL);
}

void	update_path(char ***envp, char *key, char *value)
{
	int	i;
	char	*ret;

	i = -1;
	while ((*envp)[++i])
	{
		if (!ft_strncmp((*envp)[i], key, ft_strlen(key)))
		{
			ret = ft_strdup(ft_strjoin(key, value));
			(*envp)[i] = ret;
			printf("\t%s\n", (*envp)[i]);
			return ;
		}
	}
}

void	go_to_home(char **envp)
{
	char	*home;
	char	*currentpwd;

	home = find_value(envp, "HOME=");
	if (!home)
		return ;
	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD=", currentpwd);
	update_path(&envp, "PWD=", home);
	home = find_value(envp, "HOME=");
	free(currentpwd);
}

void	go_to_oldpwd(char **envp)
{
	char	*oldpwd;
	char	*currentpwd;

	oldpwd = find_value(envp, "OLDPWD=");
	if (!oldpwd)
		return ;
	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD=", currentpwd);
	update_path(&envp, "PWD=", oldpwd);
	printf("%s\n", oldpwd);
	free(currentpwd);

}

void	go_to_new(char **envp, char *path)
{
	char	*currentpwd;

	currentpwd = getcwd(NULL, 0);
	update_path(&envp, "OLDPWD=", currentpwd);
	update_path(&envp, "PWD=", path);
	free(currentpwd);
}*/

void	cd(t_minishell *minishell, char **arr)
{(void)minishell;(void)arr;
	/*printf("HOME=%s\nPWD=%s\nOLDPWD=%s\n", find_value(minishell->envp, "HOME="), find_value(minishell->envp, "PWD="), find_value(minishell->envp, "OLDPWD="));
	if (!arr[1])
		go_to_home(minishell->envp);
	else if (!ft_strncmp(arr[1], "-", 1))
		go_to_oldpwd(minishell->envp);
	else
		go_to_new(minishell->envp, arr[1]);
	printf("\n\nHOME=%s\nPWD=%s\nOLDPWD=%s\n", find_value(minishell->envp, "HOME="), find_value(minishell->envp, "PWD="), find_value(minishell->envp, "OLDPWD="));*/
}
