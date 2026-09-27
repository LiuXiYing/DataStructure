#include <stdio.h>
#include <stdlib.h>

/* 结点与单链表完全相同 */
typedef struct Node {
    int data;
    struct Node* next;
} Node;

/* 循环链表的约定：最后一个结点的 next 指回 head；空表时 head->next == head */
typedef struct {
    Node* head;         /* 头哨兵，它也在圈上 */
    int size;           /* 有效结点个数，不含哨兵 */
} CircList;

/* --------------------------------------------------------------------------
 * 教师提供：结点级操作，与 linkedlist.c 对照
 * -------------------------------------------------------------------------- */

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

/* 与单链表完全相同的两句 */
static Node* insertAfter(Node* prev, int value) {
    Node* p = newNode(value);
    p->next = prev->next;
    prev->next = p;
    return p;
}

/* 摘下 prev 后面的结点并返回它；prev 后面是哨兵时返回 NULL。只改指针，不释放。
 * 与单链表的差别只有一处：判断的不再是 NULL，而是 head */
static Node* unlinkAfter(const CircList* list, Node* prev) {
    Node* p = prev->next;
    if (p == list->head) {
        return NULL;
    }
    prev->next = p->next;
    return p;
}

/* 秩为 rank 的结点的前驱，与单链表一字不差 */
static Node* prevOf(const CircList* list, int rank) {
    Node* p = list->head;
    for (int i = 0; i < rank; i++) {
        p = p->next;
    }
    return p;
}

/* 练习 1：最后一个有效结点。从哨兵出发，走到"next 是哨兵"的那个结点为止；空表时返回 head 本身 */
static Node* circLast(const CircList* list) {
    return list->head;  /* TODO */
}

/* --------------------------------------------------------------------------
 * 教师提供：建立与销毁
 * -------------------------------------------------------------------------- */

/* 建立空表：立哨兵，并让它指向自己，圈就成立了 */
void circInit(CircList* list) {
    list->head = newNode(0);
    list->head->next = list->head;
    list->size = 0;
}

/* 逐个摘下并释放，最后释放哨兵。末尾的输出原样保留 */
void circDestroy(CircList* list) {
    int count = 0;
    while (list->size > 0) {
        Node* p = unlinkAfter(list, list->head);
        free(p);
        list->size--;
        count++;
    }
    free(list->head);
    list->head = NULL;
    printf("(circDestroy: freed %d nodes, including the sentinel)\n", count + 1);
}

int circSize(const CircList* list) {
    return list->size;
}

/* --------------------------------------------------------------------------
 * 学生练习
 * -------------------------------------------------------------------------- */

/* 练习 2：空表判断。不许用 size，用指针关系判断 */
int circEmpty(const CircList* list) {
    return 1;   /* TODO：head->next 是否等于 head */
}

/* 练习 3：遍历。从 head->next 出发，回到 head 就停；写成 p != NULL 会死循环 */
void circPrint(const CircList* list) {
    printf("[size = %d] ", list->size);
    /* TODO */
    printf("\n");
}

/* 练习 4：追加到表尾。在 circLast 后面插入，size 加一，返回 1 */
int circPushBack(CircList* list, int value) {
    return 0;   /* TODO：insertAfter(circLast(list), value)；size 加一 */
}

/* 练习 5：按秩插入，合法范围 0 <= rank <= size。与 listInsert 一字不差 */
int circInsert(CircList* list, int rank, int value) {
    return 0;   /* TODO */
}

/* 练习 6：按秩删除，合法范围 0 <= rank < size。与 listRemove 只差 unlinkAfter 多传一个 list */
int circRemove(CircList* list, int rank, int* value) {
    return 0;   /* TODO */
}

/* 练习 7：按值查找，返回第一次出现的秩，找不到返回 -1。停止条件是 head，不是 NULL */
int circFind(const CircList* list, int value) {
    return -1;  /* TODO */
}

/* 练习 8：从第一个结点出发连续走 steps 步，每到一个结点输出它的 data；走到哨兵就跳过哨兵
 * 走的步数可以超过 size，用来证明这是一个圈。空表时输出 (empty) */
void circPrintAround(const CircList* list, int steps) {
    printf("walk %d steps around: ", steps);
    /* TODO */
    printf("\n");
}

/* 练习 9：约瑟夫问题。从第一个结点开始报 1，报到 k 的结点出列（摘下、输出、释放），
 * 从它的下一个结点重新报 1，直到全部出列。哨兵不参与报数，走到它就跳过
 * 提示：维护"下一个报 1 的结点的前驱"prev，初始为 head；出列用 unlinkAfter(list, prev) */
void circJosephus(CircList* list, int k) {
    printf("josephus n = %d, k = %d, out order: ", list->size, k);
    /* TODO */
    printf("\n");
}