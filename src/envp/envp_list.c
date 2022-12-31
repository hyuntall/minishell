/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/28 18:29:36 by hanjiwon          #+#    #+#             */
/*   Updated: 2022/12/30 21:26:49 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    get_key(t_envp *node, const char *envp)
{
    int len;

    len = 0;
    while (envp[len] && envp[len] != '=')
        ++len;
    node->key = ft_substr(envp, 0, len);
}

void    get_value(t_envp *node, const char *envp)
{
    int len;

    len = ft_strlen(envp) - ft_strlen(node->key) - 1;
    node->value = ft_substr(envp, ft_strlen(node->key) + 1, len);
}

char    **envp_to_dptr(t_envp *head)
{
    char    **ret;
    char    *str;
    int     i;

    ret = malloc(sizeof(char *) * (head->cnt + 1));
    i = 0;
    while (head)
    {
        ret[i] = ft_strjoin(head->key, "=");
        str = ft_strjoin(ret[i], head->value);
        free(ret[i]);
        ret[i] = str;
        head = head->next;
        ++i;
    }
    ret[i] = NULL;
    return (ret);
}

void	init_envp(t_envp **node, char **envp)
{
	int		i;
    t_envp  **head;
    
    head = node;
	i = 0;
	while (envp[i])
	{
		*node = malloc(sizeof(t_envp));
		(*node)->next = NULL;
		get_key(*node, envp[i]);
		get_value(*node, envp[i]);
		node = &((*node)->next);
		++i;
	}
	*node = NULL;
    (*head)->cnt = i;
}

void    insert_envp(t_envp **node, const char *key, const char *value)
{
    t_envp  *new;
    t_envp  *head;

    head = *node;
    while (*node && ft_strncmp((*node)->key, key, ft_strlen(key) + 1))
		node = &((*node)->next);
	if (*node)
	{
		free((*node)->value);
        if (value)
		    (*node)->value = ft_strdup(value);
        else
            (*node)->value = NULL;
	}
    new = malloc(sizeof(t_envp));
    if (!new)
        return ;
    new->key = ft_strdup(key);
    if (value)
        new->value = ft_strdup(value);
    else
        new->value = NULL;
    new->next = NULL;
    *node = new;
    head->cnt += 1;
}

void    delete_envp(t_envp **node, const char *key)
{
    t_envp  *head;
    t_envp  *tmp;

    head = *node;
    while (*node && ft_strncmp((*node)->key, key, ft_strlen(key) + 1))
        node = &((*node)->next);
    if (*node)
    {
        tmp = *node;
        *node = (*node)->next;
        free(tmp->key);
        free(tmp->value);
        free(tmp);
        head->cnt--;
    }
}