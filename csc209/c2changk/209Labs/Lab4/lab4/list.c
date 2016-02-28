#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

#define STRSIZE 128 /*assume string representation fits*/

/* Return true if the list h is empty
 * and false otherwise.
 */
int is_empty(List *h) {
    return h == NULL;
}

/* Create a list node and return a pointer to it 
 */
List *create_node(int v) {
    List *node = malloc(sizeof(List));
    node->value = v;
    node->next = NULL;
    return node;
}

/* Insert a new node with the value v at the 
 * front of the list. Return the new head of 
 * the list.
 */
List *add_node(List *h, int v) {
    List *node = create_node(v);
    node->next = h;
    return node;
}

/* Remove the first node in the list h that
 * has the value v.  Return the head of the
 * list.
 */
List *remove_node(List *h, int v) {
    List *curr = h;

    /* Handle the cases when list is empty or the value
     * is found at the front of the list */
    if(h == NULL) {
        return h;
    } else if(h->value == v) {
        h = h->next;
        return h;
    }

    /* Look for the value in the list (keeping the pointer to
     * the previous element so that we can remove the right 
     * element) */
    while(curr->next != NULL && curr->next->value != v) {
        curr = curr->next;
    }

    if(curr->next == NULL) { /* v is not in list so do nothing */
        return h;
    } else { /* curr->next->value == v */
        curr->next = curr->next->next;
        return h;
    } 
}

// Return a string representation of the list
char *tostring(List *head) {
    char *str= malloc(STRSIZE);
    char num[4]; /* assume integer has max. four digits*/
    str[0] = '\0';
    while(head != NULL) {
        sprintf(num, "%d", head->value);
        strncat(str, num, STRSIZE - strlen(str) - 1);
        head = head->next;
    }
    return str;
}
