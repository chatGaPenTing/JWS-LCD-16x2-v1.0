# <p align="center">بِسْمِ ٱللَّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ</p>
# <p align="center">![JWS Fullscreen Tinker-240p](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/f6aeac52-6d8a-4f4c-aaec-869a1f0dbf4e)
</p> 
    
### JWS ini gratis dan bisa digunakan siapapun.  
  
## Tentang Pembuatan JWS
Masih banyak kekurangan dalam JWS LCD 16x2 ini karena memang tujuannya adalah belajar dari dasar untuk dikembangkan hingga tingkat lanjut.  
Dengan alasan itu saya sudah terlebih dahulu memberikan nomor versi.  
  
Contoh kekurangannya :  
- Input longitude, latitude, altitude, patokan derajat dan lain-lain masih manual di dalam sketch.  
- Nama bulan masih menggunakan singkatan 3 huruf.  
- Penanggalan hijriyyah belum dimasukkan dan selanjutnya menunggu dimasukkan ke dalam versi selanjutnya.  
- Efek animasi tampilan pindah halaman akan dimasukkan ke dalam versi selanjutnya.  
- Kutipan nasehat atau kata-kata mutiara juga akan dimasukkan ke dalam versi selanjutnya.  
  
## Altitude JWS
Saya melihat jarang aplikasi JWS Arduino yang melampirkan `Altitude` sebagai tambahan parameter kalkulasi. Memang Altitude ini hanya mempengaruhi jadwal *`Syuruq`* dan *`Maghrib`* yang di dalam rumusnya ditambahkan nilai `Sun Altitude` sebagai parameter kalkulasi.  
Berdasar percobaan saya, setiap `Altitude 100 meter` itu ada perbedaan `1 menit` dan seumpama teman-teman di wilayah Bogor yang beberapa wilayah dengan Altitude 1000 meter maka akan terjadi perbedaan cukup jauh di atas 5 menit jika menggunakan `JWS tanpa paramater Altitude`.
  
## Kalkulasi Negara Indonesia
Untuk Indonesia, setting ketentuan kalkulasi menggunakan data dari KEMENAG yaitu 20° dan 18° yang dimasukkan dalam data berikut:  
```
// Atur parameter perhitungan waktu sholat
  set_calc_method(Custom);                 // Metode perhitungan, opsi ada di PrayerTimes.h
  set_asr_method(Shafii);                  // Metode perhitungan Ashar
  set_high_lats_adjust_method(AngleBased); // Metode penyesuaian tinggi lintang
  set_fajr_angle(20);                      // Sudut Fajar (KEMENAG 20 / MESIR 19.5)
  set_isha_angle(18);                      // Sudut Isya' (KEMENAG 18 / MESIR 17.5)
```
Untuk pengaturan lokasi gunakan parameter longitude, latitude, altitude dan zona waktu yang bisa anda dapatkan dari internet. Masukkan parameter tersebut seperti contoh di sini :  
```
// Atur parameter zona waktu, lintang, bujur dan altitude
int GMT = 9;                  // Perbedaan zona waktu (WIB 7 / WITA 8 / WIT 9)
float latitude = -4.151111;   // Lintang lokasi Anda, tambah tanda - jika anda di wilayah S (South)
float longitude = 138.915000; // Bujur lokasi Anda
float altitude = 2000;        // Ketinggian lokasi Anda dalam satuan meter   
```  

### Tentang Librari PrayerTimes
  
Saya memasukkan parameter penambahan Altitude ke dalam librari sesuai metode perhitungan dari [praytimes.org](http://praytimes.org/calculation). Saya menambahkan data perhitungan ke dalam librari yang awalnya seperti ini :  
```
void compute_times(double times[])
{
	day_portion(times);

	times[Fajr] = compute_time(180.0 - method_params[calc_method].fajr_angle, times[Fajr]);
	times[Sunrise] = compute_time(180.0 - 0.833, times[Sunrise]);
	times[Dhuhr] = compute_mid_day(times[Dhuhr]);
	times[Asr] = compute_asr(1 + asr_juristic, times[Asr]);
	times[Sunset] = compute_time(0.833, times[Sunset]);
	times[Maghrib] = compute_time(method_params[calc_method].maghrib_value, times[Maghrib]);
	times[Isha] = compute_time(method_params[calc_method].isha_value, times[Isha]);
}
```
Untuk diubah menjadi seperti ini :  
```
void compute_times(double times[])
{
	day_portion(times);

	times[Fajr] = compute_time(180.0 - method_params[calc_method].fajr_angle, times[Fajr]);
	times[Sunrise] = compute_time(180.0 - (0.833 + (0.0347 * sqrt(altitude))), times[Sunrise]);
	times[Dhuhr] = compute_mid_day(times[Dhuhr]);
	times[Asr] = compute_asr(1 + asr_juristic, times[Asr]);
	times[Sunset] = compute_time((0.833 + (0.0347 * sqrt(altitude))), times[Sunset]);
	times[Maghrib] = compute_time(method_params[calc_method].maghrib_value, times[Maghrib]);
	times[Isha] = compute_time(method_params[calc_method].isha_value, times[Isha]);
}
```  
  
## Skema JWS
  
![skema320](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/747120df-6544-48f8-b799-7773ca537775)
  
## Cara Mengunduh :    
     
- Download filenya seperti gambar ini:
    
![unduh480](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/2854ff19-05fb-4756-a5ff-1f04ad1ed275)
    
## Cara Instalasi :    
  
Buka Arduino IDE, lalu masuk menu --> Sketch --> Include Library --> Add .ZIP Library... :

![cara1-320](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/3f306350-7a76-402a-9080-fe2640f5d3cb)
    
- Selanjutnya masih di Arduino IDE, masuk menu --> File --> Examples --> JWS-LCD-16x2-v1.0-main --> Sampel_JWS_LCD_16x2_v1 :
    
![cara2-320](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/b24a04dc-d3d3-4131-a117-a6186e70bc96)
  
## Contoh hasil data jadwal shalat dicocokkan dengan aplikasi Accurate Times 5.7 :  

https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/3bb84285-3116-476f-81cc-920385032255
