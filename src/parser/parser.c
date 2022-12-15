/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jiwonhan <jiwonhan@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:47:20 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/15 15:58:54 by jiwonhan         ###   ########seoul.kr  */
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


static int  find_tail_from_head(t_token *tokenized, t_token **find, t_token_type type)
{printf("in find tail from head\n");
    //parenthesis check
    ssize_t parenthesis_cnt = 0;

    t_token *head = tokenized;

    while (tokenized)
    {
        //check parenthesis
        if ((tokenized->type == type) && !parenthesis_cnt)
        {
            tokenized->prev->next = NULL;
            (*find) = head;
            return (TRUE);
        }
        tokenized = tokenized->next;
    }
    return (FALSE);
}

/*static void insert_tree(t_parse_tree **parse_tree, t_token *find, t_parse_tree *prev_tree)
{
    t_parse_tree    *new_node;

    new_node = init_parse_tree();

}*/

void parse_token(t_parse_tree **parse_tree, t_token **tokenized, t_parse_tree *prev_tree)
{printf("in parse_token\n");(void)prev_tree;
    t_token *find;
    //TODO remove parenthesis
    if (find_tail_from_head(*tokenized, &find, DAND) == TRUE)
    {
        t_token *tmp = find;    //TODO check find(head ~ tail)
        while (tmp)
        {
            printf("%s\t", tmp->value);
            tmp = tmp->next;
        }printf("\n");  //TODO check find(head ~ tail) end
        printf("%s\n", (*tokenized)->value);
        //insert_tree(parse_tree, find, prev_tree);
    }
    /*else if (find_tail_from_head(*tokenized, &find, PIPE) == TRUE)
        insert_tree(parse_tree, find, prev_tree);
    else if (find_tail_from_head(*tokenized, &find, DRGT) == TRUE)   //redirection?
        insert_tree(parse_tree, find, prev_tree);*/
    if (!(*parse_tree) && *tokenized)   //single node
    {
        *parse_tree = init_parse_tree();
        (*parse_tree)->token = *tokenized;
        *tokenized = NULL;
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
