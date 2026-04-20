# RFC 9213 Uyumlu API Gateway İstek Zamanlayıcısı

Bu proje, modern HTTP önceliklendirme standartlarını (**RFC 9213**) temel alarak geliştirilmiş, yüksek performanslı bir **API Gateway İstek Zamanlayıcısı** simülasyonudur. Sistem, gelen istekleri **Min-Heap** veri yapısı kullanarak O(\log n) karmaşıklıkla önceliklendirir.

## 🚀 Öne Çıkan Özellikler
* ***RFC 9213 Uyumluluğu:** `Urgency` (0-7) ve `Incremental` parametrelerini destekleyen gelişmiş parser modülü.
* **Yüksek Performans:** Sıradan dizilere göre 100 kat daha hızlı olan Min-Heap tabanlı öncelikli kuyruk (Priority Queue).
* **Modüler Mimari:** "Separation of Concerns" prensibiyle ayrılmış 4 farklı katman (.h/.c ayrımı)[cite: 588, 589].
* **Hata Yönetimi (Resilience):** Geçersiz header değerlerinde (u=9 gibi) sistem çökmez, "Graceful Degradation" ile varsayılan öncelik atar.
* **Bellek Güvenliği:** Dinamik bellek yönetimi (malloc/realloc/free) ile sıfır bellek sızıntısı.

## 🏗️ Modüler Mimari Şeması
Proje, **Facade Design Pattern** kullanılarak şu katmanlara ayrılmıştır:
1.  **main.c:** Test senaryoları ve simülasyon giriş noktası.
2.  **scheduler:** Parser ve Kuyruk modüllerini koordine eden ana motor.
3.  **rfc_parser:** HTTP Priority header'larını ayrıştıran katman.
4.  **priority_queue:** Min-Heap algoritmasının uygulandığı veri yapısı.

## 📈 Algoritma Analizi (Big-O)
| İşlem | Karmaşıklık | Açıklama |
| :--- | :--- | :--- |
| İstek Ekleme (Push) |O(\log n) | heapify_up ile ağaç yüksekliği kadar işlem. |
| İstek İşleme (Pop) | O(\log n) | heapify_down ile en öncelikli isteği çıkarma. |
| En Öncelikliyi Bulma | O(1) | Kök düğüme doğrudan erişim. |
| Dinamik Büyüme | Amortized O(1) | 2x kapasite genişletme stratejisi (realloc). |


##  Test Senaryoları
* **Sistem aşağıdaki durumlar için otomatik test edilmektedir:
* **Farklı önceliklerdeki (u=0...7) isteklerin doğru sıralanması.
* **Geçersiz header formatlarının (u=9, u=-1) yönetilmesi.
* **8'den fazla istek geldiğinde kapasitenin dinamik olarak 16'ya büyümesi (realloc).
* **Gerçekçi bir web sayfası yükleme simülasyonu.

## 🛠️ Kurulum ve Çalıştırma
Projeyi derlemek için terminale `make` yazmanız veya aşağıdaki GCC komutunu kullanmanız yeterlidir:

```bash
gcc -Wall -o scheduler_pro main.c priority_queue.c rfc_parser.c scheduler.c
./scheduler_pro
