# Smart Door Lock RFID (ESP32 + MFRC522)

Sistem pengunci pintu otomatis berbasis RFID menggunakan ESP32 dan sensor MFRC522. Sistem ini membaca UID kartu RFID dan membandingkannya dengan daftar kartu yang diizinkan untuk mengontrol akses pintu.

---

## Deskripsi Sistem
Sistem ini digunakan untuk mengontrol akses pintu menggunakan kartu RFID. UID kartu akan diverifikasi dengan daftar yang telah disimpan di dalam program. Jika UID cocok, pintu akan terbuka. Jika tidak, akses akan ditolak dengan indikator LED dan alarm.

---

## Fitur Utama
- Autentikasi akses menggunakan kartu RFID (UID)
- Penyimpanan UID kartu yang diizinkan dalam program
- Kontrol relay untuk membuka pintu
- Indikator LED untuk status akses
- Alarm buzzer untuk akses ditolak
- Tombol manual untuk membuka pintu dari dalam
- Monitoring UID kartu melalui serial monitor

---

## Teknologi yang Digunakan

### Hardware
- ESP32  
- RFID RC522 (MFRC522)  
- Relay Module  
- LED Indicator (Hijau dan Merah)  
- Buzzer  
- Push Button  

### Software
- Arduino IDE  
- Library MFRC522  

### Protocol
- SPI (RFID)  
- Digital I/O  

---

## Cara Kerja Sistem
1. Sistem menunggu kartu RFID didekatkan ke sensor  
2. Sensor membaca UID kartu  
3. UID dibandingkan dengan daftar kartu yang diizinkan  
4. Jika cocok:
   - Relay aktif (pintu terbuka)
   - LED hijau menyala
5. Jika tidak cocok:
   - Akses ditolak
   - LED merah menyala
   - Buzzer berbunyi  
6. Tombol manual dapat digunakan untuk membuka pintu tanpa kartu  

---
