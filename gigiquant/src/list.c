#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"

Node *createNode(double val) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (newNode == NULL) return NULL;
    newNode->val = val;
    newNode->next = NULL;
    return newNode;
}

// Adaugare la final (folosita la Task 1)
void addAtEnd(Node **head, double val) {
    Node *newNode = createNode(val);
    if (*head == NULL) {
        *head = newNode;
        return;
    }
    Node *aux = *head;
    while (aux->next != NULL) aux = aux->next;
    aux->next = newNode;
}

// Adaugare la inceput (Echivalent cu PUSH pentru stiva - util la Task 2)
void addAtBeginning(Node **head, double val) {
    Node *newNode = createNode(val);
    newNode->next = *head;
    *head = newNode;
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

// Elibereaza toata structura de date (Actiuni + Listele lor de preturi)
void freeStocks(Stock **head) {
    Stock *curr = *head;
    while (curr != NULL) {
        Stock *next = curr->next;
        freeList(&(curr->prices)); // Eliberam preturile orasului curent
        free(curr);
        curr = next;
    }
    *head = NULL;
}