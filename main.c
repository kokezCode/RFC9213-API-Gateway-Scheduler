#include <stdio.h>
#include "scheduler.h"

int main(void) {
    printf("=== RFC 9213 API GATEWAY SCHEDULER ===\n\n");

    Scheduler *gateway = scheduler_init();

    // Senaryo 1: Karisik yukleme
    scheduler_add_request(gateway, "u=6", "/analytics");
    scheduler_add_request(gateway, "u=0, i", "/index.html"); // En acil
    scheduler_add_request(gateway, "u=3", "/api/data");
    scheduler_add_request(gateway, "u=1", "/styles.css");

    // Senaryo 2: Hatali header testi
    scheduler_add_request(gateway, "u=9", "/bad-req"); // u=3 olur

    printf("\n--- Oncelik Sirasina Gore Isleme Basliyor ---\n\n");

    while (gateway->queue->size > 0) {
        scheduler_process_step(gateway);
    }

    scheduler_shutdown(gateway);
    return 0;
}