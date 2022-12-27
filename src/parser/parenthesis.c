#include "minishell.h"
#include "parse_tree.h"
#include "tokenization.h"
#include "testcode.h"
static int  matching_parenthesis(t_token *token)
{
    int cnt;

    cnt = 1;
    while (token && cnt)
    {
        if (token->type == PARENTHESIS_LEFT)
            ++cnt;
        else if (token->type == PARENTHESIS_RIGHT)
            --cnt;
        token = token->next;
    }
    return (token == NULL);
}

void    remove_tail_token(t_token **tail)
{
    t_token *prev;

    prev = (*tail)->prev;
    if (prev)
        prev->next = NULL;
    free((*tail)->value);
    free(*tail);
    *tail = prev;
}

void    remove_token(t_token **del_token)
{
    t_token *next;

    next = (*del_token)->next;
    if (!next)
    {
        remove_tail_token(del_token);
        return ;
    }
    next->prev = (*del_token)->prev;
    free((*del_token)->value);
    free(*del_token);
    *del_token = next;

}

void    check_parenthesis(t_parse_tree **parse_tree, t_token **tail)
{
    t_token *head;

    head = get_head_token(*tail);
    while (head && (head->type == PARENTHESIS_LEFT) && matching_parenthesis(head->next))
    {
        remove_token(&head);
        remove_token(tail);
        if (*parse_tree)
            (*parse_tree)->token = head;
    }
}