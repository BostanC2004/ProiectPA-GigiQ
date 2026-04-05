#ifndef LIST_H
#define LIST_H

typedef struct Node {
    double val;
    struct Node *next;
} Node;

Node *createNode(double val);
void addAtEnd(Node **head, double val);
int getLength(Node *head);
void freeList(Node **head);

#endif