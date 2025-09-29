# <h1 align="center">Laporan Praktikum Modul 2 - Pengenalan Bahasa C++ (Bagian Kedua)</h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
C++ merupakan bahasa pemrograman yang dikembangkan sebagai perluasan dari C. Bahasa ini mendukung paradigma prosedural dan berorientasi objek, sehingga memungkinkan penulisan program yang lebih terstruktur, modular, dan efisien. Dalam modul lanjutan ini, pembahasan diarahkan pada fitur-fitur yang lebih kompleks dibandingkan pengenalan dasar, seperti penggunaan fungsi, array, pointer, dan struktur kontrol tingkat lanjut.

### 1. Pemrograman Berorientasi Objek (Object-Oriented Programming / OOP) <br/> 
Bahasa C++ merupakan pengembangan dari C yang menambahkan paradigma berorientasi objek. Konsep OOP seperti enkapsulasi, pewarisan, dan polimorfisme memungkinkan programmer membangun perangkat lunak yang lebih modular, efisien, dan mudah dikembangkan.
Menurut penelitian, pendekatan OOP dalam C++ membantu meningkatkan reusability kode dan mempermudah proses pengujian perangkat lunak.

### 2. Struktur Data dan Tipe Data<br/>
C++ mendukung berbagai tipe data dasar (primitive types) seperti int, float, double, serta tipe kompleks melalui struct dan class. Pemahaman tipe data penting karena memengaruhi efisiensi memori dan kecepatan eksekusi program.
Penelitian menunjukkan bahwa pemilihan tipe data yang tepat dapat mengurangi overhead komputasi dan meningkatkan performa program.

### 3. Kontrol Alur (Control Flow)<br/>
Struktur kontrol seperti percabangan (if-else, switch) dan perulangan (for, while, do-while) memungkinkan pengambilan keputusan dinamis serta eksekusi berulang.
Menurut penelitian dalam Journal of Computer Science, kontrol alur adalah aspek penting untuk mendukung algorithm design dan implementasi logika pemrograman yang kompleks.

### 4. Fungsi dan Modularitas<br/>
C++ mendukung fungsi sebagai sarana untuk membagi program menjadi bagian-bagian kecil. Modularitas ini membantu meningkatkan keterbacaan, pemeliharaan, dan memungkinkan penggunaan kembali kode.
Penelitian menjelaskan bahwa modularitas dalam desain perangkat lunak meningkatkan produktivitas pengembang serta mengurangi tingkat kesalahan.

### 5. Array dan Pointer<br/>
Array digunakan untuk menyimpan sekumpulan data dengan tipe yang sama, sedangkan pointer memungkinkan akses langsung ke alamat memori. Kedua konsep ini krusial dalam C++ karena memberikan fleksibilitas tinggi, meskipun berpotensi menimbulkan kesalahan jika tidak digunakan dengan hati-hati.
Menurut penelitian, penggunaan pointer yang tepat dapat meningkatkan efisiensi pengolahan data, namun juga meningkatkan risiko memory leak dan segmentation fault.

## Guided 

### 1. Program Input dan Output Array dengan Perulangan for dan while

```C++
#include <iostream>
using namespace std;

int main() {
    int arr[5];

    for (int i = 0; i < 5; i++) {
        cout << "masukkan value indeks ke-" << i << " : ";
        cin >> arr[i];
    }
    int j = 0;
    while (j < 5) {
        cout << "isi indeks ke-" << j << " : " << arr[j] << endl;
        j++;
    }
    return 0;
}
```
Program ini membaca 5 angka dari user ke dalam array dengan perulangan for, lalu menampilkan kembali isi array beserta indeksnya menggunakan perulangan while.

### 2. Program Operasi Matriks 2x2 (Penjumlahan dan Perkalian)

```C++
#include <iostream>
using namespace std;

void tampilkanHasil(int arr[2][2]) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cout << arr[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int arrA[2][2] = {
        {1, 2},
        {3, 4}
    };
    int arrB[2][2] = {
        {2, 3},
        {4, 5}
    };
    int arrC[2][2] = {0};
    int arrD[2][2] = {0};

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            arrC[i][j] = arrA[i][j] + arrB[i][j];
        }
    }

    cout << "Hasil penjumlahan : " << endl;
    tampilkanHasil(arrC);

    cout << endl;

    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                arrD[i][j] += arrA[i][k] * arrB[k][j];
            }
        }
    }

    cout << "Hasil perkalian : " << endl;
    tampilkanHasil(arrD);

    return 0;
}
```
Program ini mendefinisikan dua matriks 2x2, lalu menghitung hasil penjumlahannya dan hasil perkaliannya dengan menggunakan perulangan bersarang, kemudian menampilkan hasil akhir ke layar.

### 3. Program Pointer dan Fungsi Pertukaran Nilai (Swap) Menggunakan Referensi Alamat
```C++
#include <iostream>
using namespace std;

void tukar(int *x, int *y) {
    int temp;
    temp = *x;
    *x = *y; 
    *y = temp;
}

int main() {
    int a = 20, b = 30;
    int *ptr;

    ptr = &a;

    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << &a << endl;
    cout << "Value stored in ptr (address of a): " << ptr << endl;
    cout << "Value pointed to by ptr: " << *ptr << endl;

    tukar(&a, &b);
    cout << "After swapping, value of a= " << a << " and b=" << b << endl;

    return 0;
}
```
Program ini mendemonstrasikan penggunaan pointer untuk mengakses alamat dan nilai variabel, lalu menggunakan fungsi tukar dengan parameter pointer untuk menukar isi variabel a dan b.

### 4. Program Referensi (Reference) dan Fungsi Pertukaran Nilai dengan Parameter Referensi
```C++
#include <iostream>
using namespace std;

void Tukar(int &x, int &y) {
    int temp;
    temp = x;
    x = y;
    y = temp;
}

int main() {
    int a = 20,b = 30;
    int& ref = a;

    cout << "Nilai a: " << a << endl;
    cout << "Alamat a: " << &a << endl;
    cout << "Nilai ref (Alias a): " << ref << endl;
    cout << "Alamat ref (&ref): " << &ref << endl;

    ref = 50;
    cout << "\nSetelah ref = 50; " << a << endl;
    cout << "Nilai a: " << a << endl;
    cout << "Nilai ref: " << ref << endl;

    Tukar(a,b);
    cout << "After swapping, value of a= " << a << " and b=" << b << endl;
    
    return 0;
}
```
Program ini menunjukkan cara kerja reference sebagai alias dari variabel, bagaimana perubahan lewat reference langsung memengaruhi variabel asli, serta penggunaan fungsi Tukar dengan parameter referensi untuk menukar nilai dua variabel.

### 5. Program Operasi Array: Mencari Nilai Maksimum, Penjumlahan, dan Perkalian Elemen
```C++
#include <iostream>
using namespace std;

int cariMAX(int arr[], int ukuran){
    int MAX = arr[0];
    for (int i = 1; i < ukuran; i++) {
        if (arr[i] > MAX) {
            MAX = arr[i];
        }
    }
    return MAX;
}

void operasiAritmatika(int arr[], int ukuran){
    int totalJumlah = 0;
    for (int i = 0; i < ukuran; i++) {
        totalJumlah += arr[i];
    }
    cout << "Total penjumlahan: " << totalJumlah << endl;

    int totalKali = 1;
    for (int i = 0; i < ukuran; i++) {
        totalKali *= arr[i];
    }
    cout << "Total perkalian: " << totalKali << endl;
}

int main() {
    const int ukuran = 5;
    int arr[ukuran];
    for (int i = 0; i < ukuran; i++) {
        cout << "masukkan nilai array ke-" << i + 1 << ": ";
        cin >> arr[i];
    }
    cout << endl;
    cout << "Nilai terbesar dalam array : " << cariMAX(arr, ukuran) << endl;

    operasiAritmatika(arr, ukuran);
    return 0;
}
```
Program ini meminta input 5 angka dari user, lalu menggunakan fungsi untuk mencari nilai terbesar dalam array dan menghitung hasil penjumlahan serta perkalian semua elemennya, kemudian menampilkan hasilnya ke layar.

## Unguided 

### 1. Soal Unguided 1
Buatlah program yang dapat melakukan operasi penjumlahan, pengurangan, dan 
perkalian matriks 3x3 

```C++
#include <iostream>
using namespace std;

void tampilkanHasil(int arr[3][3]) {
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			cout << arr[i][j] << " ";
		}
		cout << endl;
	}
}

int main() {
	int arrA[3][3] = {
		{1, 2, 3},
		{4, 5, 6},
		{7, 8, 9}
	};
	int arrB[3][3] = {
		{9, 8, 7},
		{6, 5, 4},
		{3, 2, 1}
	};
	int arrC[3][3] = {0}; 
	int arrD[3][3] = {0}; 
	int arrE[3][3] = {0}; 

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arrC[i][j] = arrA[i][j] + arrB[i][j];
		}
	}
	cout << "Hasil penjumlahan : " << endl;
	tampilkanHasil(arrC);
	cout << endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			arrD[i][j] = arrA[i][j] - arrB[i][j];
		}
	}
	cout << "Hasil pengurangan : " << endl;
	tampilkanHasil(arrD);
	cout << endl;

	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			for (int k = 0; k < 3; k++) {
				arrE[i][j] += arrA[i][k] * arrB[k][j];
			}
		}
	}
	cout << "Hasil perkalian : " << endl;
	tampilkanHasil(arrE);

	return 0;
}
```
### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan2_modul2/output1-unguided1-modul2.png)

Program ini mendefinisikan dua matriks 3x3 lalu menghitung hasil penjumlahan, pengurangan, serta perkaliannya menggunakan perulangan bersarang, kemudian menampilkan ketiga hasil tersebut ke layar.

### 2. Soal Unguided 2
Berdasarkan guided pointer dan reference sebelumnya, buatlah keduanya dapat 
menukar nilai dari 3 variabel 

```C++
#include <iostream>
using namespace std;

void tukar(int *x, int *y) {
    int temp = *x;
    *x = *y;
    *y = temp;
}

void tukar3(int *x, int *y, int *z) {
    int temp = *x;
    *x = *y;
    *y = *z;
    *z = temp;
}

int main() {
    int a = 20, b = 30, c = 40;
    int *ptr;

    ptr = &a;

    cout << "Value of a: " << a << endl;
    cout << "Address of a: " << &a << endl;
    cout << "Value stored in ptr (address of a): " << ptr << endl;
    cout << "Value pointed to by ptr: " << *ptr << endl;

    cout << "Before swapping: a=" << a << ", b=" << b << ", c=" << c << endl;
    tukar3(&a, &b, &c);
    cout << "After swapping: a=" << a << ", b=" << b << ", c=" << c << endl;

    return 0;
}
```
### Output Unguided 2.1 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided2.1-modul2.png)

Program ini memperlihatkan penggunaan pointer untuk mengakses alamat serta nilai variabel, lalu mendemonstrasikan fungsi tukar dan tukar3 yang menggunakan pointer untuk menukar isi dua maupun tiga variabel sekaligus, kemudian menampilkan hasilnya ke layar.

```C++
#include <iostream>
using namespace std;

void Tukar(int &x, int &y) {
	int temp;
	temp = x;
	x = y;
	y = temp;
}

void Tukar3(int &x, int &y, int &z) {
	int temp = x;
	x = y;
	y = z;
	z = temp;
}

int main() {
	int a = 20, b = 30, c = 40;
	int& ref = a;

	cout << "Nilai a: " << a << endl;
	cout << "Alamat a: " << &a << endl;
	cout << "Nilai ref (Alias a): " << ref << endl;
	cout << "Alamat ref (&ref): " << &ref << endl;

	ref = 50;
	cout << "\nSetelah ref = 50; " << a << endl;
	cout << "Nilai a: " << a << endl;
	cout << "Nilai ref: " << ref << endl;

	cout << "Sebelum Tukar3: a=" << a << ", b=" << b << ", c=" << c << endl;
	Tukar3(a, b, c);
	cout << "Setelah Tukar3: a=" << a << ", b=" << b << ", c=" << c << endl;

	return 0;
}
```
### Output Unguided 2.2 :

##### Output 1
![Screenshot Output Unguided 2_2](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided2.2-modul2.png)

Program ini menampilkan cara kerja reference sebagai alias variabel, bagaimana perubahan melalui reference memengaruhi nilai asli, serta penggunaan fungsi Tukar dan Tukar3 dengan parameter referensi untuk menukar isi dua maupun tiga variabel sekaligus.

### 3. Soal Unguided 3
Diketahui sebuah array 1 dimensi sebagai berikut :  
arrA = {11, 8, 5, 7, 12, 26, 3, 54, 33, 55} 
Buatlah program yang dapat mencari nilai minimum, maksimum, dan rata – rata dari 
array tersebut! Gunakan function cariMinimum() untuk mencari nilai minimum dan 
function cariMaksimum() untuk mencari nilai maksimum, serta gunakan prosedur 
hitungRataRata() untuk menghitung nilai rata – rata! Buat program menggunakan 
menu switch-case seperti berikut ini 

--- Menu Program Array --- 
1. Tampilkan isi array 
2. cari nilai maksimum 
3. cari nilai minimum 
4. Hitung nilai rata - rata

```C++
#include <iostream>
using namespace std;

int cariMinimum(int arr[], int n) {
	int min = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] < min) min = arr[i];
	}
	return min;
}

int cariMaksimum(int arr[], int n) {
	int max = arr[0];
	for (int i = 1; i < n; i++) {
		if (arr[i] > max) max = arr[i];
	}
	return max;
}

void hitungRataRata(int arr[], int n) {
	float total = 0;
	for (int i = 0; i < n; i++) {
		total += arr[i];
	}
	cout << "Nilai rata-rata: " << total/n << endl;
}

void tampilkanArray(int arr[], int n) {
	cout << "Isi array: ";
	for (int i = 0; i < n; i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}

int main() {
	int arrA[] = {11, 8, 5, 7, 12, 26, 3, 54, 33, 55};
	int n = sizeof(arrA)/sizeof(arrA[0]);
	int pilihan;
	do {
		cout << "\n--- Menu Program Array ---" << endl;
		cout << "1. Tampilkan isi array" << endl;
		cout << "2. cari nilai maksimum" << endl;
		cout << "3. cari nilai minimum" << endl;
		cout << "4. Hitung nilai rata - rata" << endl;
		cout << "0. Keluar" << endl;
		cout << "Pilih menu: ";
		cin >> pilihan;
		switch(pilihan) {
			case 1:
				tampilkanArray(arrA, n);
				break;
			case 2:
				cout << "Nilai maksimum: " << cariMaksimum(arrA, n) << endl;
				break;
			case 3:
				cout << "Nilai minimum: " << cariMinimum(arrA, n) << endl;
				break;
			case 4:
				hitungRataRata(arrA, n);
				break;
			case 0:
				cout << "Keluar program." << endl;
				break;
			default:
				cout << "Menu tidak valid!" << endl;
		}
	} while(pilihan != 0);
	return 0;
}
```
### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided3(1)-modul2.png)

##### Output 2
![Screenshot Output Unguided 3_2](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan1_modul1/output1-unguided3(2)-modul2.png)

Program ini menggunakan menu interaktif untuk memungkinkan user menampilkan isi array, mencari nilai maksimum, minimum, menghitung rata-rata elemen, dan keluar dari program dengan struktur fungsi terpisah untuk tiap operasi.

## Kesimpulan
Bahasa pemrograman C++ merupakan bahasa yang kuat karena mendukung paradigma prosedural maupun berorientasi objek, sehingga dapat digunakan untuk membangun perangkat lunak yang kompleks, modular, dan efisien. Konsep-konsep dasar seperti tipe data, struktur kontrol, fungsi, array, dan pointer menjadi fondasi penting dalam memahami pemrograman C++.

Pemilihan tipe data yang tepat berpengaruh terhadap efisiensi memori dan kinerja program, sementara struktur kontrol dan fungsi mendukung pengembangan algoritma yang lebih sistematis serta modular. Array dan pointer memberikan fleksibilitas tinggi dalam pengolahan data, meskipun membutuhkan kehati-hatian untuk mencegah kesalahan memori.

Secara keseluruhan, penguasaan teori dasar C++ ini menjadi bekal penting untuk mempelajari materi lanjutan seperti struktur data, algoritma, hingga pemrograman berorientasi objek secara mendalam. Dengan pemahaman yang baik, mahasiswa maupun praktisi dapat mengembangkan perangkat lunak yang lebih terstruktur, dapat dipelihara, serta memiliki kinerja yang optimal.

## Referensi
[1]Sommerville, I. (2011). Software Engineering (9th ed.). Addison-Wesley.

[2]Garg, V., & Garg, V. (2014). Data Structures and Algorithms in C++. Journal of Computer Engineering, 16(2), 40-45.

[3]Ala-Mutka, K. (2007). Problems in Learning and Teaching Programming. Journal of Computer Science Education, 12(3), 197–207.

[4]Pressman, R. S., & Maxim, B. R. (2015). Software Engineering: A Practitioner's Approach (8th ed.). McGraw-Hill.

[5]McConnell, S. (2004). Code Complete: A Practical Handbook of Software Construction (2nd ed.). Microsoft Press.
<br>...
