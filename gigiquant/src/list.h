#ifndef LIST_H
#define LIST_H

// Nod pentru lista de preturi (sau element de stiva/coada)
typedef struct Node {
    double val;
    struct Node *next;
} Node;

// Structura pentru o actiune/oras (necesara de la Task 2 incolo)
typedef struct Stock {
    char name[100];
    Node *prices;        // Lista (sau stiva) de preturi pentru acest oras
    struct Stock *next;  // Pointer catre urmatorul oras din fisier
} Stock;

// Operatii pentru liste de preturi / Stive
Node *createNode(double val);
void addAtEnd(Node **head, double val);
void addAtBeginning(Node **head, double val); // Folosita pentru Stack (Push)
void freeList(Node **head);

// Operatii pentru lista de actiuni
void freeStocks(Stock **head);

#endif