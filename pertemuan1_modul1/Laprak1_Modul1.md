# <h1 align="center">Laporan Praktikum Modul 1 - Codeblocks IDE & Pengenalan Bahas C++ (Bagian Pertama)</h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
Code block (atau compound statement, blok kode) adalah suatu struktur leksikal dalam kode sumber di mana beberapa pernyataan (statements) dan/atau deklarasi dikelompokkan bersama menjadi satu kesatuan. Blok kode biasanya dibatasi oleh tanda tertentu (misalnya kurung kurawal { … } dalam C, C++, Java) atau dengan indentasi (misalnya di Python)[1]. Penggunaan blok kode juga berkaitan dengan ruang lingkup variabel (variable scope): variabel yang dideklarasikan di dalam blok seringkali hanya dapat diakses (visible) di dalam blok tersebut (lokal terhadap blok). Jika mencoba mengaksesnya dari luar blok, akan terjadi error atau tidak dikenali, tergantung bahasa pemrogramannya[2].

### A. ...<br/>
...
#### 1. ...
#### 2. ...
#### 3. ...

### B. ...<br/>
...
#### 1. ...
#### 2. ...
#### 3. ...

## Guided 

### 1. Pengenalan C++

```C++
#include <iostream>

using namespace std;
int main() {
    cout << "Hello, World!" << endl;
    return 0;
}
```
program ini hanya menampilkan tulisan "Hello, World!" ke layar sebagai output.

### 2. Perulangan dengan While
```C++
#include <iostream>
using namespace std;
int main() {
    int i=1;
    int jum;
    cout << "masukan banyak baris: ";
    cin >> jum;
    while (i <= jum) {
        cout << "baris ke-" << i << endl;
        i++;
    }
    return 0;
}
```
program ini menampilkan teks "baris ke-1", "baris ke-2", ... hingga jumlah baris yang dimasukkan user.

### 3. Program Struct Input dan Cetak Data Raport Siswa

```C++
#include <iostream>
#include <iomanip>
using namespace std;

struct Raport {
	char nama[50];
	int nis;
	float matematika;
	float bahasaIndonesia;
	float bahasaInggris;
	float ipa;
};

int main() {
	int jumlah;
	cout << "Masukkan jumlah siswa: ";
	cin >> jumlah;
	cin.ignore(); 

	Raport siswa[100]; 

	for (int i = 0; i < jumlah; i++) {
		cout << "\nData siswa ke-" << i+1 << ":\n";
		cout << "Nama: ";
		cin.getline(siswa[i].nama, 50);
		cout << "NIS: ";
		cin >> siswa[i].nis;
		cout << "Nilai Matematika: ";
		cin >> siswa[i].matematika;
		cout << "Nilai Bahasa Indonesia: ";
		cin >> siswa[i].bahasaIndonesia;
		cout << "Nilai Bahasa Inggris: ";
		cin >> siswa[i].bahasaInggris;
		cout << "Nilai IPA: ";
		cin >> siswa[i].ipa;
		cin.ignore(); 
	}

	cout << "\n--- Data Raport Siswa ---\n";
	cout << left << setw(20) << "Nama" << setw(10) << "NIS" << setw(10) << "Mat" << setw(10) << "B.Ind" << setw(10) << "B.Ing" << setw(10) << "IPA" << setw(10) << "Rata2" << endl;
	for (int i = 0; i < jumlah; i++) {
		float rata2 = (siswa[i].matematika + siswa[i].bahasaIndonesia + siswa[i].bahasaInggris + siswa[i].ipa) / 4.0;
		cout << left << setw(20) << siswa[i].nama << setw(10) << siswa[i].nis << setw(10) << siswa[i].matematika << setw(10) << siswa[i].bahasaIndonesia << setw(10) << siswa[i].bahasaInggris << setw(10) << siswa[i].ipa << setw(10) << rata2 << endl;
	}

	return 0;
}

```
program ini berfungsi untuk mencatat nilai raport beberapa siswa dan menampilkannya dalam bentuk tabel.

## Unguided 

### 1. Soal Unguided 1
Buatlah program yang menerima input-an dua buah bilangan betipe float, kemudian
memberikan output-an hasil penjumlahan, pengurangan, perkalian, dan pembagian dari dua
bilangan tersebut.

```C++
#include <iostream>
using namespace std;

int main() {
	float a, b;
	cout << "Masukkan bilangan pertama: ";
	cin >> a;
	cout << "Masukkan bilangan kedua: ";
	cin >> b;

	cout << "Hasil Penjumlahan: " << (a + b) << endl;
	cout << "Hasil Pengurangan: " << (a - b) << endl;
	cout << "Hasil Perkalian: " << (a * b) << endl;
	if (b != 0)
		cout << "Hasil Pembagian: " << (a / b) << endl;
	else
		cout << "Hasil Pembagian: Tidak dapat membagi dengan nol." << endl;

	return 0;
}

```
### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided1-modul1.png)

##### Output 2

program ini adalah kalkulator sederhana untuk dua bilangan yang bisa menghitung penjumlahan, pengurangan, perkalian, dan pembagian (dengan pengecekan nol).

### 2. Soal Unguided 2
Buatlah sebuah program yang menerima masukan angka dan mengeluarkan output nilai
angka tersebut dalam bentuk tulisan. Angka yang akan di- input-kan user adalah bilangan bulat
positif mulai dari 0 s.d 100

```C++
#include <iostream>
using namespace std;

string angkaKeTulisan(int n) {
	string satuan[] = {"Nol", "Satu", "Dua", "Tiga", "Empat", "Lima", "Enam", "Tujuh", "Delapan", "Sembilan", "Sepuluh", "Sebelas", "Dua belas", "Tiga belas", "Empat belas", "Lima belas", "Enam belas", "Tujuh belas", "Delapan belas", "Sembilan belas"};
	string puluhan[] = {"", "", "Dua puluh", "Tiga puluh", "Empat puluh", "Lima puluh", "Enam puluh", "Tujuh puluh", "Delapan puluh", "Sembilan puluh"};

	if (n < 0 || n > 100)
		return "Angka di luar jangkauan";
	if (n < 20)
		return satuan[n];
	if (n == 100)
		return "seratus";
	int puluh = n / 10;
	int satu = n % 10;
	string hasil = puluhan[puluh];
	if (satu > 0)
		hasil += " " + satuan[satu];
	return hasil;
}

int main() {
	int angka;
	cout << "Masukkan angka (0-100): ";
	cin >> angka;
	cout << angka << " : " << angkaKeTulisan(angka) << endl;
	return 0;
}

```
### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided2-modul1.png)

##### Output 2

Program ini meminta pengguna memasukkan angka antara 0 hingga 100, kemudian mengubah angka tersebut menjadi bentuk tulisan dalam bahasa Indonesia menggunakan fungsi angkaKeTulisan(), dan menampilkannya di layar dengan format angka : tulisan.

### 3. Soal Unguided 3
Buatlah program yang dapat memberikan input dan output sbb.

```C++
#include <iostream>
using namespace std;

int main() {
	int n;
	cout << "input: ";
	cin >> n;
	cout << "output:\n";

	for (int i = n; i >= 1; i--) {
		
		for (int j = i; j >= 1; j--) {
			cout << j << " ";
		}
	
		cout << "* ";
		
		for (int j = 1; j <= i; j++) {
			cout << j << " ";
		}
		cout << endl;
	}

	cout << "*" << endl;
	return 0;
}

```
### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided3-modul1.png)

##### Output 2

Program ini mencetak pola berbentuk segitiga terbalik dimana setiap baris berisi deret angka menurun dari i ke 1, diikuti tanda *, lalu deret angka menaik dari 1 ke i, dan terus berulang hingga baris terakhir hanya berisi *.

## Kesimpulan
Code block atau blok kode merupakan struktur fundamental dalam pemrograman yang berfungsi mengelompokkan sejumlah pernyataan menjadi satu kesatuan eksekusi. Keberadaan blok kode tidak hanya memengaruhi alur program melalui kontrol kondisi maupun perulangan, tetapi juga menentukan ruang lingkup variabel sehingga membantu menjaga modularitas, keterbacaan, dan pemeliharaan kode.

Dalam konteks rekayasa perangkat lunak, pemahaman terhadap blok kode berperan penting dalam praktik code review, refactoring, dan pengukuran kompleksitas perangkat lunak. Selain itu, studi empiris juga menunjukkan bahwa aspek psikologis seperti programmer’s block dapat muncul, yang menegaskan perlunya teori dan metodologi yang lebih sistematis dalam memahami hubungan antara struktur kode, produktivitas, serta kualitas perangkat lunak [Schantong et al., 2024].

Dengan demikian, dapat disimpulkan bahwa blok kode bukan hanya sekadar konstruksi sintaksis dalam bahasa pemrograman, tetapi juga komponen konseptual yang memiliki implikasi luas terhadap desain, keterbacaan, kompleksitas, hingga pengalaman kognitif programmer.

## Referensi
[1] SSchantong, B., Siegmund, N., & Siegmund, J. (2024). Toward a theory on programmer’s block inspired by writer’s block. Empirical Software Engineering.

[2] “Design of Flexible Code Block Comparisons to Improve …” (2024).

[3] Zhang, W., He, J., & Song, K. (2021). Rethinking complexity for software code structures: A pioneering study on Linux kernel code repository.
<br>...
