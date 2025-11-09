# <h1 align="center">Laporan Praktikum Modul 7 - STACK </h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
### 1. Definisi dan Sifat Dasar
Struktur data stack adalah koleksi elemen yang hanya memperbolehkan akses terpusat di satu ujung saja, sering disebut “top” (puncak). Sifat utamanya adalah LIFO (Last-In First-Out) — elemen yang paling terakhir dimasukkan adalah yang pertama dikeluarkan[1]. Contoh analogi sehari-hari: tumpukan piring—yang paling atas adalah yang pertama diambil[2].
Dalam definisi:
```
“A stack is an ordered collection of homogeneous data elements where the insertion and deletion operations take place at one end only[3].”
```
Juga:
```
“A stack is a container of objects that are inserted and removed according to the last-in first-out (LIFO) principle[4].”
```
Sifat penting lainnya: karena hanya satu ujung yang bisa diakses (top), maka operasi selain akses di top biasanya tidak diizinkan atau tidak efisien.

### 2. Operasi dasar pada Stack
Berikut adalah operasi-operasi yang lazim pada stack:
- push(e): memasukkan elemen e ke posisi puncak (top) stack.
- pop(): menghapus dan biasanya mengembalikan elemen yang berada di puncak.
- peek() atau top(): melihat elemen di puncak tanpa menghapusnya (opsional).
- isEmpty() / pengecekan apakah stack kosong.
- isFull() jika implementasi dengan kapasitas terbatas. Contoh: “overflow” dan “underflow”.

Operasi-operasi ini biasanya memiliki waktu operasi yang efisien (konstan) dalam implementasi yang tepat — karena hanya menyentuh satu ujung struktur. Misalnya push/pop sering O(1). (Meski implementasi spesifik bisa berbeda).

### 3. Kelebihan dan Kekurangan
#### Kelebihan
- Operasi push/pop di puncak dapat dilakukan dengan efisien.
- Struktur yang sederhana, mudah diimplementasikan dan dipahami.
- Cocok untuk situasi di mana urutan elemen yang terakhir masuk harus yang pertama keluar (LIFO).
- Dalam C++ menggunakan std::stack, cukup mudah untuk digunakan dan aman (selama container dasar memilih dengan benar).

#### Kekurangan
- Akses ke elemen selain puncak (top) tidak diperbolehkan atau sangat tidak efisien → jika dibutuhkan, stack bukan pilihan yang bagus.
- Dalam implementasi array dengan kapasitas tetap, perlu alokasi kapasitas terlebih dahulu/overflow perlu ditangani.
- Bila ukuran dinamis sangat besar atau banyak alokasi/dealokasi, overhead memori bisa muncul (jika menggunakan linked list).
- Tidak cocok untuk skenario di mana elemen sering diakses secara acak atau banyak operasi yang bukan di ujung.

### 4. Aplikasi dan kegunaan
Struktur data stack memiliki banyak aplikasi praktis dalam pemrograman dan algoritma, antara lain:
- Manajemen pemanggilan fungsi (call stack) dalam runtime program (termasuk dalam C++).
- Implementasi rekursi, atau konversi rekursif ke iteratif.
- Undo/Redo di user interface.
- Validasi ekspresi (misalnya bracket matching, infix→postfix).
- Navigasi web (history back/forward) sebagai analogi stack. 
- Struktur kontrol dalam algoritma (backtracking, DFS).

## Guided 

### 1. Implementasi Struktur Data Stack Menggunakan Linked List
#### [stack.h]
```C++
#ifndef STACK
#define STACK
#define Nil NULL

#include<iostream>
using namespace std;

typedef struct node *address;

struct node{
    int dataAngka;
    address next;
};

struct stack{
    address top;
};

bool isEmpty(stack listStack);
void createStack(stack &listStack);
address alokasi(int angka);
void dealokasi(address &node);

void push(stack &listStack, address nodeBaru);
void pop(stack &listStack);
void update(stack &listStack, int posisi);
void view(stack listStack);
void searchData(stack listStack, int data);

#endif
```

#### [stack.cpp]
```C++
#include "stack.h"
#include <iostream>

using namespace std;

bool isEmpty(stack listStack){
    if(listStack.top == Nil){
        return true;
    } else {
        return false;
    }
}

void createStack(stack &listStack){
    listStack.top = Nil;
}

address alokasi(int angka){
    address nodeBaru = new node;
    nodeBaru->dataAngka = angka;
    nodeBaru->next = Nil;
    return nodeBaru;
}

void dealokasi(address &node){
    node->next = Nil;
    delete node;
}

void push(stack &listStack, address nodeBaru){
    nodeBaru->next = listStack.top;
    listStack.top = nodeBaru;
    cout << "Node " << nodeBaru->dataAngka << " berhasil ditambahkan kedalam stack!" << endl;
}

void pop(stack &listStack){
    address nodeHapus;
    if(isEmpty(listStack) == true){
        cout << "Stack kosong!" << endl;
    } else {
        nodeHapus = listStack.top;
        listStack.top = listStack.top->next;
        nodeHapus->next = Nil;
        dealokasi(nodeHapus);
        cout << "node " <<  nodeHapus->dataAngka << " berhasil dihapus dari stack!" << endl;
    }
}

void update(stack &listStack, int posisi){
    if(isEmpty(listStack) == true){
        cout << "Stack kosong!" << endl;
    } else {
        if(posisi == 0){
            cout << "Posisi tidak valid!" << endl;
        } else {
            address nodeBantu = listStack.top;
            int count = 1;
            bool found = false;
            while(nodeBantu != Nil){
                if(count < posisi){
                    nodeBantu = nodeBantu->next;
                    count++;
                } else if(count == posisi){
                    cout << "Update node poisisi ke-" << posisi << endl;
                    cout << "Masukkan angka : ";
                    cin >> nodeBantu->dataAngka;
                    cout << "Data berhasil diupdate!" << endl;
                    cout << endl;
                    found = true;
                    break;
                }
            }
            if(found == false){
                cout << "Posisi " << posisi << " tidak valid!" << endl;
            }
        }
    }
}

void view(stack listStack){
    if(isEmpty(listStack) == true){
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = listStack.top;
        while(nodeBantu != Nil){
            cout << nodeBantu->dataAngka << " ";
            nodeBantu = nodeBantu->next;
        }
    }
    cout << endl;
}

void searchData(stack listStack, int data){
    if(isEmpty(listStack) == true){
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = listStack.top;
        int posisi = 1;
        bool found = false;
        cout << "Mencari data " << data << "..." << endl;
        while(nodeBantu != Nil){
            if(nodeBantu->dataAngka == data){
                cout << "Data " << data << " ditemukan pada posisi ke-" << posisi << endl;
                found = true;
                cout << endl;
                break;
            } else {
                posisi++;
                nodeBantu = nodeBantu->next;
            }
        }
        if(found == false){
            cout << "Data " << data << " tidak ditemukan didalam stack!" << endl;
            cout << endl;
        }
    }
}
```

#### [main.cpp]
```C++
#include "stack.h"
#include <iostream>

using namespace std;

int main(){
    stack listStack;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createStack(listStack);

    nodeA = alokasi(1);
    nodeB = alokasi(2);
    nodeC = alokasi(3);
    nodeD = alokasi(4);
    nodeE = alokasi(5);

    push(listStack, nodeA);
    push(listStack, nodeB);
    push(listStack, nodeC);
    push(listStack, nodeD);
    push(listStack, nodeE);
    cout << endl;

    cout << "--- Stack setelah push ---" << endl;
    view(listStack);
    cout << endl;

    pop(listStack);
    pop(listStack);
    cout << endl;

    cout << "--- Stack setelah pop 2 kali ---" << endl;
    view(listStack);
    cout << endl;

    update(listStack, 2);
    update(listStack, 1);
    update(listStack, 4);
    cout << endl;

    cout << "--- Stack setelah update ---" << endl;
    view(listStack);
    cout << endl;

    searchData(listStack, 4);
    searchData(listStack, 9);

    return 0;
}
```
Kode ini merupakan implementasi struktur data Stack (tumpukan) dengan menggunakan Linked List. File stack.h berisi deklarasi struktur node dan stack, serta fungsi-fungsi dasar stack seperti push, pop, update, view, dan searchData. File stack.cpp berisi definisi fungsi-fungsi tersebut, termasuk logika untuk menambah, menghapus, memperbarui, menampilkan, dan mencari elemen pada stack. Stack diimplementasikan secara dinamis menggunakan pointer, dengan elemen paling atas direpresentasikan oleh top. Pada main.cpp, fungsi-fungsi ini diuji — program membuat stack kosong, menambahkan lima elemen (push), menghapus dua elemen (pop), memperbarui nilai pada posisi tertentu (update), menampilkan isi stack (view), dan mencari data tertentu (searchData). Secara keseluruhan, kode ini menunjukkan cara kerja stack dengan prinsip LIFO (Last In, First Out) menggunakan pendekatan linked list.

### 2. Implementasi Struktur Data Stack Menggunakan Array
#### [stack.h]
```C++
#ifndef STACK_TABLE
#define STACK_TABLE

#include <iostream>
using namespace std;

const int MAX = 10;

struct stackTable {
    int data[MAX];
    int top;
};

bool isEmpty(stackTable s);
bool isFull(stackTable s);
void createStack(stackTable &s);

void push(stackTable &s, int angka);
void pop(stackTable &s);
void update(stackTable &s, int posisi);
void view(stackTable s);
void searchData(stackTable s, int data);

#endif
```

#### [stack.cpp]
```C++
#include "stack.h"
#include <iostream>

using namespace std;

bool isEmpty(stackTable s){
    return s.top == -1;
}

bool isFull(stackTable s){
    return s.top == MAX - 1;
}

void createStack(stackTable &s){
    s.top = -1;
}

void push(stackTable &s, int angka){
    if(isFull(s)){
        cout << "Stack penuh!" << endl;
    } else {
        s.top++;
        s.data[s.top] = angka;
        cout << "Data " << angka << " berhasil ditambahkan ke dalam stack!" << endl;
    }
}

void pop(stackTable &s){
    if(isEmpty(s)){
        cout << "Stack kosong!" << endl;
    } else {
        int val = s.data[s.top];
        s.top--;
        cout << "Data " << val << " berhasil dihapus dari stack!" << endl;
    }
}

void update(stackTable &s, int posisi){
    if(isEmpty(s)){
        cout << "Stack kosong!" << endl;
        return;
    }
    if(posisi <= 0){
        cout << "Posisi tidak valid!" << endl;
        return;
    }

    int idx = s.top - (posisi + 1);
    if(idx < 0 || idx > s.top){
        cout << "Posisi " << posisi << " tidak valid!" << endl;
        return;
    }

    cout << "Update data posisi ke- " << posisi << endl;
    cout << "Masukkan angka : ";
    cin >> s.data[idx];
    cout << "Data berhasil diupdate!" << endl;
    cout << endl;
}

void view(stackTable s){
    if(isEmpty(s)){
        cout << "Stack kosong!" << endl;
    } else {
        for(int i = s.top; i >= 0; --i){
            cout << s.data[i] << " ";
        }
    }
    cout << endl;
}

void searchData(stackTable s, int data){
    if(isEmpty(s)){
        cout << "Stack kosong!" << endl;
        return;
    }
    cout << "Mencari data " << data << "..." << endl;
    int posisi = -1;
    bool found = false;

    for(int i = s.top; i >= 0; --i){
        if(s.data[i] == data){
            cout << "Data " << data << " ditemukan pada posisi ke- " << posisi << endl;
            cout << endl;
            found = true;
            break;
        }
        posisi++;
    }

    if(!found){
        cout << "Data " << data << " tidak ditemukan dalam stack!" << endl;
        cout << endl;
    }
}
```

#### [main.cpp]
```C++
#include "stack.h"
#include <iostream>

using namespace std;

int main(){
    stackTable s;
    createStack(s);

    push(s, 1);
    push(s, 2);
    push(s, 3);
    push(s, 4);
    push(s, 5);
    cout << endl;

    cout << "--- Stack setelah push ---" << endl;
    view(s);
    cout << endl;

    pop(s);
    pop(s);
    cout << endl;

    cout << "--- Stack setelah pop 2 kali ---" << endl;
    view(s);
    cout << endl;

    // posisi dihitung dari TOP (1-based index)
    update(s, 2);
    update(s, 1);
    update(s, 4);
    cout << endl;

    cout << "--- Stack setelah update ---" << endl;
    view(s);
    cout << endl;

    searchData(s, 4);
    searchData(s, 9);

    return 0;
}
```
Kode ini merupakan implementasi struktur data Stack (tumpukan) dengan menggunakan array statis. File stack.h mendefinisikan struktur stackTable yang menyimpan elemen stack dalam array berukuran tetap (MAX = 10) serta indeks top untuk melacak elemen paling atas. Fungsi-fungsi seperti push, pop, update, view, dan searchData dideklarasikan untuk mengelola isi stack. Pada stack.cpp, fungsi-fungsi tersebut diimplementasikan untuk menambahkan data ke stack (push), menghapus data dari stack (pop), memperbarui data di posisi tertentu (update), menampilkan seluruh isi stack (view), dan mencari elemen tertentu (searchData). Sedangkan file main.cpp digunakan untuk menguji semua operasi stack — mulai dari membuat stack kosong, menambahkan lima data, menghapus dua data, memperbarui beberapa posisi, hingga mencari nilai tertentu. Kode ini menunjukkan prinsip dasar kerja stack dengan konsep LIFO (Last In, First Out) menggunakan array sebagai media penyimpanan data.

## Unguided 

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan7_modul7/unguided1-modul7.png)

#### [stack.h]
```C++
#ifndef STACK_H
#define STACK_H

typedef int infotype;

struct Stack {
    infotype info[20];
    int top;
};

void createStack(Stack &S);
void Push(Stack &S, infotype x);
infotype pop(Stack &S);
void printInfo(const Stack &S);
void balikStack(Stack &S);

#endif
```

#### [stack.cpp]
```C++
#include "stack.h"
#include <iostream>

void createStack(Stack &S)
{
	S.top = 0;
}

void Push(Stack &S, infotype x)
{
	if (S.top < 20)
	{
		S.info[S.top] = x;
		S.top = S.top + 1;
	}
	else
	{
		std::cout << "Stack penuh" << std::endl;
	}
}

infotype pop(Stack &S)
{
	if (S.top > 0)
	{
		S.top = S.top - 1;
		return S.info[S.top];
	}
	else
	{
		std::cout << "Stack kosong" << std::endl;
		return -1;
	}
}

void printInfo(const Stack &S)
{
	std::cout << "[TOP] ";
	for (int i = S.top - 1; i >= 0; i = i - 1)
	{
		std::cout << S.info[i];
		if (i > 0) std::cout << " ";
	}
	std::cout << std::endl;
}

void balikStack(Stack &S)
{
	int i = 0;
	int j = S.top - 1;
	while (i < j)
	{
		infotype temp = S.info[i];
		S.info[i] = S.info[j];
		S.info[j] = temp;
		i = i + 1;
		j = j - 1;
	}
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "stack.h"

int main()
{
	std::cout << "Hello world!" << std::endl;

	Stack S;
	createStack(S);
	Push(S,3);
	Push(S,4);
	Push(S,8);
	pop(S);
	Push(S,2);
	Push(S,3);
	pop(S);
	Push(S,9);
	printInfo(S);
	std::cout << "balik stack" << std::endl;
	balikStack(S);
	printInfo(S);
	return 0;
}
```

### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan7_modul7/output1-unguided1-modul7.png)

Kode ini merupakan implementasi sederhana dari struktur data Stack (tumpukan) menggunakan array statis berukuran tetap. File stack.h mendefinisikan struktur Stack yang berisi array info untuk menyimpan elemen dan variabel top untuk menandai posisi elemen teratas. Beberapa fungsi utama dideklarasikan, seperti createStack untuk inisialisasi stack, Push untuk menambah elemen ke puncak stack, pop untuk menghapus elemen teratas, printInfo untuk menampilkan isi stack dari atas ke bawah, dan balikStack untuk membalik urutan elemen stack. Pada stack.cpp, fungsi-fungsi tersebut diimplementasikan dengan logika sederhana sesuai prinsip LIFO (Last In, First Out). Di main.cpp, program menguji berbagai operasi stack seperti menambah dan menghapus elemen, menampilkan isi stack, serta membalik urutannya. Kode ini memperlihatkan konsep dasar penggunaan stack dan manipulasi data di dalamnya dengan array sebagai media penyimpanan.

### 2. ![Screenshot Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan7_modul7/unguided2-modul7.png)

#### [stack.h]
```C++
#ifndef STACK_H
#define STACK_H

typedef int infotype;

struct Stack {
	infotype info[20];
	int top;
};

void createStack(Stack &S);
void Push(Stack &S, infotype x);
infotype pop(Stack &S);
void pushAscending(Stack &S, infotype x);
void printInfo(const Stack &S);
void balikStack(Stack &S);

#endif
```

#### [stack.cpp]
```C++
#include "stack.h"
#include <iostream>

void createStack(Stack &S)
{
    S.top = 0;
}

void Push(Stack &S, infotype x)
{
    if (S.top < 20)
    {
        S.info[S.top] = x;
        S.top = S.top + 1;
    }
    else
    {
        std::cout << "Stack penuh" << std::endl;
    }
}

infotype pop(Stack &S)
{
    if (S.top > 0)
    {
        S.top = S.top - 1;
        return S.info[S.top];
    }
    else
    {
        std::cout << "Stack kosong" << std::endl;
        return -1;
    }
}

void pushAscending(Stack &S, infotype x)
{
    Stack T;
    createStack(T);
    while (S.top > 0 && S.info[S.top - 1] > x)
    {
        Push(T, pop(S));
    }
    Push(S, x);
    while (T.top > 0)
    {
        Push(S, pop(T));
    }
}

void printInfo(const Stack &S)
{
    std::cout << "[TOP] ";
    for (int i = S.top - 1; i >= 0; i = i - 1)
    {
        std::cout << S.info[i];
        if (i > 0) std::cout << " ";
    }
    std::cout << std::endl;
}

void balikStack(Stack &S)
{
    int i = 0;
    int j = S.top - 1;
    while (i < j)
    {
        infotype temp = S.info[i];
        S.info[i] = S.info[j];
        S.info[j] = temp;
        i = i + 1;
        j = j - 1;
    }
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "stack.h"

int main()
{
    std::cout << "Hello world!" << std::endl;

    Stack S;
    createStack(S);
    pushAscending(S,3);
    pushAscending(S,4);
    pushAscending(S,8);
    pushAscending(S,2);
    pushAscending(S,3);
    pushAscending(S,9);
    printInfo(S);
    std::cout << "balik stack" << std::endl;
    balikStack(S);
    printInfo(S);
    return 0;
}
```

### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan7_modul7/output1-unguided2-modul7.png)

Kode ini merupakan implementasi struktur data Stack (tumpukan) menggunakan array statis, dengan tambahan fitur penyisipan terurut secara ascending. Struktur Stack menyimpan data integer dalam array berukuran 20 dan menggunakan variabel top untuk menandai elemen teratas. Fungsi createStack menginisialisasi stack kosong, Push menambahkan data ke puncak stack, pop menghapus dan mengembalikan elemen teratas, pushAscending menyisipkan elemen baru sambil menjaga urutan dari kecil ke besar menggunakan stack bantu (T), printInfo menampilkan isi stack dari atas ke bawah, dan balikStack membalik urutan elemen dalam stack. Pada main.cpp, program menguji fungsi-fungsi tersebut dengan menambahkan beberapa angka menggunakan pushAscending, menampilkan hasilnya, kemudian membalik urutannya menggunakan balikStack. Kode ini memperlihatkan cara kerja stack dengan prinsip LIFO (Last In, First Out) sekaligus menunjukkan bagaimana elemen dapat dimasukkan dalam urutan yang teratur.

### 3. ![Screenshot Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan7_modul7/unguided3-modul7.png)

#### [stack.h]
```C++
#ifndef STACK_H
#define STACK_H

typedef int infotype;

struct Stack {
    infotype info[20];
    int top;
};

void createStack(Stack &S);
void Push(Stack &S, infotype x);
infotype pop(Stack &S);
void pushAscending(Stack &S, infotype x);
void getInputStream(Stack &S);
void printInfo(const Stack &S);
void balikStack(Stack &S);

#endif
```

#### [stack.cpp]
```C++
#include "stack.h"
#include <iostream>

void createStack(Stack &S)
{
    S.top = 0;
}

void Push(Stack &S, infotype x)
{
    if (S.top < 20)
    {
        S.info[S.top] = x;
        S.top = S.top + 1;
    }
    else
    {
        std::cout << "Stack penuh" << std::endl;
    }
}

infotype pop(Stack &S)
{
    if (S.top > 0)
    {
        S.top = S.top - 1;
        return S.info[S.top];
    }
    else
    {
        std::cout << "Stack kosong" << std::endl;
        return -1;
    }
}

void pushAscending(Stack &S, infotype x)
{
    Stack T;
    createStack(T);
    while (S.top > 0 && S.info[S.top - 1] > x)
    {
        Push(T, pop(S));
    }
    Push(S, x);
    while (T.top > 0)
    {
        Push(S, pop(T));
    }
}

void getInputStream(Stack &S)
{
    char ch;
    while (true)
    {
        ch = std::cin.get();
        if (!std::cin)
            break;
        if (ch == '\r')
            continue;
        if (ch == '\n')
            break;
        if (ch >= '0' && ch <= '9')
            Push(S, ch - '0');
        else
            Push(S, ch);
    }
}

void printInfo(const Stack &S)
{
    std::cout << "[TOP] ";
    for (int i = S.top - 1; i >= 0; i = i - 1)
    {
        std::cout << S.info[i];
        if (i > 0) std::cout << " ";
    }
    std::cout << std::endl;
}

void balikStack(Stack &S)
{
    int i = 0;
    int j = S.top - 1;
    while (i < j)
    {
        infotype temp = S.info[i];
        S.info[i] = S.info[j];
        S.info[j] = temp;
        i = i + 1;
        j = j - 1;
    }
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "stack.h"

int main()
{
    std::cout << "Hello world!" << std::endl;
    Stack S;
    createStack(S);
    getInputStream(S);
    printInfo(S);
    std::cout << "balik stack" << std::endl;
    balikStack(S);
    printInfo(S);
    return 0;
}
```

### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan7_modul7/output1-unguided3-modul7.png)

Kode ini merupakan implementasi struktur data Stack (tumpukan) menggunakan array statis dengan tambahan fitur input karakter dari pengguna. Struktur Stack menyimpan elemen bertipe int dalam array berukuran 20 dengan indeks top untuk menandai posisi elemen teratas. Fungsi createStack menginisialisasi stack kosong, Push menambah data ke puncak stack, pop menghapus elemen teratas, pushAscending menyisipkan data baru secara terurut menaik dengan bantuan stack sementara, getInputStream membaca input karakter satu per satu dari pengguna (baik angka maupun simbol) dan menyimpannya ke dalam stack, printInfo menampilkan isi stack dari atas ke bawah, serta balikStack membalik urutan elemen di dalam stack. Pada main.cpp, program membuat stack, mengambil input dari pengguna melalui keyboard, menampilkannya, lalu membalik dan mencetak kembali isi stack. Kode ini menunjukkan penggunaan konsep LIFO (Last In, First Out) dalam stack serta bagaimana data dapat dimanipulasi dan ditampilkan secara interaktif.

## Kesimpulan
Struktur data stack adalah mekanisme penyimpanan linear yang sangat efisien untuk situasi di mana elemen terakhir yang dimasukkan harus menjadi yang pertama dikeluarkan (LIFO). Dalam konteks pemrograman C++, stack dapat diimplementasikan dengan array, linked list, atau menggunakan adaptor std::stack. Pemilihan implementasi yang tepat akan mempengaruhi efisiensi memori dan kecepatan eksekusi. Meskipun sederhana, stack memainkan peran penting dalam banyak algoritma dan aplikasi (seperti manajemen fungsi, undo/redo, evaluasi ekspresi). Namun, struktur ini kurang cocok jika diperlukan akses acak ke elemen selain puncak atau jika operasi melibatkan banyak penghapusan/penyisipan selain di top. Oleh karena itu, memahami sifat, operasi, implementasi, serta konteks penggunaan stack sangat penting terutama dalam pengembangan simulasi pasar saham virtual atau aplikasi lain menggunakan C++.

## Referensi
[1] AITS-TPT, Data Structures – Unit 2.1: Stack, 2018.
https://aits-tpt.edu.in/wp-content/uploads/2018/08/DS-unit-2.1.pdf

<br> [2] GeeksforGeeks, Introduction to Stack Data Structure and Algorithm Tutorials, 2023.
https://www.geeksforgeeks.org/dsa/introduction-to-stack-data-structure-and-algorithm-tutorials/

<br>[3] Wikipedia, Stack (abstract data type), 2024.
https://en.wikipedia.org/wiki/Stack_(abstract_data_type)

<br>[4] D. Hendler, N. Shavit, L. Yerushalmi, “A Dynamic Elimination-Combining Stack Algorithm,” arXiv:1106.6304, 2010.

<br>[5] J. Barbay et al., “Experimental Study of Compressed Stack Algorithms in Limited Memory Environments,” arXiv:1706.04708, 2017.

<br>[6] Y. Zhang, “Research on How to Optimize Data Structures with C++ Language,” Francis Academic Press, 2021.

<br>[7] Acceldata, Stack Data Structure Explained: How LIFO Drives Modern Computing, 2023.
https://www.acceldata.io/blog/stack-data-structure-explained-how-lifo-drives-modern-computing