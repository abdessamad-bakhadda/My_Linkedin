#include "liste.h"

#include <assert.h>
#include <stddef.h>
#include <stdlib.h>

node* l_make_node(void* data)
{
    node* noeud = (node*)malloc(sizeof(node)) ;
    noeud->data = data ;
    noeud->next = NULL ;
    noeud->previous = NULL ;
    return noeud ;
}

void l_free_node(node* n)
{
    if(n) free(n) ;
    return ;
}

void l_free_list(node* n)
{
    node*tmp ;
    tmp = n ;
    while(tmp){
        l_free_node(tmp) ;
        tmp = tmp->next ;
    }
    return;
}

int l_length(node const* n)
{
    int cmpt = 0 ;
    node* tmp ;
    if (n){
        tmp = n ;
        while(tmp){
            cmpt++ ;
            tmp = tmp->next ;
        }
        tmp = n->previous ;
        while(tmp){
            cmpt++ ;
            tmp = tmp->previous ;
        }
    }
    return cmpt ;
}

node* l_head(node* n)
{
    node* tmp = NULL ;
    if (n){
        tmp = n ;
        while(tmp->previous) tmp = tmp->previous ;
    }
    return tmp ;
}

node* l_tail(node* n)
{
    node*tmp = NULL ;
    if (n){
        tmp = n ;
        while(tmp->next) tmp = tmp->next ;
    }
    return tmp ;
}

node* l_skip(node* n, int i)
{
    int j ;
    node* tmp = NULL ;
    if (n){
        j= 0 ;
        tmp = n ;
        while(tmp && j< abs(i)){
            if (i>0) tmp = tmp->next ;
            else tmp = tmp->previous ;
            j++ ;
        }
    }
    return tmp ;
}

node* l_append(node** p, node* tail)
{
    assert(p);
    node *tmp = l_tail(*p) ;
    if (tmp) {
      tmp->next = tail ;
    }
    else *p = tail ;
    tail->previous = tmp ;
    tail->next = NULL ;
    return tail ;
}

node* l_prepend(node** p, node* head)
{
    assert(p);
    node *tmp = l_head(*p) ;
    if (tmp) {
      tmp->previous = head ;
    }
    else *p = head ;
    head->previous = NULL ;
    head->next = tmp ;
    return head ;
}

node* l_insert(node** p, node* body)
{
    assert(p);
    if (*p){
      body->previous = *p ;
      body->next = (*p)->next ;
      if ((*p)->next) (*p)->next->previous = body ;
      (*p)->next = body ;

    }
    else {
      *p = body ;
      body->next = NULL ;
      body->previous = NULL ;
    }
    return body ;
}


node* l_remove(node* n)
{
    node* tmp = NULL ;
    if (n){
        if (n->previous) n->previous->next = n->next ;
        if (n->next) n->next->previous = n->previous ;
        tmp = n->next ;
        l_free_node(n) ;
    }
    return tmp ;
}
