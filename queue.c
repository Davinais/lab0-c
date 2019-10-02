/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    /* What if malloc returned NULL? */
    if (!q) {
        return NULL;
    }
    q->head = NULL;
    q->tail = NULL;
    q->size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    /* How about freeing the list elements and the strings? */
    /* Free queue structure */
    if (!q) {
        return;
    }
    list_ele_t *item = q->head;
    list_ele_t *tmp = NULL;
    while ((tmp = item)) {
        free(item->value);
        item = item->next;
        free(tmp);
    }
    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (!q) {
        return false;
    }
    list_ele_t *newh;
    /* What should you do if the q is NULL? */
    newh = malloc(sizeof(list_ele_t));
    /* Don't forget to allocate space for the string and copy it */
    /* What if either call to malloc returns NULL? */
    if (!newh) {
        return false;
    }
    // Alloc for string
    size_t len = (strlen(s) + 1);
    newh->value = malloc(len);
    if (!(newh->value)) {
        free(newh);
        return false;
    }
    memcpy(newh->value, s, len);
    // Insert to head
    newh->next = q->head;
    // If the queue was empty, we need to revise tail too
    if (q_is_empty(q)) {
        q->tail = newh;
    }
    q->head = newh;
    q->size++;
    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    /* You need to write the complete code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return false;
    }
    list_ele_t *newt;
    newt = malloc(sizeof(list_ele_t));
    if (!newt) {
        return false;
    }
    // Alloc for string
    size_t len = (strlen(s) + 1);
    newt->value = malloc(len);
    if (!(newt->value)) {
        free(newt);
        return false;
    }
    memcpy(newt->value, s, len);
    // Insert to tail
    newt->next = NULL;
    // If the queue was empty, we need to revise head too
    // And also we only need to revise tail->next if q was not empty
    if (q_is_empty(q)) {
        q->head = newt;
    } else {
        q->tail->next = newt;
    }
    q->tail = newt;
    q->size++;
    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    /* You need to fix up this code. */
    if ((!q) || q_is_empty(q)) {
        return false;
    }
    list_ele_t *old_head = q->head;
    q->head = q->head->next;
    if (!!sp && bufsize > 0) {
        memcpy(sp, old_head->value, bufsize - 1);
        sp[bufsize - 1] = '\0';
    }
    free(old_head->value);
    free(old_head);
    q->size--;
    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    /* You need to write the code for this function */
    /* Remember: It should operate in O(1) time */
    if (!q) {
        return 0;
    }
    return q->size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    /* You need to write the code for this function */
    if ((!q) || q_is_empty(q)) {
        return;
    }
    list_ele_t *prev = NULL;
    list_ele_t *tmp = NULL;
    list_ele_t *current = q->head;
    while (current) {
        tmp = current->next;
        current->next = prev;
        prev = current;
        current = tmp;
    }
    tmp = q->tail;
    q->tail = q->head;
    q->head = tmp;
}
