#include <PrayerTimes_v1.h> // Librari untuk menghitung waktu sholat

#include <RTClib.h> // Librari Real-Time Clock (RTC)
RTC_DS1307 rtc;     // Inisialisasi objek RTC

#include <LiquidCrystal_I2C.h>      // Librari komunikasi I2C dengan LCD
LiquidCrystal_I2C lcd(0x27, 16, 2); // Alamat, kolom, dan baris LCD

// Array untuk menyimpan nama bulan dan hari
char namaBulan[12][4] = {"Jan", "Feb", "Mar", "Apr", "Mei", "Jun", "Jul", "Agu", "Sep", "Okt", "Nov", "Des"};
char namaHari[7][7] = {"Ahad", "Senin", "Selasa", "Rabu", "Kamis", "Jum'at", "Sabtu"};

// Array untuk menyimpan waktu sholat yang dihitung
double times[sizeof(TimeName) / sizeof(char *)];

// Atur zona waktu, lintang, dan bujur
int GMT = 7; // Perbedaan zona waktu (WIB 7 / WITA 8 / WIT 9)
float latitude = -6.1702922;  // Lintang lokasi Anda
float longitude = 106.831721; // Bujur lokasi Anda

int hours, minutes;

// Fungsi inisialisasi dan mengatur parameter perhitungan waktu sholat
void setup()
{
  lcd.init();      // Inisialisasi LCD
  lcd.backlight(); // Nyalakan lampu latar LCD

  rtc.begin(); // Inisialisasi RTC

  // Hapus komentar pada baris di bawah untuk mengatur waktu awal RTC (ganti dengan waktu awal yang Anda inginkan)
  // rtc.adjust(DateTime(2024, 12, 31, 16, 50, 40));

  // Atur parameter perhitungan waktu sholat
  set_calc_method(Makkah);                 // Metode perhitungan, opsi ada di PrayerTimes.h
  set_asr_method(Shafii);                  // Metode perhitungan Ashar
  set_high_lats_adjust_method(AngleBased); // Metode penyesuaian tinggi lintang
  set_fajr_angle(20);                      // Sudut Fajar (KEMENAG 20 / MESIR 19.5)
  set_isha_angle(18);                      // Sudut Isya' (KEMENAG 18 / MESIR 17.5)
}

// Fungsi untuk menampilkan tanggal Masehi di LCD
void tampilkanTanggal()
{
  DateTime now = rtc.now(); // Dapatkan waktu saat ini dari RTC

  const char *bulan = namaBulan[now.month() - 1]; // Kurangi 1 karena indeks namaBulan dimulai dari 0, bukan 1
  uint16_t tgl = now.day();

  lcd.setCursor(2, 0);
  lcd.print(String(tgl) + " " + bulan + " " + now.year());
}

// Fungsi untuk mencetak digit nol di depan jika diperlukan
void digitNol(int digits)
{
  if (digits < 10)
  {
    lcd.print('0');
    lcd.print(digits);
  }
  else
    lcd.print(digits);
}

// Fungsi untuk menampilkan hari di LCD
void tampilkanHari()
{
  DateTime now = rtc.now(); // Dapatkan waktu saat ini dari RTC

  lcd.setCursor(0, 1);
  lcd.print(namaHari[now.dayOfTheWeek()]);
}

// Fungsi untuk menampilkan waktu di LCD
void tampilkanJam()
{
  DateTime now = rtc.now(); // Dapatkan waktu saat ini dari RTC

  lcd.setCursor(8, 1);
  digitNol(now.hour());
  lcd.print(":");
  digitNol(now.minute());
  lcd.print(":");
  digitNol(now.second());

  // Pemisah waktu
  lcd.setCursor(8 + 2, 1);
  lcd.print(":");
  lcd.setCursor(8 + 5, 1);
  lcd.print(":");
}

// Fungsi untuk menampilkan halaman 1 di LCD
void buatHalaman1()
{
  unsigned long pageStartTime = millis(); // Dapatkan waktu saat ini

  // Tampilkan tanggal Masehi
  tampilkanTanggal();

  // Tampilkan hari
  tampilkanHari();

  // Tampilkan jam selama 3 detik
  while (millis() - pageStartTime < 5000)
  {
    tampilkanJam();
  }
}

// Fungsi untuk menampilkan halaman 2 di LCD
void buatHalaman2()
{
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();
  
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, GMT, times);

  // Imsak
  get_float_time_parts(times[0], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Imsak");
  lcd.setCursor(11, 0);
  // kurangi 10 menit
  minutes -= 10;
  if (minutes < 0) {
    minutes += 60;
    hours -= 1;
    if (hours < 0) {
      hours = 23; // Kembali ke 23 jika sudah hari sebelumnya
    }
  }
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes - 10);

  // Shubuh
  get_float_time_parts(times[0], hours, minutes);
  lcd.setCursor(0, 1);
  lcd.print("Shubuh");
  lcd.setCursor(11, 1);
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes);
}

// Fungsi untuk menampilkan halaman 3 di LCD
void buatHalaman3()
{
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();
  
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, GMT, times);

  // Syuruq
  get_float_time_parts(times[1], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Syuruq");
  lcd.setCursor(11, 0);
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes);

  // Zhuhur
  get_float_time_parts(times[2], hours, minutes);
  lcd.setCursor(0, 1);
  lcd.print("Zhuhur");
  lcd.setCursor(11, 1);
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes);
}

// Fungsi untuk menampilkan halaman 4 di LCD
void buatHalaman4()
{
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();
  
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, GMT, times);

  // Ashar
  get_float_time_parts(times[3], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Ashar");
  lcd.setCursor(11, 0);
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes);

  // Maghrib
  get_float_time_parts(times[5], hours, minutes);
  lcd.setCursor(0, 1);
  lcd.print("Maghrib");
  lcd.setCursor(11, 1);
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes);
}

// Fungsi untuk menampilkan halaman 5 di LCD
void buatHalaman5()
{
  // Dapatkan waktu saat ini dari RTC
  DateTime now = rtc.now();
  
  get_prayer_times(now.year(), now.month(), now.day(), latitude, longitude, GMT, times);

  // Isya'
  get_float_time_parts(times[6], hours, minutes);
  lcd.setCursor(0, 0);
  lcd.print("Isya'");
  lcd.setCursor(11, 0);
  digitNol(hours);
  lcd.print(":");
  digitNol(minutes);
}

// Fungsi untuk menampilkan semua halaman secara berurutan
void semuaHalaman()
{
  buatHalaman1();
  // delay(3000); // delay di sini dimatikan karena sudah ada delay di millis buatHalaman1
  lcd.clear();
  buatHalaman2();
  delay(3000);
  lcd.clear();
  buatHalaman3();
  delay(3000);
  lcd.clear();
  buatHalaman4();
  delay(3000);
  lcd.clear();
  buatHalaman5();
}

// Fungsi loop utama
void loop()
{
  lcd.clear();
  semuaHalaman();
  delay(2000);
}
