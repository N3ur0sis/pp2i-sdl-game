#include "List.h"

void free_list(List *Liste) {
    List *current = Liste;
    while (current != NULL) {
        List *next = current->next;
        free(current);
        current = next;
    }
}

List *create_list(int val, List *next){
    List *res = malloc(sizeof(List));
    res->val = val;
    res->next = next;
    return res;
}

void printL(List *L){
    if (L==NULL){
        printf("[]");
        return;
    }
    List *next=L->next;
    printf("[%d",L->val);
    while (next){
        printf(", %d",next->val);
        next=next->next;
    }
    printf("]\n");
}

int len(List *lis){
    List *l = lis;
    if (l==NULL){
        return 0;
        }
    else{ 
        return 1+len(l->next);
    }
}



void append(List **head, int value) {
    List *new_node = malloc(sizeof(List));
    if (new_node == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire\n");
        exit(EXIT_FAILURE);
    }
    new_node->val = value;
    new_node->next = NULL;

    if (*head == NULL) {
        *head = new_node;
        return;
    }

    List *current = *head;
    while (current->next != NULL) {
        current = current->next;
    }
    current->next = new_node;
}
void removeLast(List **head) {
    if (*head == NULL) {
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }

    List *current = *head;
    List *prev = NULL;
    while (current->next != NULL) {
        prev = current;
        current = current->next;
    }
    free(current);
    if (prev != NULL) {
        prev->next = NULL;
    } else {
        *head = NULL;
    }
}
