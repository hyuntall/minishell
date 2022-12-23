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

void    check_parenthesis(t_parse_tree **parse_tree, t_token **tail)
{
    t_token *head;

    head = get_head_token(*tail);
    while (head && (head->type == PARENTHESIS_LEFT))
    {
        if (matching_parenthesis(head->next))
        {
            delete_token(head);
            delete_token(*tail);
            if (*parse_tree)
                (*parse_tree)->token = head;
        }
        print_node(head);
    }
}