#include <stdlib.h>
#include "../include/node.h"

typedef struct list {
    node *head;
    node *tail;
    node *curr;
    int length;
} linked_list; 

linked_list* ll_create_list() {
    linked_list *l;
    
    l = (linked_list*) malloc(sizeof (linked_list));
    if (l == NULL) {
        return NULL;
    }
    l->head = l->tail = l->curr = ll_create_node(NULL, 0);
    l->length = 0;

    return l;
}

int ll_insert(linked_list *l, int element) {
    node *n;

    n = create_node(l->curr->next_node, element);
    if (n == NULL) {
        return -1;
    }
    l->curr->next_node = n;
    if (l->tail == l->curr) {
        l->tail = l->curr->next_node; // l->tail->next_node == NULL
    }
    l->length++;

    return 0;
}

int ll_append(linked_list *l, int element) {
    node *n;
    
    n = create_node(NULL, element);
    if (n == NULL) {
        return -1;
    }
    l->tail->next_node = n; 
    l->tail = l->tail->next_node;
    l->length++;

    return 0;
}

int ll_pop(linked_list *l) {
    if (l->curr->next_node == NULL) {
        return -1;
    }

    int element;
    node *n;
    
    element = l->curr->next_node->element;
    n = l->curr->next_node;
    if (l->tail == l->curr->next_node) {
        l->tail = l->curr;
    }
    l->curr->next_node = l->curr->next_node->next_node;
    l->length--;
    free(n);

    return element;
}

void ll_clear(linked_list *l) {
    node *n;

    l->tail = l->curr = l->head;
    while(l->head->next_node != NULL) {
        n = l->head->next_node;
        l->head->next_node = l->head->next_node->next_node;
        free(n);
    }
    l->length = 0;
}

void ll_move_to_start(linked_list *l) {
    l->curr = l->head;
}

void ll_move_to_end(linked_list *l) {
    l->curr = l->tail;
}

int ll_move_to_position(linked_list *l, int p) {
    if (p >= l->length) {
        return -1;
    }

    int i;

    i = 0;
    l->curr = l->head;
    while(i < p) {
        l->curr = l->curr->next_node;
        i++;
    }

    return 0;
}

int ll_previous(linked_list *l) {
    if (l->curr == l->head) {
        return -1;
    }

    node *n;
    
    n = l->head;
    while(n->next_node != l->curr) {
        n = n->next_node;
    }
    l->curr = n;

    return 0;
}

int ll_next(linked_list *l) {
    if(l->curr == l->tail) {
        return -1;
    }

    l->curr = l->curr->next_node;

    return 0;
}

int ll_length(linked_list *l) {
    return l->length;
}

int ll_curr_position(linked_list *l) {
    if (l->curr == l->head) {
        return 0;
    }

    int i;
    node *n;

    i = 0;
    n = l->head;
    while(n->next_node != l->curr) {
        n = n->next_node;
        i++;
    }

    return i;
}

int ll_get_value(linked_list *l) {
    if (l->length <= 0) {
        return -1;
    }

    return l->curr->element;
}

void ll_delete_list(linked_list *l) {
    ll_clear(l);
    free(l->head);
    free(l);
}
