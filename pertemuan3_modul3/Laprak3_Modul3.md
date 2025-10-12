# <h1 align="center">Laporan Praktikum Modul 3 - ABSTRACT DATA TYPE (ADT) </h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
ADT adalah model matematis untuk tipe data, yang mendefinisikan tingkah laku (behavior) dari sudut pandang pengguna tipe tersebut. Yang penting adalah apa operasi-operasi yang bisa dilakukan dan sifat-sifatnya, bukan bagaimana operasi-operasi tersebut diimplemen secara fisik[1]. ADT memisahkan antara antarmuka (interface) — operasi yang bisa dilakukan & bagaimana mereka harus berperilaku — dengan implementasi — struktur data dan algoritma yang nyata untuk mendukung operasi tersebut1[2].

### A. Komponen ADT<br/>
Beberapa unsur yang biasa ada dalam definisi ADT:
#### 1. Domain nilai (value domain) — himpunan nilai-nilai yang bisa dimiliki oleh objek dari tipe data tersebut.

#### 2. Operasi-operasi (operations) — fungsi atau prosedur yang diizinkan terhadap objek ADT (seperti insert, delete, find, push, pop, dll).

#### 3. Aksioma atau spesifikasi formal — aturan-aturan yang mendefinisikan sifat operasi-operasi tersebut (misalnya identitas, komutatif, asosiatif, batasan, precondition/postcondition).

#### 4. Abstraksi dari implementasi — pengguna tidak melihat detail struktur internal (contoh: apakah implementasi menggunakan list, array, pointer, pohon, dsb).

#### 5. Spesifikasi formal sering menggunakan teknik aljabar atau logika (equational specification, algebraic specification), dan kadang operational semantics atau model matematis lainnya. 

### B. Tipe Spesifikasi<br/>

- Spesifikasi aljabar (algebraic specification): mendefinisikan operasi dan persamaan (axioms) di antara operasi tersebut. Cocok untuk ADT yang operasinya total dan nilai-nilainya bisa diobservasi lewat operasi.

- Spesifikasi diuji secara logika atau model aksiomatik: menggunakan teori-teori logika, model formal, dan teori himpunan untuk mendefinisikan perilaku ADT, termasuk keadaan luar biasa (exceptional), nondeterminisme, prasyarat (preconditions), postconditions.

### 3. ADT dalam Teori Tipe dan Sistem Formal <br/>

- ADT generalisasi dari tipe induktif dalam teori tipe (type theory), misalnya paper Abstract Data Type Systems oleh Jouannaud & Okada membahas bagaimana ADT bisa diperlakukan dalam sistem tipe murni, dengan dukungan untuk definisi fungsi via pattern matching dan relasi antar konstruktor.

- Spesifikasi ADT juga terkait dengan teori semantik, seperti initial algebra semantics, model-model aljabar lainnya yang menunjukkan bahwa ADT bisa diinterpretasikan sebagai struktur aljabar bebas dengan aksioma tertentu.

### 4. Keunggulan dan Masalah<br/>
#### Keunggulan:<br/>
- Memudahkan modularitas: pengguna ADT tidak harus tahu implementasinya, memungkinkan perubahan implementasi tanpa mengubah kode yang menggunakan ADT.

- Mempermudah verifikasi formal: dengan spesifikasi formal, bisa dibuktikan bahwa implementasi mematuhi spesifikasi (correctness).

- Memisahkan aspek “what” dan “how” sehingga fokus desain bisa lebih tinggi ke aspek konsep dan penggunaan.

#### Keterbatasan / tantangan:<br/>
- Spesifikasi yang terlalu abstrak bisa sulit dihubungkan ke aspek performa (waktu, memori). Pengguna terkadang perlu mengetahui kompleksitas operasi.

- Pembuatan aksioma yang lengkap dan konsisten bisa sulit terutama bila memasukkan operasi luar biasa, nondeterminisme, atau situasi error.

- Pemodelan formal memerlukan usaha tambahan, dan penggunaan dalam proyek nyata kadang terbatas karena biaya atau kompleksitas.

## Guided 

### 1. Program Menghitung Rata-Rata Nilai Mahasiswa Menggunakan Struct

```C++
#include <iostream>
using namespace std; 

struct mahasiswa {
    string nama;
    float nilai1, nilai2;
};

void inputMhs(mahasiswa &m) {
    cout << "Masukkan nama mahasiswa: ";
    cin >> m.nama;
    cout << "Masukkan nilai 1 : ";
    cin >> m.nilai1;
    cout << "Masukkan nilai 2: ";
    cin >> m.nilai2;
}

float rata2(mahasiswa m) {
    return (m.nilai1 + m.nilai2) / 2;
}

int main() {
    mahasiswa mhs;
    inputMhs(mhs);
    cout << "Rata-rata : " << rata2(mhs);
    return 0;
}
```
Program ini menggunakan struct untuk menyimpan data mahasiswa berupa nama dan dua nilai. Fungsi inputMhs() digunakan untuk memasukkan data, sedangkan fungsi rata2() menghitung rata-rata dari dua nilai tersebut. Di fungsi main(), data dimasukkan, lalu hasil rata-ratanya ditampilkan ke layar.

### 2. Program Manajemen Data Pelajaran

```C++
[main.cpp]

#include <iostream>
#include "pelajaran.h"
using namespace std;

int main() {
    string namapel = "Struktur Data";
    string kodepel = "STD";

    pelajaran pel = create_pelajaran(namapel, kodepel);
    tampil_pelajaran(pel);

    return 0;
}

[pelajaran.cpp]

#include "pelajaran.h"

pelajaran create_pelajaran(string namaMapel, string kodepel) {
    pelajaran p;
    p.namaMapel = namaMapel;
    p.kodeMapel = kodepel;
    return p;
}

void tampil_pelajaran(pelajaran pel) {
    cout << "Nama Pelajaran : " << pel.namaMapel << endl;
    cout << "kode : " << pel.kodeMapel << endl;
}

[pelajaran.h]
#ifndef PELAJARAN_H
#define PELAJARAN_H

#include <iostream>
using namespace std;

struct pelajaran {
    string namaMapel;
    string kodeMapel;
};

pelajaran create_pelajaran(string namaMapel, string kodepel);

void tampil_pelajaran(pelajaran pel);

#endif
```
Program C++ ini terdiri dari tiga berkas terpisah — main.cpp, pelajaran.cpp, dan pelajaran.h — yang bekerja sama untuk membuat dan menampilkan data sebuah pelajaran. File header pelajaran.h berisi definisi struktur pelajaran dengan dua atribut (namaMapel dan kodeMapel) serta deklarasi fungsi create_pelajaran() dan tampil_pelajaran(). Implementasi kedua fungsi tersebut ada di pelajaran.cpp: fungsi create_pelajaran() membuat objek pelajaran baru berdasarkan nama dan kode yang diberikan, sedangkan tampil_pelajaran() mencetak informasi pelajaran ke layar. Dalam main.cpp, program utama membuat objek pelajaran “Struktur Data” dengan kode “STD”, lalu menampilkannya menggunakan fungsi-fungsi tersebut, menunjukkan konsep modularisasi dan penggunaan header dalam C++.

## Unguided 

### 1. Buat program yang dapat menyimpan data mahasiswa (max. 10) ke dalam sebuah array dengan field nama, nim, uts, uas, tugas, dan nilai akhir. Nilai akhir diperoleh dari FUNGSI dengan rumus 0.3* uts+0.4* uas+0.3* tugas.

```C++
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float uts;
    float uas;
    float tugas;
    float nilaiAkhir;
};

float hitungNilaiAkhir(float uts, float uas, float tugas) {
    return 0.3 * uts + 0.4 * uas + 0.3 * tugas;
}

int main() {
    Mahasiswa mhs[10];
    int n;

    cout << "Masukkan jumlah mahasiswa (maks 10): ";
    cin >> n;

    if (n > 10) {
        cout << "Jumlah mahasiswa tidak boleh lebih dari 10!" << endl;
        return 0;
    }

    cout << endl;

    for (int i = 0; i < n; i++) {
        cout << "Data mahasiswa ke-" << i + 1 << endl;
        cout << "Nama   : ";
        cin.ignore(); 
        getline(cin, mhs[i].nama);
        cout << "NIM    : ";
        getline(cin, mhs[i].nim);
        cout << "Nilai UTS   : ";
        cin >> mhs[i].uts;
        cout << "Nilai UAS   : ";
        cin >> mhs[i].uas;
        cout << "Nilai Tugas : ";
        cin >> mhs[i].tugas;

        mhs[i].nilaiAkhir = hitungNilaiAkhir(mhs[i].uts, mhs[i].uas, mhs[i].tugas);
        cout << endl;
    }

    cout << "\n==============================================\n";
    cout << setw(20) << left << "Nama"
         << setw(15) << left << "NIM"
         << setw(10) << "Nil. Akhir" << endl;
    cout << "==============================================\n";

    for (int i = 0; i < n; i++) {
        cout << setw(20) << left << mhs[i].nama
             << setw(15) << left << mhs[i].nim
             << setw(10) << fixed << setprecision(2) << mhs[i].nilaiAkhir << endl;
    }

    cout << "==============================================\n";

    return 0;
}
```
### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan3_modul3/output1-unguided1-modul3.png)

Program ini digunakan untuk menginput dan menampilkan data beberapa mahasiswa (maksimal 10 orang) beserta nilai akhir mereka. Setiap mahasiswa memiliki atribut berupa nama, NIM, serta nilai UTS, UAS, dan tugas. Nilai akhir dihitung menggunakan rumus berbobot: 30% UTS, 40% UAS, dan 30% tugas melalui fungsi hitungNilaiAkhir(). Program meminta pengguna memasukkan jumlah mahasiswa dan data masing-masing mahasiswa, lalu menghitung nilai akhir setiap mahasiswa. Hasil akhirnya ditampilkan dalam bentuk tabel yang rapi menggunakan manipulasi output setw, setprecision, dan fixed agar nilai akhir memiliki dua angka di belakang koma.

### 2. ![Screenshot Soal Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan3_modul3/unguided2-modul3.png)

```C++ 
[main.cpp]

#include <iostream>
#include "pelajaran.h"
using namespace std;

int main() {
    string namapel = "Struktur Data";
    string kodepel = "STD";

    pelajaran pel = create_pelajaran(namapel, kodepel);
    tampil_pelajaran(pel);

    return 0;
}

[pelajaran.cpp]

#include "pelajaran.h"

pelajaran create_pelajaran(string namaMapel, string kodepel) {
    pelajaran p;
    p.namaMapel = namaMapel;
    p.kodeMapel = kodepel;
    return p;
}

void tampil_pelajaran(pelajaran pel) {
    cout << "Nama Pelajaran : " << pel.namaMapel << endl;
    cout << "kode : " << pel.kodeMapel << endl;
}

[pelajaran.h]
#ifndef PELAJARAN_H
#define PELAJARAN_H

#include <iostream>
using namespace std;

struct pelajaran {
    string namaMapel;
    string kodeMapel;
};

pelajaran create_pelajaran(string namaMapel, string kodepel);

void tampil_pelajaran(pelajaran pel);

#endif
```
### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan3_modul3/output1-unguided2-modul3.png)

Program C++ ini terdiri dari tiga berkas terpisah — main.cpp, pelajaran.cpp, dan pelajaran.h — yang bekerja sama untuk membuat dan menampilkan data sebuah pelajaran. File header pelajaran.h berisi definisi struktur pelajaran dengan dua atribut (namaMapel dan kodeMapel) serta deklarasi fungsi create_pelajaran() dan tampil_pelajaran(). Implementasi kedua fungsi tersebut ada di pelajaran.cpp: fungsi create_pelajaran() membuat objek pelajaran baru berdasarkan nama dan kode yang diberikan, sedangkan tampil_pelajaran() mencetak informasi pelajaran ke layar. Dalam main.cpp, program utama membuat objek pelajaran “Struktur Data” dengan kode “STD”, lalu menampilkannya menggunakan fungsi-fungsi tersebut, menunjukkan konsep modularisasi dan penggunaan header dalam C++.

### 3. Buatlah program dengan ketentuan :
- 2 buah array 2D integer berukuran 3x3 dan 2 buah pointer integer
- fungsi/prosedur yang menampilkan isi sebuah array integer 2D
- fungsi/prosedur yang akan menukarkan isi dari 2 array integer 2D pada posisi tertentu
- fungsi/prosedur yang akan menukarkan isi dari variabel yang ditunjuk oleh 2 buah pointer
```C++
#include <iostream>
#include <iomanip>
using namespace std;

void tampilkanArray(int arr[3][3]) {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << std::setw(4) << arr[i][j];
        }
        std::cout << '\n';
    }
}

void tukarElem(int arr1[3][3], int arr2[3][3], int i, int j) {
    if (i < 0 || i >= 3 || j < 0 || j >= 3) return;
    int tmp = arr1[i][j];
    arr1[i][j] = arr2[i][j];
    arr2[i][j] = tmp;
}

void tukarPointer(int *p, int *q) {
    if (!p || !q) return;
    int tmp = *p;
    *p = *q;
    *q = tmp;
}

int main() {
    int A[3][3] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}
    };

    int B[3][3] = {
        {10, 11, 12},
        {13, 14, 15},
        {16, 17, 18}
    };

    int x = 100;
    int y = 200;
    int *px = &x;
    int *py = &y;

    std::cout << "Array A awal:\n";
    tampilkanArray(A);
    std::cout << "\nArray B awal:\n";
    tampilkanArray(B);

    std::cout << "\nMenukar elemen A[1][1] dengan B[1][1] (indeks 1,1 = baris kedua kolom kedua)\n";
    tukarElem(A, B, 1, 1);

    std::cout << "Array A setelah tukar:\n";
    tampilkanArray(A);
    std::cout << "\nArray B setelah tukar:\n";
    tampilkanArray(B);

    std::cout << "\nNilai sebelum tukar via pointer: x=" << x << ", y=" << y << '\n';
    tukarPointer(px, py);
    std::cout << "Nilai setelah tukar via pointer: x=" << x << ", y=" << y << '\n';

    return 0;
}
```
### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan3_modul3/output1-unguided3-modul3.png)

Program ini mendemonstrasikan penggunaan array dua dimensi dan pointer untuk menukar nilai. Dua buah array 3×3 (A dan B) berisi angka berbeda ditampilkan dengan fungsi tampilkanArray(), yang mencetak elemen array dalam format tabel rapi menggunakan setw. Fungsi tukarElem() menukar elemen pada posisi tertentu antara dua array (misalnya A[1][1] dengan B[1][1]), sementara tukarPointer() menukar nilai dua variabel melalui pointer. Program menampilkan kondisi awal dan hasil setelah pertukaran, menunjukkan cara manipulasi data baik pada array maupun melalui pointer di memori.

## Kesimpulan
Abstract Data Type adalah konsep penting dalam ilmu komputer yang memungkinkan pemisahan antara antarmuka dan implementasi, fokus pada perilaku yang diharapkan daripada detail representasi.

ADT mendasari banyak prinsip dalam pemrograman, seperti abstraksi data, modularitas, dan spesifikasi formal, dan juga muncul di teori tipe dan semantik pemrograman.

Untuk desain sistem yang handal dan dapat diverifikasi, penggunaan ADT dengan spesifikasi formal sangat berguna; namun, harus ada keseimbangan antara abstraksi dan kebutuhan praktis (misalnya performa, kegunaan implementasi).

Penelitian tentang ADT terus berkembang terutama dalam konteks model formal, teori tipe, dan aplikasi himpunan aksioma yang lebih kompleks (misalnya nondeterminisme, kesalahan, higher-order types).

## Referensi
[1]Jean-Pierre Jouannaud & Mitsuhiro Okada. Abstract Data Type Systems. Theoretical Computer Science, Vol. 173, No. 2, pp. 349-391, 1997.

<br>[2]Solomon Feferman. A new approach to abstract data types, I Informal development. Mathematical Structures in Computer Science, Vol. 2, Issue 2, 1992.

<br>[3]Paulo A. S. Veloso, T. S. E. Maibaum, M. R. Sadler. A theory of abstract data types for program development: Bridging the gap? In Formal Methods and Software Development (TAPSOFT 1985).

<br>[4]Yingxu Wang, Xinming Tan, Cyprian F. Ngolah, Philip Sheu. The Formal Design Models of a Set of Abstract Data Types (ADTs): Computer Science & IT Journal Article | IJSSCI, 2010.

<br>[5]Marie-Claude Gaudel, Pascale Le Gall. Testing data types implementations from algebraic specifications. arXiv preprint, 2008.