#include <stdlib.h>
#include "list.h"

Node *createNode(double val) {
    Node *node = (Node *)malloc(sizeof(Node));
    if (!node) return NULL;
    node->val = val;
    node->next = NULL;
    return node;
}

void addAtEnd(Node **head, double val) {
    Node *node = createNode(val);
    if (!node) return;

    if (*head == NULL) {
        *head = node;
        return;
    }

    Node *p = *head;
    while (p->next != NULL) {
        p = p->next;
    }
    p->next = node;
}

void freeList(Node **head) {
    while (*head != NULL) {
        Node *t = *head;
        *head = (*head)->next;
        free(t);
    }
}