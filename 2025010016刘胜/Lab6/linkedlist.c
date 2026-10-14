#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node* next;
} Node;

typedef struct {
    Node* head;
    int size;
} LinkedList;

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

static Node* unlinkAfter(Node* prev) {
    Node* p = prev->next;
    prev->next = p->next;
    return p;
}

static Node* prevOf(const LinkedList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
    }
    return p;
}

void listInit(LinkedList* list) {
    list->head = newNode(0);
    list->size = 0;
}

void listDestroy(LinkedList* list) {
    int count = 0;
    Node* p = list->head;
    while (p != NULL) {
        Node* next = p->next;
        free(p);
        p = next;
        count++;
    }
    printf("(listDestroy: freed %d nodes, including the sentinel)\n", count);
}

int listSize(const LinkedList* list) {
    return list->size;
}

int listEmpty(const LinkedList* list) {
    return list->size == 0;
}

void listPrint(const LinkedList* list) {
    printf("[size = %d] ", list->size);
    for (Node* p = list->head->next; p != NULL; p = p->next) {
        printf("%d ", p->data);
    }
    printf("\n");
}

int listInsert(LinkedList* list, int rank, int value) {
    if (rank < 0 || rank > list->size) {
        return 0;
    }
    insertAfter(prevOf(list, rank), newNode(value));
    list->size++;
    return 1;
}

int listRemove(LinkedList* list, int rank, int* removed) {
    if (removed == NULL) {
        return 0;
    }
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    Node* p = unlinkAfter(prevOf(list, rank));
    *removed = p->data;
    free(p);
    list->size--;
    return 1;
}

int listGet(const LinkedList* list, int rank, int* value) {
    if (value == NULL) {
        return 0;
    }
    if (rank < 0 || rank >= list->size) {
        return 0;
    }
    *value = prevOf(list, rank)->next->data;
    return 1;
}

int listFind(const LinkedList* list, int value) {
    int rank = 0;
    for (Node* p = list->head->next; p != NULL; p = p->next, rank++) {
        if (p->data == value) {
            return rank;
        }
    }
    return -1;
}

int listPushBack(LinkedList* list, int value) {
    return listInsert(list, list->size, value);
}

int listPushFront(LinkedList* list, int value) {
    return listInsert(list, 0, value);
}

int main() {
    LinkedList list;
    LinkedList empty;

    listInit(&list);
    listInit(&empty);

    printf("after init: ");
    listPrint(&list);
    printf("listEmpty = %d, listSize = %d\n", listEmpty(&list), listSize(&list));
    printf("\n");

    listPushBack(&list, 18);
    listPushBack(&list, -1);
    listPushBack(&list, 42);
    listPushBack(&list, 18);
    listPushBack(&list, 65);
    printf("after listPushBack 18, -1, 42, 18, 65: ");
    listPrint(&list);
    printf("\n");

    int ok = listInsert(&list, 2, 25);
    printf("listInsert(2, 25): ok = %d, ", ok);
    listPrint(&list);

    int removed = 0;
    ok = listRemove(&list, 1, &removed);
    printf("listRemove(1): ok = %d, removed = %d, ", ok, removed);
    listPrint(&list);

    ok = listPushFront(&list, 7);
    printf("listPushFront(7): ok = %d, ", ok);
    listPrint(&list);
    printf("\n");

    int value = 777;
    ok = listGet(&list, 0, &value);
    printf("listGet(0): ok = %d, value = %d\n", ok, value);
    value = 777;
    ok = listGet(&list, 6, &value);
    printf("listGet(6): ok = %d, value = %d\n", ok, value);
    printf("\n");

    printf("listFind(42) = %d\n", listFind(&list, 42));
    printf("listFind(18) = %d\n", listFind(&list, 18));
    printf("listFind(99) = %d\n", listFind(&list, 99));
    printf("\n");

    ok = listInsert(&list, -1, 100);
    printf("listInsert(-1, 100): ok = %d\n", ok);
    ok = listInsert(&list, 100, 100);
    printf("listInsert(100, 100): ok = %d\n", ok);
    ok = listRemove(&empty, 0, &removed);
    printf("empty listRemove(0): ok = %d\n", ok);
    printf("\n");

    printf("before destroy: ");
    listPrint(&list);
    printf("destroy by hand before main ends, empty first, then list:\n");
    listDestroy(&empty);
    listDestroy(&list);

    return 0;
}