#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* TODO: What if malloc returned NULL? */
    if (!q)
        return NULL;
    q->head = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* TODO: How about freeing the list elements and the strings? */
    if (!q)
        return;
    list_ele_t *current = q->head, *prev = NULL;
    while (current) {
        prev = current;
        current = current->next;
        free(prev->value);
        free(prev);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh;
    /* TODO: What should you do if the q is NULL? */
    if (!q)
        return false;
    newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    int len = strlen(s);
    newh->value = malloc((len + 1) * sizeof(char));
    if (!(newh->value)) {
        free(newh);
        return false;
    }
    for (int i = 0; i < len; i++) {
        newh->value[i] = s[i];
    }
    newh->value[len] = '\0';
    if (!(q->head))
        q->tail = newh;
    newh->next = q->head;
    q->head = newh;
    q->size += 1;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* TODO: You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    list_ele_t *newt;
    if (!q)
        return false;
    newt = malloc(sizeof(list_ele_t));
    if (!newt)
        return false;
    int len = strlen(s);
    newt->value = malloc((len + 1) * sizeof(char));
    if (!(newt->value)) {
        free(newt);
        return false;
    }
    for (int i = 0; i < len; i++) {
        newt->value[i] = s[i];
    }
    newt->value[len] = '\0';
    if (!(q->tail))
        q->head = newt;
    (q->tail)->next = newt;
    q->tail = newt;
    newt->next = NULL;
    q->size += 1;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* TODO: You need to fix up this code. */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !(q->head))
        return false;
    list_ele_t *tmp = q->head;
    q->head = q->head->next;
    if (sp) {
        for (int i = 0; i < bufsize - 1; i++) {
            sp[i] = tmp->value[i];
        }
        sp[bufsize - 1] = '\0';
    }
    free(tmp->value);
    free(tmp);
    if (!(q->head))
        q->tail = NULL;
    q->size -= 1;
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    /* TODO: Remove the above comment when you are about to implement. */
    return q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (q && q->head) {
        list_ele_t *current = q->head, *prev = NULL, *tmp = NULL;
        while (current) {
            tmp = current->next;
            current->next = prev;
            prev = current;
            current = tmp;
        }
        tmp = q->head;
        q->head = q->tail;
        q->tail = tmp;
    }
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
    if (!q || !(q->head) || !((q->head)->next))
        return;
    // find mid
    queue_t left, right;
    list_ele_t *slow = q->head, *fast = q->head;
    while (fast && fast->next) {
        fast = (fast->next)->next;
        slow = slow->next;
    }
    left.head = q->head;
    right.head = slow;
    // recursive sort
    q_sort(&left);
    q_sort(&right);
    // merge two list
    list_ele_t *current1 = left.head, *current2 = right.head;
    list_ele_t *newhead = NULL, *newtail = NULL;
    while (current1 && current2) {
        int len1 = strlen(current1->value);
        int len2 = strlen(current2->value);
        if (len1 < len2) {
            if (newhead) {
                newtail->next = current1;
            } else {
                newhead = current1;
            }
            newtail = current1;
            current1 = current1->next;
        } else if (len1 > len2) {
            if (newhead) {
                newtail->next = current2;
            } else {
                newhead = current2;
            }
            newtail = current2;
            current2 = current2->next;
        } else {
            for (int i = 0; i < len1; i++) {
                if (current1->value[i] <= current2->value[i]) {
                    if (newhead) {
                        newtail->next = current1;
                    } else {
                        newhead = current1;
                    }
                    newtail = current1;
                    current1 = current1->next;
                } else {
                    if (newhead) {
                        newtail->next = current2;
                    } else {
                        newhead = current2;
                    }
                    newtail = current2;
                    current2 = current2->next;
                }
            }
        }
    }
    if (current1) {
        while (current1) {
            newtail->next = current1;
            newtail = current1;
            current1 = current1->next;
        }
    } else {
        while (current2) {
            newtail->next = current2;
            newtail = current2;
            current2 = current2->next;
        }
    }
    q->head = newhead;
    q->tail = newtail;
}
