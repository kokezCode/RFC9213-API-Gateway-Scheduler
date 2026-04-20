#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "priority_queue.h"
#include "rfc_parser.h"

typedef struct {
    PriorityQueue *queue;
    int next_id;
    int total_processed;
    int total_errors;
} Scheduler;

Scheduler* scheduler_init(void);
int scheduler_add_request(Scheduler *s, const char *header, const char *path);
void scheduler_process_step(Scheduler *s);
void scheduler_shutdown(Scheduler *s);

#endif