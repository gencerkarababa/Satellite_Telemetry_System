# 🛰️ Satellite Telemetry & Mission Control System

Bu projenin temel amacı, bir uydunun uzay görevleri sırasında ürettiği telemetri verilerini (sıcaklık, basınç, enerji durumu vb.) en güvenli ve verimli şekilde yöneten bir **Görev Kontrol Sistemi** simüle etmektir. 

Proje, kısıtlı kaynaklara sahip gömülü sistemlerde verinin kaybolmadan nasıl işleneceğini, iletileceğini ve yedekleneceğini uygulamalı olarak gösterir.



## 🔄 Projenin İşleyişi ve Veri Yolculuğu

Sistem, bir uydunun yaşam döngüsündeki veri akışını şu adımlarla yönetir:

1.  **Veri Toplama (Data Ingestion):** Uydudaki sensörlerden gelen her bir paket, sistemin "Fırlatma Rampası" olan **TelemetryQueue**'ya alınır.
2.  **Otonom Denetim:** Sistem, kuyruğun doluluk oranını sürekli izler. Eğer kapasite (50 paket) dolarsa, dışarıdan müdahale beklemeden otomatik olarak iletim sürecini başlatır.
3.  **Dünyaya İletim (Transmission):** Kuyruktaki veriler FIFO (İlk Giren İlk Çıkar) disipliniyle sırayla işlenir. Bu aşamada veriler "Dünya İstasyonu"na gönderilmek üzere kuyruktan çıkarılır.
4.  **Akıllı Yedekleme (Archive/Backup):** Dünyaya başarıyla gönderilen her veri paketi, aynı zamanda uydunun yedekleme bölümü olan **BackupRingBuffer**'a kopyalanır.
5.  **Dairesel Yönetim:** Arşiv (Buffer) dolduğunda, sistem en eski yedekleri otomatik olarak siler ve yeni gelen güncel verileri bu boşalan yerlere yazar. Böylece hafıza hiçbir zaman şişmez ve uydu en güncel görev geçmişini her zaman saklar.



## 🛠️ Teknik Mimari ve Veri Yapıları

* **TelemetryQueue (Dairesel Kuyruk):** Statik dizi tabanlı yapısı sayesinde bellek kullanımını sabitler ve $O(1)$ erişim hızıyla yüksek performanslı veri iletimi sağlar.
* **BackupRingBuffer (Dairesel Tampon):** Bellek parçalanmasını (fragmentation) önleyerek kısıtlı RAM alanında sonsuz bir veri akışını yönetir.
* **Deep Copy Mekanizması:** Aktif veriler silinse bile yedeklerin güvenli bir şekilde arşivde kalmasını sağlayan nesne yönelimli koruma.



---

## 👨‍💻 Yazar
Nizamettin Gencer Karababa
