#ifndef LIST_H
#define LIST_H

typedef struct Node {
    double val;
    struct Node *next;
} Node;

/* Nod simplu pentru lista de preturi */
Node *createNode(double val);

/* Adauga la final, ca sa pastram ordinea cronologica */
void addAtEnd(Node **head, double val);

/* Elibereaza toata lista */
void freeList(Node **head);

#endif