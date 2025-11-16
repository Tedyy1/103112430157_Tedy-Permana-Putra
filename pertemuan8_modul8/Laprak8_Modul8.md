# <h1 align="center">Laporan Praktikum Modul 8 - QUEUE </h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
### 1. Definisi Teori Queue
Teori antrian (queueing theory) adalah cabang dari riset operasi dan probabilitas yang mempelajari model barisan tunggu (antrian) ketika entitas (pelanggan, paket, tugas) menunggu untuk dilayani oleh server.

### 2. Komponen Sistem Queue
Sistem antrian terdiri dari beberapa elemen utama:
- Kedatangan (arrival): pola kedatangan entitas ke sistem, yang bisa berupa proses stokastik seperti Poisson. 
- Pelayanan (service): waktu pelayanan oleh server, bisa memiliki distribusi tertentu (misalnya eksponensial). 
- Disiplin antrian (queue discipline): aturan urutan pelayanan, misalnya FIFO (First-In First-Out), prioritas, dan sebagainya. 
- Struktur sistem: jumlah saluran pelayanan (single / multiple), fase pelayanan (single/multi-phase). 
- Kinerja sistem: metrik seperti waktu tunggu rata-rata, jumlah entitas dalam antrian/sistem, probabilitas server sibuk, dsb.

### 3. Modul Queue Klasik
- Model M/M/1: model antrian dengan satu server, distribusi kedatangan Poisson, dan waktu layanan eksponensial. Banyak analisis dasar menggunakan model ini. 
Arteii Journal
- Proses birth–death: model stokastik dasar untuk banyak model antrian, di mana “birth” mewakili kedatangan dan “death” mewakili selesainya layanan. 
- Rumus Lindley: salah satu persamaan fundamental untuk menghitung waktu tunggu dalam antrian (queue-length evolution). 
- Aproksimasi Kingman (Kingman’s formula): rumus perkiraan untuk mean waiting time di antrian G/G/1 (generik, kedatangan & layanan bisa variatif) berdasarkan utilisasi dan variabilitas.

### 4. Estimasi Parameter Queue
Dalam penelitian terkini, salah satu topik penting adalah estimasi parameter dan status sistem antrian (seperti tingkat kedatangan λ, pemanfaatan sistem, panjang antrian) dari data observasi. Contohnya, A Survey of Parameter and State Estimation in Queues mengklasifikasikan berbagai paradigma estimasi (contoh: Bayesian, pendekatan sampling, inferensi balik, dsb).

### 5. Penerapan Teori Queue
- Dalam manajemen operasional layanan (misalnya bank, rumah makan), teori antrian digunakan untuk merancang jumlah server yang optimal agar waktu tunggu minimal dan efisiensi maksimal. 
- Simulasi antrian sering digunakan untuk menganalisis sistem nyata (misalnya kantin sekolah) menggunakan model yang sesuai (FIFO, multi-server). 
- Dalam konteks industri laboratorium atau pengujian material, teori antrian dipakai untuk menganalisis dan memprediksi antrian pada fasilitas pengujian agar throughput dan utilisasi dapat dioptimalkan. 
- Penerapan prioritas: sistem antrian dengan prioritas (priority queue) dan algoritma seperti priority queue descending dipakai dalam layanan kritikal seperti pelayanan kesehatan.

### 6. Pertimbangan Biaya dan Trade-Off
Salah satu tujuan teori antrian adalah menemukan keseimbangan antara biaya pelayanan (misalnya biaya menambah server) dan biaya waktu tunggu (kerugian pelanggan menunggu).

### 7. Model Khusus dan Kemajuan Teoritis
- Retrial queues: model di mana entitas yang gagal dilayani (misalnya karena penuh) akan “coba lagi” nanti. Survey retrial queue menyoroti aplikasi dan solusi teoritis untuk model semacam ini. 
- Queueing-inventory systems: integrasi antara teori antrian dan inventori; misalnya dalam supply chain, persediaan + permintaan + antrian saling berhubungan. 
- Antrian dengan informasi tertunda: penelitian asimptotik menunjukkan bagaimana delay informasi (misalnya pelanggan mendapat info panjang antrian dengan delay) dapat memengaruhi stabilitas sistem. 
- Simulasi quantum: penelitian terbaru bahkan mencoba mensimulasikan antrian (misal M/M/1) menggunakan komputasi kuantum.


## Guided 

### 1. Implementasi dan Pengujian Struktur Data Queue Berbasis Linked List
#### [queue.h]
```C++
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
#include <string>
using namespace std;

struct Node {
    string nama;
    Node* next;
};

struct queue {
    Node* head;
    Node* tail;
};

void CreateQueue(queue &Q);
bool isEmpty(queue Q);
bool isFull(queue Q);   
void enQueue(queue &Q, const string &nama);
void deQueue(queue &Q);
void viewQueue(queue Q);
void clearQueue(queue &Q);

#endif
```

#### [queue.cpp]
```C++
#include "queue.h"
using namespace std;

void CreateQueue(queue &Q) {
    Q.head = nullptr;
    Q.tail = nullptr;
}

bool isEmpty(queue Q) {
    return Q.head == nullptr;
}

bool isFull(queue) {
    return false;
}

void enQueue(queue &Q, const string &nama) {
    Node* baru = new Node{nama, nullptr};
    if (isEmpty(Q)) {
        Q.head = Q.tail = baru;
    } else {
        Q.tail->next = baru;
        Q.tail = baru;
    }
    cout << "nama " << nama << " berhasil ditambahkan kedalam queue!" << endl;
}

void deQueue(queue &Q) {
    if (isEmpty(Q)) {
        cout << "Queue kosong!" << endl;
        return;
    }
    Node* hapus = Q.head;
    cout << "Menghapus data " << hapus->nama << "..." << endl;
    Q.head = Q.head->next;
    if (Q.head == nullptr) {
        Q.tail = nullptr;
    }
    delete hapus;
}

void viewQueue(queue Q) {
    if (isEmpty(Q)) {
        cout << "Queue kosong!" << endl;
        return;
    }
    int i = 1;
    for (Node* p = Q.head; p != nullptr; p = p->next) {
        cout << i++ << ". " << p->nama << endl;
    }
}

void clearQueue(queue &Q) {
    while (!isEmpty(Q)) {
        deQueue(Q);
    }
}
```

#### [main.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

int main() {
    queue Q;
    CreateQueue(Q);

    enQueue(Q, "dhimas");
    enQueue(Q, "Arvin");
    enQueue(Q, "Rizal");
    enQueue(Q, "Hafizh");
    enQueue(Q, "Fathur");
    enQueue(Q, "Atha");
    cout << endl;

    cout << "--- Isi Queue Setelah enQueue ---" << endl;
    viewQueue(Q);

    deQueue(Q);
    deQueue(Q);
    deQueue(Q);
    deQueue(Q);
    cout << endl;

    cout << "--- Isi Queue Setelah deQueue ---" << endl;
    viewQueue(Q);

    clearQueue(Q);
    return 0;
}
```
Kode ini menampilkan bagaimana sebuah queue dibangun menggunakan struktur linked list, dimulai dari pendefinisian struktur data serta deklarasi fungsi pada queue.h, dilanjutkan dengan implementasi seluruh operasi queue pada queue.cpp, dan diakhiri dengan pengujian langsung di main.cpp. Melalui proses penambahan elemen ke bagian belakang, penghapusan dari bagian depan, penampilan isi queue, dan pembersihan seluruh data, program ini menggambarkan alur kerja queue yang mengikuti prinsip FIFO (First In, First Out) secara jelas dan terstruktur.

### 2. Implementasi Queue Statis dengan Berbagai Metode Pergerakan Head dan Tail
#### [queue.h]
```C++
#ifndef QUEUE_H
#define QUEUE_H


#include <iostream>
using namespace std;

const int MAKSIMAL = 5;

struct queue{
    string nama[MAKSIMAL];
    int head;
    int tail;
};

bool isFull(queue Q);
bool isEmpty(queue Q);
void CreateQueue(queue &Q);
void enQueue(queue &Q, string nama);
void deQueue(queue &Q);
void viewQueue(queue Q);

#endif
```

#### [queue.cpp]
```C++
#include "queue.h"
#include <iostream>

using namespace std;

// NOTE : 
// Implementasi 1 = head diam, tail bergerak (Queue Linear Statis, kerana head nya tetap diam)
// Implementasi 2 = head bergerak, tail bergerak (Queue Linear Dinamis, karena head & tail nya sama-sama bergerak)
// Implementasi 3 = head dan tail berputar (Queue Circular, karena jika udh mentok tapi masih ada space, diputar sehingga tail bisa ada didepan head)

bool isEmpty(queue Q){
    if(Q.head == -1 && Q.tail == -1){
        return true;
    } else {
        return false;
    }
}

//isFull implmenetasi 1 & 2
bool isFull(queue Q){
    if(Q.tail == MAKSIMAL - 1){
        return true;
    } else {
        return false;
    }
}

// //isFull implementasi 3
// bool isFull(queue Q){
//     if((Q.tail + 1) % MAKSIMAL == Q.head){
//         return true;
//     } else {
//         return false;
//     }
// }

void CreateQueue(queue &Q){ //terbentuk queue dengan head = -1 dan tail = -1 
    Q.head = -1;
    Q.tail = -1;
}
 

//enqueue implementasi 1 & 2
void enQueue(queue &Q, string nama){
    if(isFull(Q) == true){
        cout << "Queue sudah penuh!" << endl;
    } else {
        if(isEmpty(Q) == true){
            Q.head = Q.tail = 0;
        } else {
            Q.tail++;
        }
        Q.nama[Q.tail] = nama;
        cout << "nama " << nama << " berhasil ditambahkan kedalam queue!" << endl;
    }
}

// //enQueue implementasi 3
// void enQueue(queue &Q, string nama){
//     if(isFull(Q) == true){
//         cout << "Queue sudah penuh!" << endl;
//     } else {
//         if(isEmpty(Q) == true){
//             Q.head = Q.tail = 0;
//         } else {
//             Q.tail = (Q.tail + 1) % MAKSIMAL; // bergerak melingkar
//         }
//         Q.nama[Q.tail] = nama;
//         cout << "nama " << nama << " berhasil ditambahkan kedalam queue!" << endl;
//     }
// }

//dequeue implementasi 1
void deQueue(queue &Q){
    if(isEmpty(Q) == true){
        cout << "Queue kosong!" << endl;
    } else {
        cout << "Mengahapus data " << Q.nama[Q.head] << "..." << endl;
        for(int i = 0; i < Q.tail; i++){
            Q.nama[i] =  Q.nama[i+1];
        }
        Q.tail--;
        if(Q.tail < 0){ //kalo semua isi queue nya udh dikelaurin, set head & tail ke -1
            Q.head = -1;
            Q.tail = -1;
        }
    }
}

// //dequeue implementasi 2
// void deQueue(queue &Q){
//     if(isEmpty(Q) == true){
//         cout << "Queue kosong!" << endl;
//     } else {
//         cout << "Mengahapus data " << Q.nama[Q.head] << "..." << endl;
//         Q.head++;
//         if(Q.head > Q.tail){ //kalo elemennya udh abis (head akan lebih 1 dari tail), maka reset ulang head & tail ke -1
//             Q.head = -1;
//             Q.tail = -1;
//         }
//     }
// }

// //deQueue implementasi 3
// void deQueue(queue &Q){
//     if(isEmpty(Q) == true){
//         cout << "Queue kosong!" << endl;
//     } else {
//         cout << "Mengahapus data " << Q.nama[Q.head] << "..." << endl;
//         if(Q.head == Q.tail){ //kalo elemennya tinggal 1, langsungkan saja head & tail nya reset ke -1
//             Q.head = -1;
//             Q.tail = -1;
//         } else {
//             Q.head = (Q.head + 1) % MAKSIMAL; // bergerak melingkar
//         }
//     }
// }

//viewQueue implementasi 1 & 2
void viewQueue(queue Q){
    if(isEmpty(Q) == true){
        cout << "Queue kosong!" << endl;
    } else {
        for(int i = Q.head; i <= Q.tail; i++){
            cout << i -  Q.head + 1 << ". " << Q.nama[i] << endl;
        }
    }
    cout << endl;
}

// //viewQueue implementasi 3
// void viewQueue(queue Q){
//     if(isEmpty(Q) == true){
//         cout << "Queue kosong!" << endl;
//     } else {
//         int i = Q.head;
//         int count = 1;
//         while(true){
//             cout << count << ". " << Q.nama[i] << endl;
//             if(i == Q.tail){
//                 break;
//             }
//             i = (i + 1) % MAKSIMAL;
//             count++;
//         }   
//     }
// }
```

#### [main.cpp]
```C++
#include "queue.h"
#include <iostream>

using namespace std;

int main(){
    queue Q;

    CreateQueue(Q);
    enQueue(Q, "dhimas");
    enQueue(Q, "Arvin");
    enQueue(Q, "Rizal");
    enQueue(Q, "Hafizh");
    enQueue(Q, "Fathur");
    enQueue(Q, "Daffa");
    cout << endl;

    cout << "--- Isi Queue Setelah enQueue ---" << endl;
    viewQueue(Q);
    cout << endl;

    deQueue(Q);
    deQueue(Q);
    deQueue(Q);
    deQueue(Q);
    // deQueue(Q);
    // deQueue(Q);
    cout << endl;

    cout << "--- Isi Queue Setelah deQueue ---" << endl;
    viewQueue(Q);

    return 0;
}
```
Kode ini menunjukkan bagaimana struktur data queue direalisasikan menggunakan array statis berukuran tetap, lengkap dengan tiga variasi implementasi: queue linear dengan head diam dan tail bergerak, queue linear dengan head dan tail bergerak, serta queue circular yang memungkinkan pergerakan melingkar untuk efisiensi ruang. Melalui fungsi-fungsi seperti CreateQueue, isFull, isEmpty, enQueue, deQueue, dan viewQueue, program ini memperlihatkan cara menambah, menghapus, dan menampilkan elemen queue. Bagian main.cpp digunakan untuk menguji operasi-operasi tersebut, memperlihatkan bagaimana data masuk dan keluar sesuai prinsip FIFO (First In, First Out) pada berbagai skenario implementasi.

## Unguided 

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan8_modul8/unguided1-modul8.png)

#### [queue.h]
```C++
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

typedef int infotype;

struct Queue {
    infotype info[5];
    int head;
    int tail;
};

void createQueue(Queue &Q);
bool isEmptyQueue(const Queue &Q);
bool isFullQueue(const Queue &Q);
void enqueue(Queue &Q, infotype x);
infotype dequeue(Queue &Q);
void printInfo(const Queue &Q);

#endif
```

#### [queue.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

void createQueue(Queue &Q)
{
    Q.head = -1;
    Q.tail = -1;
}

bool isEmptyQueue(const Queue &Q)
{
    return Q.head == -1;
}

bool isFullQueue(const Queue &Q)
{
    return Q.tail == 4;
}

void enqueue(Queue &Q, infotype x)
{
    if (isEmptyQueue(Q))
    {
        Q.head = 0;
        Q.tail = 0;
        Q.info[Q.tail] = x;
    }
    else if (!isFullQueue(Q))
    {
        Q.tail = Q.tail + 1;
        Q.info[Q.tail] = x;
    }
    else
    {
        std::cout << "Queue penuh" << std::endl;
    }
}

infotype dequeue(Queue &Q)
{
    if (!isEmptyQueue(Q))
    {
        infotype val = Q.info[0];
        for (int i = 0; i < Q.tail; i = i + 1)
        {
            Q.info[i] = Q.info[i + 1];
        }
        Q.tail = Q.tail - 1;
        if (Q.tail < 0)
        {
            Q.head = -1;
            Q.tail = -1;
        }
        return val;
    }
    else
    {
        std::cout << "Queue kosong" << std::endl;
        return -1;
    }
}

void printInfo(const Queue &Q)
{
    if (isEmptyQueue(Q))
    {
        std::cout << Q.head << " - " << Q.tail << "  : " << "empty queue" << std::endl;
        return;
    }
    std::cout << Q.head << " - " << Q.tail << "  : ";
    for (int i = 0; i <= Q.tail; i = i + 1)
    {
        std::cout << Q.info[i];
        if (i < Q.tail) std::cout << " ";
    }
    std::cout << std::endl;
}
```

#### [main.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

int main()
{
    std::cout << "Hello world!" << std::endl;

    Queue Q;
    createQueue(Q);

    std::cout << "---------------------------" << std::endl;
    std::cout << " H - T  : Queue Info" << std::endl;
    std::cout << "---------------------------" << std::endl;

    printInfo(Q);
    enqueue(Q, 5); printInfo(Q);
    enqueue(Q, 2); printInfo(Q);
    enqueue(Q, 7); printInfo(Q);
    dequeue(Q); printInfo(Q);
    dequeue(Q); printInfo(Q);
    enqueue(Q, 4); printInfo(Q);
    dequeue(Q); printInfo(Q);
    dequeue(Q); printInfo(Q);

    return 0;
}
```

### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan8_modul8/output1-unguided1-modul8.png)

Kode ini mengimplementasikan struktur data queue statis menggunakan array berukuran lima elemen, dengan penanda head dan tail untuk menentukan posisi awal dan akhir antrian. Fungsi createQueue menginisialisasi queue kosong, isEmptyQueue dan isFullQueue memeriksa kondisi antrian, enqueue menambahkan elemen ke posisi tail selama queue belum penuh, dan dequeue menghapus elemen terdepan lalu menggeser semua elemen sisanya ke kiri. Fungsi printInfo digunakan untuk menampilkan isi queue beserta posisi head dan tail. Pada program utama, berbagai operasi enqueue dan dequeue diuji untuk menunjukkan bagaimana data masuk dan keluar sesuai prinsip FIFO (First In, First Out). 

### 2. Buatlah implementasi ADT Queue pada file “queue.cpp” dengan menerapkan mekanisme queue Alternatif 2 (head bergerak, tail bergerak).

#### [queue.h]
```C++
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

typedef int infotype;

struct Queue {
    infotype info[5];
    int head;
    int tail;
};

void createQueue(Queue &Q);
bool isEmptyQueue(const Queue &Q);
bool isFullQueue(const Queue &Q);
void enqueue(Queue &Q, infotype x);
infotype dequeue(Queue &Q);
void printInfo(const Queue &Q);

#endif
```

#### [queue.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

void createQueue(Queue &Q)
{
    Q.head = -1;
    Q.tail = -1;
}

bool isEmptyQueue(const Queue &Q)
{
    return Q.head == -1;
}

bool isFullQueue(const Queue &Q)
{
    if (Q.head == -1) return false; 
    const int MAX = 5;
    return ((Q.tail + 1) % MAX) == Q.head;
}

void enqueue(Queue &Q, infotype x)
{
    const int MAX = 5;
    if (isFullQueue(Q))
    {
        std::cout << "Queue penuh" << std::endl;
        return;
    }

    if (isEmptyQueue(Q))
    {
        Q.head = 0;
        Q.tail = 0;
        Q.info[Q.tail] = x;
    }
    else
    {
        Q.tail = (Q.tail + 1) % MAX;
        Q.info[Q.tail] = x;
    }
}

infotype dequeue(Queue &Q)
{
    if (isEmptyQueue(Q))
    {
        std::cout << "Queue kosong" << std::endl;
        return -1;
    }

    infotype val = Q.info[Q.head];
    const int MAX = 5;
    if (Q.head == Q.tail)
    {
        Q.head = -1;
        Q.tail = -1;
    }
    else
    {
        Q.head = (Q.head + 1) % MAX;
    }
    return val;
}

void printInfo(const Queue &Q)
{
    if (isEmptyQueue(Q))
    {
        std::cout << Q.head << " - " << Q.tail << "  : " << "empty queue" << std::endl;
        return;
    }
    std::cout << Q.head << " - " << Q.tail << "  : ";
    const int MAX = 5;
    int i = Q.head;
    while (true)
    {
        std::cout << Q.info[i];
        if (i == Q.tail) break;
        std::cout << " ";
        i = (i + 1) % MAX;
    }
    std::cout << std::endl;
}
```

#### [main.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

int main()
{
    std::cout << "Hello world!" << std::endl;

    Queue Q;
    createQueue(Q);

    std::cout << "---------------------------" << std::endl;
    std::cout << " H - T  : Queue Info" << std::endl;
    std::cout << "---------------------------" << std::endl;

    printInfo(Q);
    enqueue(Q, 5); printInfo(Q);
    enqueue(Q, 2); printInfo(Q);
    enqueue(Q, 7); printInfo(Q);
    dequeue(Q); printInfo(Q);
    dequeue(Q); printInfo(Q);
    enqueue(Q, 4); printInfo(Q);
    dequeue(Q); printInfo(Q);
    dequeue(Q); printInfo(Q);

    return 0;
}
```

### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan8_modul8/output1-unguided2-modul8.png)

Kode ini menerapkan struktur data circular queue menggunakan array berukuran tetap (5 elemen), di mana posisi head dan tail bergerak secara melingkar menggunakan operasi modulo untuk memaksimalkan penggunaan ruang. Fungsi createQueue menginisialisasi queue kosong, isEmptyQueue dan isFullQueue memeriksa kondisi antrian, enqueue menambah elemen dengan memutar posisi tail, dan dequeue menghapus elemen terdepan sambil memutar posisi head atau mereset queue jika tinggal satu elemen. Fungsi printInfo menampilkan seluruh isi queue secara berurutan meskipun posisi array melingkar. Pada main.cpp, operasi enqueue dan dequeue diuji untuk menunjukkan cara kerja FIFO pada circular queue.

### 3. Buatlah implementasi ADT Queue pada file “queue.cpp” dengan menerapkan mekanisme queue Alternatif 3 (head dan tail berputar)

#### [queue.h]
```C++
#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>
using namespace std;

typedef int infotype;

struct Queue {
    infotype info[5];
    int head;
    int tail;
};

void createQueue(Queue &Q);
bool isEmptyQueue(const Queue &Q);
bool isFullQueue(const Queue &Q);
void enqueue(Queue &Q, infotype x);
infotype dequeue(Queue &Q);
void printInfo(const Queue &Q);

#endif
```

#### [queue.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

void createQueue(Queue &Q)
{
    Q.head = -1;
    Q.tail = -1;
}

bool isEmptyQueue(const Queue &Q)
{
    return Q.head == -1;
}

bool isFullQueue(const Queue &Q)
{
    return (Q.tail + 1) % 5 == Q.head;
}

void enqueue(Queue &Q, infotype x)
{
    if (isEmptyQueue(Q))
    {
        Q.head = 0;
        Q.tail = 0;
        Q.info[Q.tail] = x;
    }
    else if (!isFullQueue(Q))
    {
        Q.tail = (Q.tail + 1) % 5;
        Q.info[Q.tail] = x;
    }
    else
    {
        std::cout << "Queue penuh" << std::endl;
    }
}

infotype dequeue(Queue &Q)
{
    if (!isEmptyQueue(Q))
    {
        infotype val = Q.info[Q.head];
        if (Q.head == Q.tail)
        {
            Q.head = -1;
            Q.tail = -1;
        }
        else
        {
            Q.head = (Q.head + 1) % 5;
        }
        return val;
    }
    else
    {
        std::cout << "Queue kosong" << std::endl;
        return -1;
    }
}

void printInfo(const Queue &Q)
{
    if (isEmptyQueue(Q))
    {
        std::cout << Q.head << " - " << Q.tail << "  : " << "empty queue" << std::endl;
        return;
    }
    std::cout << Q.head << " - " << Q.tail << "  : ";
    int i = Q.head;
    while (true)
    {
        std::cout << Q.info[i];
        if (i == Q.tail) break;
        std::cout << " ";
        i = (i + 1) % 5;
    }
    std::cout << std::endl;
}
```

#### [main.cpp]
```C++
#include "queue.h"
#include <iostream>
using namespace std;

int main()
{
    std::cout << "Hello world!" << std::endl;

    Queue Q;
    createQueue(Q);

    std::cout << "---------------------------" << std::endl;
    std::cout << " H - T  : Queue Info" << std::endl;
    std::cout << "---------------------------" << std::endl;

    printInfo(Q);
    enqueue(Q, 5); printInfo(Q);
    enqueue(Q, 2); printInfo(Q);
    enqueue(Q, 7); printInfo(Q);
    dequeue(Q); printInfo(Q);
    dequeue(Q); printInfo(Q);
    enqueue(Q, 4); printInfo(Q);
    dequeue(Q); printInfo(Q);
    dequeue(Q); printInfo(Q);

    return 0;
}
```

### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan8_modul8/output1-unguided3-modul8.png)

Kode ini mengimplementasikan circular queue menggunakan array berukuran lima elemen, di mana posisi head dan tail dapat berputar menggunakan operasi modulo agar ruang array dimanfaatkan secara maksimal. Fungsi createQueue menginisialisasi queue dalam keadaan kosong, isEmptyQueue dan isFullQueue memeriksa apakah queue kosong atau penuh, enqueue menambahkan data dengan menggeser tail secara melingkar, dan dequeue menghapus elemen terdepan serta menggeser head atau mereset queue jika tinggal satu elemen. Fungsi printInfo menampilkan isi queue secara berurutan mengikuti posisi head dan tail. Pada main.cpp, operasi enqueue dan dequeue diuji untuk memperlihatkan cara kerja antrian mengikuti prinsip FIFO dalam bentuk circular queue.

## Kesimpulan
Teori antrian merupakan alat analitis matematis yang sangat kuat untuk memahami dan mengoptimalkan sistem pelayanan yang melibatkan waktu tunggu.

Dengan memodelkan kedatangan, pelayanan, dan aturan antrian, kita bisa memprediksi metrik penting seperti waktu tunggu rata-rata, utilisasi server, dan panjang antrian, yang sangat berguna dalam perancangan sistem nyata.

Estimasi parameter dan status sistem antrian semakin berkembang, memungkinkan analisis sistem yang lebih adaptif dan berbasis data nyata.

Model-model antrian klasik (seperti M/M/1, birth–death) masih sangat relevan, tetapi model yang lebih kompleks (retrials, antrian-inventori, antrian dengan delay, dsb) memberikan fleksibilitas untuk aplikasi dunia nyata dengan karakteristik khusus.

Ada trade-off penting antara biaya menambah fasilitas pelayanan dengan biaya yang timbul akibat waktu tunggu pelanggan; teori antrian membantu menyeimbangkan faktor-faktor tersebut.

Teknologi dan teori baru (misalnya simulasi kuantum, integrasi dengan manajemen inventori) membuka kemungkinan penerapan antrian pada domain baru dan meningkatkan efisiensi serta akurasi analisis.

## Referensi
[1] A. Asanjarani, Y. Nazarathy, and P. Taylor, “A survey of parameter and state estimation in queues,” arXiv preprint arXiv:2012.14614, 2020.

<br>[2] T. Phung-Duc, “Retrial queueing models: A survey on theory and applications,” arXiv preprint arXiv:1906.09560, 2019.

<br>[3] K. Salini, P. S. Arya, and M. Rangaswamy, “Queueing-inventory systems: A survey,” arXiv preprint arXiv:2308.06518, 2023.

<br>[4] J. Pender, R. Rand, and E. Wesson, “An asymptotic analysis of queues with delayed information and time varying arrival rates,” arXiv preprint arXiv:1701.05443, 2017.

<br>[5] M. Koren and O. Peretz, “Quantum simulation of single-server Markovian queues: A dynamic amplification approach,” arXiv preprint arXiv:2410.08252, 2024.

<br>[6] R. Alam and M. T. Safirin, “Analisis Sistem Antrian Pengujian Material Pada Laboratorium Menggunakan Queuing Theory,” Venus: Jurnal Teknik, vol. 2, no. 1, pp. 45–52, 2021.

<br>[7] Y. Fortunatus, “Penerapan Teori Antrian dalam Pengukuran Sistem Layanan,” Prosiding SNTEK, 2020.

<br>[8] M. Aleksander, “Study of queuing theory (M/M/M) and optimization services teller at retail banking,” Jurnal Ekonomi, vol. 3, no. 2, pp. 15–22, 2014.

<br>[9] D. Gross, J. F. Shortle, J. M. Thompson, and C. M. Harris, Fundamentals of Queueing Theory, 5th ed. Hoboken, NJ, USA: Wiley, 2018.