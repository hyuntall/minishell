/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:47:20 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/14 21:01:05 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"

static t_parse_tree *init_parse_tree(void)
{
    t_parse_tree *ret;

    ret = (t_parse_tree *)malloc(sizeof(t_parse_tree));
    ft_memset(ret, 0, sizeof(t_parse_tree));
    ret->type = NORM;
    return (ret);
}


static int  find_tail_from_head(t_token *list, t_token *find, t_token_type type)
{
    //parenthesis check
    ssize_t parenthesis_cnt = 0;
    t_token     *token;

    token = list->head;
    find->head = list->head;
    printf("in find tail from head\n");
    while (token)
    {
        //check parenthesis
        if ((token->type == type) && !parenthesis_cnt)
        {
            find->tail = token;
            return (TRUE);
        }
        token = token->next;
    }
    return (FALSE);
}

static void parse_token(t_parse_tree **parse_tree, t_token *list, t_parse_tree *prev_tree_node)
{
    t_token *find = NULL;
    printf("%s\n", list->head->value);

    //remove parenthesis
    if (find_tail_from_head(list, find, DAND) == TRUE)
    {printf("find head ~ tail\n");
        t_token *token;
        token = find->head;
        while (token)
        {
            printf("%s\t",token->value);
            token = token->next;
        }
        printf("\n");
    }

    if (!(*parse_tree) && list->head)   //single node
    {
        *parse_tree = init_parse_tree();
        (*parse_tree)->token = list->head;
    }
    else
        return ;
    (void)parse_tree;(void)prev_tree_node;
}

t_parse_tree *parser(t_token *token)
{
    t_parse_tree    *parse_tree;
    t_token         *token;
    
    parse_tree = NULL;
    //
    printf("in parser\n");
    token = token->head;
    while (token)
    {
        printf("arg: %10s type: %10d len: %10zu\n", token->value, token->type, ft_strlen(token->value));
        if (token->type == 3)
            printf("<======= $: %s ========>\n", process_dquote(token->value));
        token = token->next;
    }
    printf("======parser tree start========\n");
    parse_token(&parse_tree, token, NULL);
    return (parse_tree);
}
