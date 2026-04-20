#include <stdio.h>
#include "scheduler.h"

int main(void) {
    printf("=== RFC 9213 API GATEWAY SCHEDULER ===\n\n");

    Scheduler *gateway = scheduler_init();

    // Senaryo 1: Karışık Öncelikli İstekler
    scheduler_add_request(gateway, "u=6", "/analytics");
    scheduler_add_request(gateway, "u=0, i", "/index.html"); // En kritik (u=0)
    scheduler_add_request(gateway, "u=3", "/api/data");
    scheduler_add_request(gateway, "u=1", "/styles.css");

    // Senaryo 2: Geçersiz ve Bozuk Header Testleri 
    printf("\n--- Hata Yonetimi Testleri Baslatiliyor ---\n");
    
    // u=9: Üst sınır ihlali (Maksimum 7 olmalı)
    scheduler_add_request(gateway, "u=9", "/bad-req-high"); 
    
    // u=-1: Alt sınır ihlali (Minimum 0 olmalı)
    scheduler_add_request(gateway, "u=-1", "/bad-req-negative"); 
    
    // Bozuk format: "u=" anahtarı hiç yok
    scheduler_add_request(gateway, "u=invalid", "/malformed-header");

    printf("\n--- Oncelik Sirasina Gore Isleme Basliyor ---\n\n");

    /* * Kuyruk boşalana kadar işle. 
     * Beklenen: u=0 önce, u=-1 ve u=9 olanlar u=3 (varsayılan) olarak işlenir.
     */
    while (gateway->queue->size > 0) {
        scheduler_process_step(gateway);
    }

    scheduler_shutdown(gateway);
    return 0;
}
