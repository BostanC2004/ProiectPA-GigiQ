#include <stdio.h>
#include <stdlib.h>
#include "list.h"

Node *createNode(double val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) {
        return NULL;
    }
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

void addAtEnd(Node **head, double val) {
    Node *newNode = createNode(val);
    if (newNode == NULL) {
        exit(1);
    }

    if (*head == NULL) {
        *head = newNode;
        return;
    }

    Node *aux = *head;
    while (aux->next != NULL) {
        aux = aux->next;
    }
    aux->next = newNode;
}

int getLength(Node *head) {
    int len = 0;
    while (head != NULL) {
        len++;
        head = head->next;
    }
    return len;
}

void freeList(Node **head) {
    Node *curr = *head;
    while (curr != NULL) {
        Node *next = curr->next;
        free(curr);
        curr = next;
    }
    *head = NULL;
}