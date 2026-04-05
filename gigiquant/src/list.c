#include <stdlib.h>
#include "list.h"

Node* createNode(double v) {
    Node *newNode = (Node*)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->val = v;
    newNode->next = NULL;
    return newNode;
}

void addAtEnd(Node **head, double v) {
    Node *newNode = createNode(v);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *temp = *head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = newNode;
}

void freeList(Node **head) {
    Node *temp;
    while (*head != NULL) {
        temp = *head;
        *head = (*head)->next;
        free(temp);
    }
}

int getLength(Node *head) {
    int count = 0;
    while (head != NULL) {
        count++;
        head = head->next;
    }
    return count;
}