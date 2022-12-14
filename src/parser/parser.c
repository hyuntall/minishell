/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:47:20 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/14 22:38:49 by hanjiwon         ###   ########.fr       */
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


/*static int  find_tail_from_head(t_token *head, t_token **find, t_token_type type)
{
    //parenthesis check
    ssize_t parenthesis_cnt = 0;
    printf("in find tail from head\n");
    t_token *tmp;
    while (head)
    {
        tmp = head;
        tmp->next = NULL;
        //check parenthesis
        if ((head->type == type) && !parenthesis_cnt)
        {

            return (TRUE);
        }
        head = head->next;
    }
    return (FALSE);
}*/

/*static void insert_tree(t_parse_tree **parse_tree, t_token *find, t_parse_tree *prev_tree)
{
    t_parse_tree    *new_node;

    new_node = init_parse_tree();

}*/

void parse_token(t_parse_tree **parse_tree, t_token **head, t_parse_tree *prev_tree)
{printf("in parse_token\n");(void)prev_tree;
    //t_token *find;
    //TODO remove parenthesis
    /*if (find_tail_from_head(*head, &find, DAND) == TRUE)
    {
        t_token *tmp = find;
        while (tmp)
        {
            printf("%s\t", tmp->value);
            tmp = tmp->next;
        }
    }
        //insert_tree(parse_tree, find, prev_tree);
    else if (find_tail_from_head(*head, &find, PIPE) == TRUE)
        insert_tree(parse_tree, find, prev_tree);
    else if (find_tail_from_head(*head, &find, DRGT) == TRUE)   //redirection?
        insert_tree(parse_tree, find, prev_tree);
    else */
    if (!(*parse_tree) && *head)   //single node
    {
        *parse_tree = init_parse_tree();
        (*parse_tree)->token = *head;
        *head = NULL;
        return ;
    }
    else
        return ;
    //TODO node->left, right
}

t_parse_tree *parser(t_token *token)
{printf("in parser\n");
    t_parse_tree    *parse_tree;
    
    parse_tree = NULL;
    parse_token(&parse_tree, &token, NULL);
    return (parse_tree);
}
