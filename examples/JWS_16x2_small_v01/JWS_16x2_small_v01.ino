// Kode ini mencakup beberapa pustaka untuk menangani berbagai fungsionalitas.
#include <Wire.h>  // Librari untuk komunikasi I2C
#include "PrayerTimes.h"  // Librari untuk menghitung waktu salat
#include "quotes_v1.h"  // Librari yang berisi kutipan untuk ditampilkan

#include <RTClib.h>  // Librari Jam Real-Time (RTC)
RTC_DS1307 rtc;  // Inisialisasi objek RTC

#include <LiquidCrystal_I2C.h>  // Librari untuk komunikasi I2C dengan LCD
LiquidCrystal_I2C lcd(0x27, 16, 2);  // Alamat LCD, kolom, dan baris

// Array untuk menyimpan nama bulan dan hari
char namaBulan[12][9] = {"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Nov", "Des"};
char namaHari[7][7] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

// Array untuk menyimpan waktu salat yang dihitung dan perbedaan waktu zona
double times[sizeof(TimeName) / sizeof(char *)];
int GMT = 7;  // Perbedaan waktu zona (WIB 7 / WITA 8 / WIT 9)

// Fungsi setup untuk menginisialisasi perangkat keras dan mengatur parameter perhitungan waktu salat
void setup() {
  lcd.init();  // Inisialisasi LCD
  lcd.backlight();  // Nyalakan lampu latar LCD

  rtc.begin();  // Inisialisasi RTC

  // Hapus komentar pada baris di bawah untuk mengatur waktu RTC awal (ganti dengan waktu awal yang Anda inginkan)
  // rtc.adjust(DateTime(2024, 12, 31, 16, 50, 40));

  // Atur parameter perhitungan waktu salat
  set_calc_method(Makkah);  // Metode perhitungan, opsi ada di PrayerTimes.h
  set_asr_method(Shafii);  // Metode perhitungan Asr
  set_high_lats_adjust_method(AngleBased);  // Metode penyesuaian lintang tinggi
  set_fajr_angle(20);  // Sudut Fajr (KEMENAG 20 / MESIR 19.5)
  set_isha_angle(18);  // Sudut Isha (KEMENAG 18 / MESIR 17.5)
}

// Fungsi untuk menampilkan tanggal Masehi di LCD
void displayTanggal() {
  DateTime now = rtc.now();  // Dapatkan waktu saat ini dari RTC

  const char* bulan = namaBulan[now.month() - 1];  // Kurangi 1 karena indeks dimulai dari 0, bukan 1
  uint16_t tgl = now.day();

  lcd.setCursor(2, 0);
  lcd.print(String(tgl) + " " + bulan + " " + now.year());
}

// Fungsi untuk menampilkan hari di LCD
void displayDay() {
  DateTime now = rtc.now(); // Dapatkan waktu saat ini dari RTC

  lcd.setCursor(0, 1);
  lcd.print(namaHari[now.dayOfTheWeek()]);
}

// Variabel untuk mengatur waktu sebelumnya dan interval waktu pembaruan
unsigned long previousMillis = 0;
const long interval = 1000;  // Update setiap 1 detik

// Fungsi untuk menampilkan waktu di LCD
void displayTime() {
  DateTime now = rtc.now(); // Dapatkan waktu saat ini dari RTC

  lcd.setCursor(8, 1);
  printDigits(now.hour());
  lcd.print(":");
  printDigits(now.minute());
  lcd.print(":");
  printDigits(now.second());

  // Pemisah waktu
  lcd.setCursor(8 + 2, 1);
  lcd.print(":");
  lcd.setCursor(8 + 5, 1);
  lcd.print(":");
}

// Fungsi untuk menampilkan kutipan di LCD
void displayQuote() {
  long randNumber;
  randNumber = random(0, 7);  // Menghasilkan nomor acak antara 0 dan 4
  String text = quotes[randNumber];  // Dapatkan kutipan acak
  int i, j = 0;

  for (i = 0; i < text.length(); i++) {
    if (i < 15) {
      lcd.setCursor(0 + i, 1);
      lcd.print(text.charAt(i));
      delay(150);
    } else {
      for (i = 16; i < text.length(); i++) {
        j++;
        lcd.setCursor(0, 1);
        lcd.print(text.substring(j, j + 16));
        delay(150);
      }
    }
  }
}

// Fungsi untuk mencetak digit dengan nol di depan jika diperlukan
void printDigits(int digits) {
  if (digits < 10) {
    lcd.print('0');
    lcd.print(digits);
  }
  else lcd.print(digits);
}

// Fungsi untuk menampilkan halaman 1 di LCD
void displayPage1() {
  unsigned long pageStartTime = millis(); // Dapatkan waktu saat ini

  // Tampilkan tanggal Masehi
  displayTanggal();

  // Tampilkan hari
  displayDay();

  // Tampilkan jam selama 3 detik
  while (millis() - pageStartTime < 3000) {
    displayTime();
  }
}

// Fungsi untuk menampilkan halaman 3 di LCD
void displayPage2() {
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();

  // Atur zona waktu, lintang, dan bujur
  int gmt = 7;
  float latitude = -6.2663638; // Lintang lokasi Anda
  float longitude = 106.699388; // Bujur lokasi Anda
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, gmt, times);
  int hours, minutes;

  // Imsak
  get_float_time_parts(times[0], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Imsak");
  lcd.setCursor(11, 0);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes - 10);

  // Shubuh
  lcd.setCursor(0, 1);
  lcd.print("Shubuh");
  lcd.setCursor(11, 1);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes);
}

// Fungsi untuk menampilkan halaman 4 di LCD
void displayPage3() {
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();

  // Atur zona waktu, lintang, dan bujur
  int gmt = 7;
  float latitude = -6.2663638; // Lintang lokasi Anda
  float longitude = 106.699388; // Bujur lokasi Anda
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, gmt, times);
  int hours, minutes;

  // Syuruq
  get_float_time_parts(times[1], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Syuruq");
  lcd.setCursor(11, 0);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes);

  // Zhuhur
  get_float_time_parts(times[2], hours, minutes);
  lcd.setCursor(0, 1);
  lcd.print("Zhuhur");
  lcd.setCursor(11, 1);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes);
}

// Fungsi untuk menampilkan halaman 5 di LCD
void displayPage4() {
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();

  // Atur zona waktu, lintang, dan bujur
  int gmt = 7;
  float latitude = -6.2663638; // Lintang lokasi Anda
  float longitude = 106.699388; // Bujur lokasi Anda
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, gmt, times);
  int hours, minutes;

  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Ashar");
  lcd.setCursor(11, 0);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes);

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  lcd.setCursor(0, 1);
  lcd.print("Maghrib");
  lcd.setCursor(11, 1);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes);
}

// Fungsi untuk menampilkan halaman 6 di LCD
void displayPage5() {
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();

  // Atur zona waktu, lintang, dan bujur
  int gmt = 7;
  float latitude = -6.2663638; // Lintang lokasi Anda
  float longitude = 106.699388; // Bujur lokasi Anda
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, gmt, times);
  int hours, minutes;

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Isya'");
  lcd.setCursor(11, 0);
  printDigits(hours);
  lcd.print(":");
  printDigits(minutes);
}

// Fungsi untuk menghilangkan tampilan karakter di LCD
void fadeOut() {
  for (int i = 0; i < 16; i++) {
    lcd.setCursor(i, 0);
    lcd.print(' '); // Cetak spasi untuk menggeser karakter ke kiri
    lcd.setCursor(i, 1);
    lcd.print(' ');
    delay(50);
  }
}

// Fungsi untuk menampilkan semua halaman secara berurutan
void displayAllPages() {
  displayPage1();
  //delay(12000); // delay di sini dimatikan karena digantikan delay di millis displayPage1
  fadeOut();
  lcd.clear();
  displayPage2();
  delay(3000);
  fadeOut();
  lcd.clear();
  displayPage3();
  delay(3000);
  fadeOut();
  lcd.clear();
  displayPage4();
  delay(3000);
  fadeOut();
  lcd.clear();
  displayPage5();
  displayQuote();
}

// Fungsi loop utama
void loop() {
  lcd.clear();
  displayAllPages();
  delay(2000);
}
