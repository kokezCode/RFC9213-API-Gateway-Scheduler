#include "scheduler.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Scheduler* scheduler_init(void) {
    Scheduler *s = (Scheduler*)malloc(sizeof(Scheduler));
    s->queue = pq_create();
    s->next_id = 1;
    s->total_processed = 0;
    s->total_errors = 0;
    return s;
}

int scheduler_add_request(Scheduler *s, const char *header, const char *path) {
    HttpRequest *req = (HttpRequest*)malloc(sizeof(HttpRequest));
    req->id = s->next_id++;
    req->path = strdup(path ? path : "/");

    ParseResult res = rfc_parse(header, &req->urgency, &req->incremental);
    if (res != PARSE_OK) s->total_errors++;

    printf("[SCHEDULER] Yeni Istek: ID#%d, %s, Path: %s\n", 
           req->id, rfc_urgency_to_string(req->urgency), req->path);

    return pq_push(s->queue, req);
}

void scheduler_process_step(Scheduler *s) {
    if (pq_is_empty(s->queue)) {
        printf("[SCHEDULER] Kuyruk bos, islem yapilmadi.\n");
        return;
    }

    HttpRequest *req = pq_pop(s->queue);
    s->total_processed++;
    printf("[PROCESS] Isleniyor: ID#%d (%s) -> Path: %s\n", 
           req->id, rfc_urgency_to_string(req->urgency), req->path);

    // Isleme bittiginde bellek iadesi
    free(req->path);
    free(req);
}

void scheduler_shutdown(Scheduler *s) {
    printf("\n--- SISTEM KAPATILIYOR ---\n");
    printf("Toplam Islenen: %d, Toplam Hata: %d\n", s->total_processed, s->total_errors);
    pq_destroy(s->queue);
    free(s);
}