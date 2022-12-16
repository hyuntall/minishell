/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hanjiwon <hanjiwon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/13 11:47:20 by jiwonhan          #+#    #+#             */
/*   Updated: 2022/12/16 18:02:52 by hanjiwon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "parse_tree.h"
#include "tokenization.h"

int  find_head_from_tail(t_token *tail, t_token **find, t_token_type type)
{printf("in find head from tail\n");
    //parenthesis check
    ssize_t parenthesis_cnt = 0;

    while (tail)
    {
        //check parenthesis
        if ((tail->type == type) && !parenthesis_cnt)
        {
            *find = tail;
            return (TRUE);
        }
        tail = tail->prev;
    }
    *find = NULL;
    return (FALSE);
}

static void go_left_node(t_parse_tree **parse_tree)
{printf("in go left\n");
    t_token         *next_tail;
    t_parse_tree    *prev_tree;

    prev_tree = *parse_tree;
    parse_tree = &((*parse_tree)->left);
    next_tail = get_tail_token((*parse_tree)->token);
    parse_token(parse_tree, &next_tail, prev_tree);
}

static void go_right_node(t_parse_tree **parse_tree)
{printf("in go right\n");
    t_token         *next_tail;
    t_parse_tree    *prev_tree;

    prev_tree = *parse_tree;
    parse_tree = &((*parse_tree)->right);
    next_tail = get_tail_token((*parse_tree)->token);
    parse_token(parse_tree, &next_tail, prev_tree);
}

void parse_token(t_parse_tree **parse_tree, t_token **tail, t_parse_tree *prev_tree)
{
    t_token *find;
    //TODO remove parenthesis
    if (find_head_from_tail(*tail, &find, DAND) == TRUE)
        insert_tree(parse_tree, find, prev_tree);
    else if (find_head_from_tail(*tail, &find, PIPE) == TRUE)
        insert_tree(parse_tree, find, prev_tree);
    /*else if (find_head_from_tail(*tail, &find, DRGT) == TRUE)   //redirection?
        insert_tree(parse_tree, find, prev_tree);*/
    else if (!(*parse_tree) && *tail)   //single node
    {
        *parse_tree = init_parse_tree();
        (*parse_tree)->token = get_head_token(*tail);
        *tail = NULL;
        return ;
    }
    else
        return ;
    //TODO node->left, right
    go_right_node(parse_tree);
    go_left_node(parse_tree);
}


t_parse_tree *parser(t_token *token)
{
    t_parse_tree    *parse_tree;
    t_token         *tail;
    
    parse_tree = NULL;
    tail = get_tail_token(token);
    parse_token(&parse_tree, &tail, NULL);
    return (parse_tree);
}
