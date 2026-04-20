#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "http_request.h"

#define INITIAL_CAPACITY 8

typedef struct {
    HttpRequest **data; /* Verimli takas (swap) için pointer dizisi */
    int size;           /* Mevcut eleman sayısı */
    int capacity;       /* Ayrılmış toplam bellek alanı */
} PriorityQueue;

/* Kuyruk işlemleri */
PriorityQueue* pq_create(void);
int pq_push(PriorityQueue *pq, HttpRequest *req);
HttpRequest* pq_pop(PriorityQueue *pq);
bool pq_is_empty(const PriorityQueue *pq);
void pq_destroy(PriorityQueue *pq);
void pq_print(const PriorityQueue *pq);

#endif