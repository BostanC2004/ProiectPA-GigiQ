#ifndef LIST_H
#define LIST_H

typedef struct Node {
    double val;
    struct Node *next;
} Node;

Node* createNode(double v);
void addAtEnd(Node **head, double v);
void freeList(Node **head);
int getLength(Node *head);

#endif