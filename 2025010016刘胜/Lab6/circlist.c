#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} CircList;

static Node* newNode(int value) {
    Node* p = (Node*)malloc(sizeof(Node));
    if (p == NULL) {
        printf("malloc failed, exit\n");
        exit(1);
    }
    p->data = value;
    p->next = NULL;
    return p;
}

static void insertAfter(Node* prev, Node* p) {
    p->next = prev->next;
    prev->next = p;
}

static Node* unlinkAfter(CircList* list, Node* prev) {
    if (prev->next == list->head) {
        return NULL;
    }
    Node* p = prev->next;
    prev->next = p->next;
    return p;
}

static Node* prevOf(CircList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
        if (p == list->head) {
            p = p->next;
        }
    }
    return p;
}

static Node* circLast(CircList* list) {
    Node* p = list->head;
    while (p->next != list->head) {
        p = p->next;
    }
    return p;
}

void circInit(CircList* list) {
    list->head = newNode(0);
    list->head->next = list->head;
    list->size = 0;
}

void circDestroy(CircList* list) {
    int count = 0;
    Node* cur = list->head->next;
    while (cur != list->head) {
        Node* next = cur->next;
        free(cur);
        cur = next;
        count++;
    }
    free(list->head);
    count++;
    printf("(circDestroy: freed %d nodes, including the sentinel)\n", count);
}

int circEmpty(const CircList* list) {
    return list->head->next == list->head;
}

void circPrint(const CircList* list) {
    printf("[size = %d] ", list->size);
    for (Node* p = list->head->next; p != list->head; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

int circPushBack(CircList* list, int value) {
    insertAfter(circLast(list), newNode(value));
    list->size++;
    return 1;
}

int circInsert(CircList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) {
        return 0;
    }
    insertAfter(prevOf(list, rank), newNode(value));
    list->size++;
    return 1;
}

int circRemove(CircList* list, int rank, int* removed) {
    if (removed == NULL) {
        return 0;
    }
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    Node* p = unlinkAfter(list, prevOf(list, rank));
    *removed = p->data;
    free(p);
    list->size--;
    return 1;
}

int circFind(const CircList* list, int value) {
    int rank = 0;
    for (Node* p = list->head->next; p != list->head; p = p->next, rank++) {
        if (p->data == value) {
            return rank;
        }
    }
    return -1;
}

void circPrintAround(const CircList* list, int steps) {
    if (circEmpty(list)) {
        printf("(empty)\n");
        return;
    }
    Node* p = list->head->next;
    for (int i = 0; i < steps; i++) {
        printf("%d ", p->data);
        p = p->next;
        if (p == list->head) {
            p = p->next;
        }
    }
    printf("\n");
}

void circJosephus(CircList* list, int k) {
    Node* prev = list->head;
    while (list->size > 0) {
        for (int step = 0; step < k - 1; step++) {
            do {
                prev = prev->next;
            } while (prev == list->head);
        }
        if (prev->next == list->head) {
            prev = prev->next;
        }
        Node* out = unlinkAfter(list, prev);
        printf("%d ", out->data);
        free(out);
        list->size--;
        if (prev->next == list->head) {
            prev = list->head;
        }
    }
    printf("\n");
}

int main() {
    CircList c;
    circInit(&c);

    printf("after init: ");
    circPrint(&c);
    printf("circEmpty = %d\n", circEmpty(&c));
    printf("\n");

    circPushBack(&c, 1);
    circPushBack(&c, 2);
    circPushBack(&c, 3);
    circPushBack(&c, 4);
    circPushBack(&c, 5);
    printf("after circPushBack 1 to 5: ");
    circPrint(&c);
    printf("walk 12 steps around: ");
    circPrintAround(&c, 12);
    printf("\n");

    int ok = circInsert(&c, 2, 25);
    printf("circInsert(2, 25): ok = %d, ", ok);
    circPrint(&c);

    int removed = 0;
    ok = circRemove(&c, 2, &removed);
    printf("circRemove(2): ok = %d, removed = %d, ", ok, removed);
    circPrint(&c);

    ok = circRemove(&c, 4, &removed);
    printf("circRemove(4): ok = %d, removed = %d, ", ok, removed);
    circPrint(&c);

    ok = circPushBack(&c, 5);
    printf("circPushBack(5): ok = %d, ", ok);
    circPrint(&c);
    printf("walk 7 steps around: ");
    circPrintAround(&c, 7);
    printf("\n");

    printf("circFind(4) = %d\n", circFind(&c, 4));
    printf("circFind(99) = %d\n", circFind(&c, 99));

    ok = circInsert(&c, 6, 100);
    printf("circInsert(6, 100): ok = %d\n", ok);
    ok = circRemove(&c, 5, &removed);
    printf("circRemove(5): ok = %d, removed = %d\n", ok, removed);
    printf("\n");

    printf("josephus n = 5, k = 3, out order: ");
    circJosephus(&c, 3);
    printf("after josephus: ");
    circPrint(&c);
    printf("circEmpty = %d\n", circEmpty(&c));
    printf("\n");

    CircList j7;
    circInit(&j7);
    circPushBack(&j7, 1);
    circPushBack(&j7, 2);
    circPushBack(&j7, 3);
    circPushBack(&j7, 4);
    circPushBack(&j7, 5);
    circPushBack(&j7, 6);
    circPushBack(&j7, 7);
    printf("josephus n = 7, k = 2, out order: ");
    circJosephus(&j7, 2);

    CircList j1;
    circInit(&j1);
    circPushBack(&j1, 1);
    printf("josephus n = 1, k = 1, out order: ");
    circJosephus(&j1, 1);

    printf("destroy by hand before main ends:\n");
    circDestroy(&c);
    circDestroy(&j7);
    circDestroy(&j1);

    return 0;
}