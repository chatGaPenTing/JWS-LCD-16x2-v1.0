# <p align="center">بِسْمِ ٱللَّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ</p>
# <p align="center">![JWS Fullscreen Tinker-240p](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/f6aeac52-6d8a-4f4c-aaec-869a1f0dbf4e)
</p>

### JWS ini gratis dan bisa digunakan siapapun.  
---
## Tentang Pembuatan JWS
Masih banyak kekurangan dalam JWS LCD 16x2 ini karena memang tujuannya adalah belajar dari dasar untuk dikembangkan hingga tingkat lanjut.  
Dengan alasan itu saya sudah terlebih dahulu memberikan nomor versi.  
  
Contoh kekurangannya :  
- Input longitude, latitude, altitude, patokan derajat dan lain-lain masih manual di dalam sketch.  
- Nama bulan masih menggunakan singkatan 3 huruf.  
- Penanggalan hijriyyah belum dimasukkan dan selanjutnya menunggu dimasukkan ke dalam versi selanjutnya.  
- Efek animasi tampilan pindah halaman akan dimasukkan ke dalam versi selanjutnya.  
- Kutipan nasehat atau kata-kata mutiara juga akan dimasukkan ke dalam versi selanjutnya.  
---
## Altitude JWS
Saya melihat jarang aplikasi JWS Arduino yang melampirkan `Altitude` sebagai tambahan parameter kalkulasi. Memang Altitude ini hanya mempengaruhi jadwal *`Syuruq`* dan *`Maghrib`* yang di dalam rumusnya ditambahkan nilai `Sun Altitude` sebagai parameter kalkulasi.  
Berdasar percobaan saya, setiap `Altitude 100 meter` itu ada perbedaan `1 menit` dan seumpama teman-teman di wilayah Bogor yang beberapa wilayah dengan Altitude 1000 meter maka akan terjadi perbedaan cukup jauh di atas 5 menit jika menggunakan `JWS tanpa paramater Altitude`.

---
## Kalkulasi Negara Indonesia
Untuk Indonesia, setting ketentuan kalkulasi menggunakan data dari KEMENAG yaitu 20° dan 18° yang dimasukkan dalam data berikut:  
```cpp
// Atur parameter perhitungan waktu sholat
  set_calc_method(Custom);                 // Metode perhitungan, opsi ada di PrayerTimes.h
  set_asr_method(Shafii);                  // Metode perhitungan Ashar
  set_high_lats_adjust_method(AngleBased); // Metode penyesuaian tinggi lintang
  set_fajr_angle(20);                      // Sudut Fajar (KEMENAG 20 / MESIR 19.5)
  set_isha_angle(18);                      // Sudut Isya' (KEMENAG 18 / MESIR 17.5)
```
Untuk pengaturan lokasi gunakan parameter longitude, latitude, altitude dan zona waktu yang bisa anda dapatkan dari internet. Masukkan parameter tersebut seperti contoh di sini :  
```cpp
// Atur parameter zona waktu, lintang, bujur dan altitude
int GMT = 9;                  // Perbedaan zona waktu (WIB 7 / WITA 8 / WIT 9)
float latitude = -4.151111;   // Lintang lokasi Anda, tambah tanda - jika anda di wilayah S (South)
float longitude = 138.915000; // Bujur lokasi Anda
float altitude = 2000;        // Ketinggian lokasi Anda dalam satuan meter   
```  
---
  
### Tentang Librari PrayerTimes  
Librari diambil dari [asmaklad/Arduino Prayer Times](https://github.com/asmaklad/Arduino-Prayer-Times) dengan perubahan berupa penambahan kalkulasi Altitude dari saya.
Saya memasukkan parameter penambahan Altitude ke dalam librari sesuai metode perhitungan dari [praytimes.org](http://praytimes.org/calculation). Saya menambahkan data perhitungan ke dalam librari pada line perhitungan `Sunrise` dan `Sunset` yang awalnya seperti ini :  
```cpp
	times[Sunrise] = compute_time(180.0 - 0.833, times[Sunrise]);
	times[Sunset] = compute_time(0.833, times[Sunset]);
```
Untuk diubah menjadi seperti ini :  
```cpp
	times[Sunrise] = compute_time(180.0 - (0.833 + (0.0347 * sqrt(altitude))), times[Sunrise]);
	times[Sunset] = compute_time((0.833 + (0.0347 * sqrt(altitude))), times[Sunset]);
```
Selanjutnya menambahkan deklarasi untuk `Altitude` :  
```cpp
extern double altitude;
```

---

## Percobaan hasil penambahan Altitude  
Untuk sebagai bahan riset waktu shalat, saya mengambil 5 lokasi wilayah di 5 pulau besar Indonesia yaitu Sumatra, Jawa, Kalimantan, Sulawesi dan Papua yang mempunyai ketinggian wilayah di atas 1000 meter. Sebagai bahan pembanding riset waktu shalat  saya menggunakan aplikasi PC Accurate Times 5.7. Dan terlihat jelas perbedaan Altitude terhadap *`Syuruq`* dan *`Maghrib`*. Untuk titik riset lokasi berikut saya cantumkan beserta hasil perbedaannya :  
| Lokasi                                            | Longitude       | Latitude        | Altitude        | *`Syuruq`* tanpa `Altitude` | *`Syuruq`* pakai `Altitude` | *`Maghrib`* tanpa `Altitude` | *`Maghrib`* pakai `Altitude` |
|---------------------------------------------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|-----------------|
| Aceh - Masjid Al-Azhar/Sahara Gunung Geureudong   | 96.773333       | 4.790000        | 1300 meters     | 06:42           | 06:36           | 18:45           | 18:51           |
| Jawa Barat - Masjid Al-Amin Taman Safari          | 106.950607      | -6.720000       | 1150 meters     | 05:57           | 05:52           |	18:08           | 18:13           |
| Kalimanta Barat - Taman Nasional Bukit Baka       | 112.435556      | -0.050556       | 1490 meters     | 05:37           | 05:32           |	17:44           | 17:50           |
| Sulawesi Selatan - Masjid Gunung Lompobattang     | 119.865503      | -5.360541       | 1180 meters     | 06:06           | 06:01           |	18:16           | 18:21           |
| Papua - Masjid Nurul Falah Puncak Trikora         | 138.915000      | -4.151111	| 2000 meters     | 05:50           | 05:43           |	17:59           | 18:06           |

---

<details>
<summary>Dan berikut hasil riset tentang pengaruh Altitude menggunakan aplikasi PC Accurate Times 5.7 :</summary>  
    
`Sumatra - Aceh`  
![Aceh Diff](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/6ac6f40e-7577-4293-aff3-f48e78b427f8)
  
`Jawa - Bogor`
![Bogor Diff](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/e4286b17-81a5-4836-ac3e-261038544d32)

`Kalimantan - Sintang`  
![Kalbar Diff](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/53632e53-ea6b-402f-9bca-30ad18d44d96)

`Sulawesi - Gowa`  
![Sulsel Diff](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/f4386ee8-e603-47e2-be50-9c2feb7f4dfd)

`Papua - Puncak Trikora`  
![Papua Diff](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/bf3c40f5-134c-4dea-908f-65edd451f0b4)
</details>  

---

## Skema JWS
<details>
<summary>Contoh skema menggunakan Nano :</summary>  
	
![skema320](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/747120df-6544-48f8-b799-7773ca537775)  
</details>  

---
  
## Cara Mengunduh :    
<details>
<summary>Download filenya seperti gambar ini :</summary>  
    
![unduh480](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/2854ff19-05fb-4756-a5ff-1f04ad1ed275)
</details>  

---
  
## Cara Instalasi :    
  
<details>  
<summary>Buka Arduino IDE, lalu masuk menu --> Sketch --> Include Library --> Add .ZIP Library... :</summary>  

![cara1-320](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/3f306350-7a76-402a-9080-fe2640f5d3cb)
</details>
    
<details>  
<summary>Selanjutnya masih di Arduino IDE, masuk menu --> File --> Examples --> JWS-LCD-16x2-v1.0-main --> Sampel_JWS_LCD_16x2_v1 :</summary>  
    
![cara2-320](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/b24a04dc-d3d3-4131-a117-a6186e70bc96)
</details>
  
<details>  
<summary>Contoh hasil data jadwal shalat dicocokkan dengan aplikasi PC Accurate Times 5.7 :</summary>  
  
https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/3bb84285-3116-476f-81cc-920385032255
</details>  

---
  
## DONASI  
Dukung saya
- [Es Krim](https://trakteer.id/iqbal1990/tip)

  
