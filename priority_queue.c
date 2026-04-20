#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>

/* İndeks hesaplama yardımcıları */
static inline int parent(int i) { return (i - 1) / 2; }
static inline int left(int i)   { return 2 * i + 1; }
static inline int right(int i)  { return 2 * i + 2; }

static void swap(HttpRequest **a, HttpRequest **b) {
    HttpRequest *temp = *a;
    *a = *b;
    *b = temp;
}

static void heapify_up(PriorityQueue *pq, int i) {
    while (i > 0 && pq->data[i]->urgency < pq->data[parent(i)]->urgency) {
        swap(&pq->data[i], &pq->data[parent(i)]);
        i = parent(i);
    }
}

static void heapify_down(PriorityQueue *pq, int i) {
    int smallest = i;
    int l = left(i);
    int r = right(i);

    if (l < pq->size && pq->data[l]->urgency < pq->data[smallest]->urgency) smallest = l;
    if (r < pq->size && pq->data[r]->urgency < pq->data[smallest]->urgency) smallest = r;

    if (smallest != i) {
        swap(&pq->data[i], &pq->data[smallest]);
        heapify_down(pq, smallest);
    }
}

PriorityQueue* pq_create(void) {
    PriorityQueue *pq = (PriorityQueue*)malloc(sizeof(PriorityQueue));
    if (!pq) return NULL;
    pq->data = (HttpRequest**)malloc(INITIAL_CAPACITY * sizeof(HttpRequest*));
    pq->size = 0;
    pq->capacity = INITIAL_CAPACITY;
    return pq;
}

int pq_push(PriorityQueue *pq, HttpRequest *req) {
    if (pq->size == pq->capacity) {
        int new_cap = pq->capacity * 2;
        HttpRequest **new_data = (HttpRequest**)realloc(pq->data, new_cap * sizeof(HttpRequest*));
        if (!new_data) return -1;
        pq->data = new_data;
        pq->capacity = new_cap;
    }
    pq->data[pq->size] = req;
    heapify_up(pq, pq->size);
    pq->size++;
    return 0;
}

HttpRequest* pq_pop(PriorityQueue *pq) {
    if (pq->size == 0) return NULL;
    HttpRequest *min = pq->data[0];
    pq->size--;
    if (pq->size > 0) {
        pq->data[0] = pq->data[pq->size];
        heapify_down(pq, 0);
    }
    return min;
}

bool pq_is_empty(const PriorityQueue *pq) { return pq->size == 0; }

void pq_destroy(PriorityQueue *pq) {
    if (!pq) return;
    for (int i = 0; i < pq->size; i++) {
        free(pq->data[i]->path);
        free(pq->data[i]);
    }
    free(pq->data);
    free(pq);
}

void pq_print(const PriorityQueue *pq) {
    printf("[QUEUE] Mevcut bekleyen istekler (Size: %d):\n", pq->size);
    for (int i = 0; i < pq->size; i++) {
        printf("  [%d] ID:%d Urgency:%d Path:%s\n", i, pq->data[i]->id, pq->data[i]->urgency, pq->data[i]->path);
    }
}