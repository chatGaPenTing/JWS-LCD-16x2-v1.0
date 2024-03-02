# <p align="center">بِسْمِ ٱللَّٰهِ ٱلرَّحْمَٰنِ ٱلرَّحِيمِ</p>

# <p align="center">Jam Waktu Shalat - JWS LCD 16x2</p>  
    
### JWS ini gratis dan bisa digunakan siapapun.  
  
## Tentang Pembuatan JWS
Masih banyak kekurangan dalam JWS LCD 16x2 ini karena memang tujuannya adalah belajar dari dasar untuk dikembangkan hingga tingkat lanjut.  
Dengan alasan itu saya sudah terlebih dahulu memberikan nomor versi.  
  
Contoh kekurangannya :  
- Input lokasi, patokan derajat dan lain-lain masih manual di dalam sketch.  
- Nama bulan masih menggunakan singkatan 3 huruf.  
- Penanggalan hijriyyah belum dimasukkan ke dalam v1 dan selanjutnya menunggu dimasukkan ke dalam versi selanjutnya.  
- Efek animasi tampilan pindah halaman akan dimasukkan ke dalam versi selanjutnya.  
- Kutipan nasehat atau kata-kata mutiara juga akan dimasukkan ke dalam versi selanjutnya.  

## Kalkulasi Negara Indonesia
Untuk Indonesia, setting ketentuan kalkulasi menggunakan data dari KEMENAG yaitu 20° dan 18° yang dimasukkan dalam data berikut:  
```
set_fajr_angle(20);
set_isha_angle(18);
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
  
### Tentang Librari PrayerTimes.h dan PrayerTimes.cpp
  
Librari JWS saya ambil dari internet dan tidak ada keterangan header siapa pembuatnya.

## Contoh hasil data jadwal shalat dicocokkan dengan aplikasi Shollu PC :  
  
![ulewyldw](https://github.com/chatGaPenTing/JWS-LCD-16x2-v1.0/assets/161785031/1deccfec-f08d-4a16-96c5-027c24eac047)
