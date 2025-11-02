# <h1 align="center">Laporan Praktikum Modul 5 - DOUBLY LINKED LIST (BAGIAN PERTAMA) </h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
### 1. Definisi dan Struktur Dasar
Sebuah doubly linked list adalah suatu struktur data dinamis di mana setiap elemen (node) memiliki setidaknya tiga bagian:

- sebuah bidang data (value)
- sebuah pointer/link ke node berikutnya (next)
- sebuah pointer/link ke node sebelumnya (previous)

Sehingga traversal (menjelajah) bisa dilakukan baik ke arah depan maupun ke arah belakang[1].

Contoh sederhana: 
```
NULL <-> node1 <-> node2 <-> node3 <-> NULL.
```

Karena memiliki dua arah link, operasi seperti penghapusan node atau traversal dari belakang ke depan menjadi lebih mudah dibandingkan singly linked list.

### 2. Operasi pada Doubly Linked List

- Penyisipan (insertion): bisa di awal, di tengah, atau di akhir list. Karena ada pointer ke previous dan next, penyisipan setelah atau sebelum node tertentu dapat dilakukan dengan memperbarui sedikit link.
- Penghapusan (deletion): karena setiap node tahu node sebelumnya, penghapusan sebuah node tertentu tidak selalu memerlukan traversal panjang untuk menemukan node sebelumnya (berbeda dengan singly linked list).
- Traversal: bisa maju (menggunakan next) ataupun mundur (menggunakan previous).
- Pencarian (searching): meskipun tetap berlaku O(n) dalam kasus umum jika tidak ada struktur tambahan, tapi kemudahan traversal dua arah bisa membantu implementasi algoritma tertentu.

### 3. Kelebihan dan Kekurangan
#### Kelebihan
- Traversal dua arah: karena adanya pointer ke previous dan next. Ini sangat berguna saat kita butuh pindah ke belakang setelah traversal ke depan.
- Penghapusan node secara langsung: jika kita punya pointer ke node yang akan dihapus, kita bisa memperbaharui pointer previous dan next langsung tanpa perlu mencari node sebelumnya.
- Penyisipan pada posisi arbitrary: relatif lebih mudah dibandingkan singly linked list pada beberapa kasus.

#### Kekurangan
- Overhead tambahan: setiap node memerlukan dua pointer (previous & next) dibanding singly linked list hanya satu pointer.
- Memori lebih banyak: karena pointer tambahan.
- Kompleksitas pengelolaan: jika tidak hati-hati, pointer previous/next bisa menjadi null atau dangling, menyebabkan bugs.

Contoh implementasi yang mencoba optimasi memori menyoroti bahwa overhead memori bisa signifikan. Misalnya artikel “A Memory-Efficient Doubly Linked List” mengulas cara alternatif untuk mengurangi overhead pointer[2].

### 4. Variasi dan Kontemporer
- DLL pada lingkungan multi‐thread / concurrent: Keperluan untuk struktur data yang bisa digunakan secara paralel menghasilkan penelitian seperti “Lock-Free Deques and Doubly Linked Lists” yang membahas implementasi DLL yang lock-free, mendukung akses paralel dan traversal melalui node yang telah dihapus[3].
- DLL untuk simulasi atau domain khusus: Contoh “Cell Lists Method Based on Doubly Linked Lists for Monte Carlo Simulation” menggunakan DLL untuk manajemen partikel dalam simulasi fisik.
[4].
- Heuristik reorganisasi untuk DLL: Contoh “A Short Note on Doubly-Linked List Reorganizing Heuristics” yang membahas heuristik memoriless untuk mempertahankan daftar secara optimal[5].

### 5. Konteks Penggunaan dan Relevansi terhadap Simulasi / Aplikasi
Dalam konteks aplikasi yang dinamis (seperti simulasi pasar saham virtual yang Anda kerjakan dalam bahasa Go), penggunaan dll bisa relevan ketika Anda membutuhkan:
- Struktur data yang memungkinkan traversal baik ke depan maupun ke belakang (misalnya histori transaksi, undo/redo, atau bergerak bolak-balik dalam waktu).
- Penyisipan dan penghapusan elemen dengan posisi yang tidak tetap atau sering berubah.
- Memori yang dikelola secara dinamis (misalnya jumlah elemen tidak diketahui di awal).

Namun, juga perlu mempertimbangkan bahwa dalam banyak kasus modern, array dinamik atau struktur data berbasis vektor/array mungkin lebih efisien dalam hal cache/memory locality. Seperti dicatat dalam diskusi forum bahwa linked list kadang-kala kurang optimal karena elemen tersebar di memori.

## Guided 

### 1. Program Manajemen Data Makanan dengan Double Linked List
#### [listMakanan.h]
```C++
#ifndef LISTMAKANAN_H
#define LISTMAKANAN_H
#define Nil NULL

#include<iostream>
#include<string>
using namespace std;

struct makanan{
    string nama;
    string jenis; 
    float harga;
    float rating; 
};

typedef makanan dataMakanan;

typedef struct node *address;

struct node{
    dataMakanan isidata;
    address next;
    address prev;
};

struct linkedlist{
    address first;
    address last;
};

bool isEmpty(linkedlist List);
void createList(linkedlist &List);
address alokasi(string nama, string jenis, float harga, float rating);
void dealokasi(address &node);

void insertFirst(linkedlist &List, address nodeBaru);
void insertLast(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address Prev);
void insertBefore(linkedlist &List, address nodeBaru, address nodeNext);

void printList(linkedlist List);

void updateFirst(linkedlist List);
void updateLast(linkedlist List);
void updateAfter(linkedlist List, address prev);
void updateBefore(linkedlist List, address nodeNext);

#endif
```

#### [listMakanan.cpp]
```C++
#include "listMakanan.h"
#include <iostream>
using namespace std;

bool isEmpty(linkedlist List) {
    if(List.first == Nil){
        return true; 
    } else {
        return false;
    }
}

void createList(linkedlist &List) {
    List.first = Nil;
    List.last = Nil;
}

address alokasi(string nama, string jenis, float harga, float rating) { 
    address nodeBaru = new node;
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.jenis = jenis; 
    nodeBaru->isidata.harga = harga;
    nodeBaru->isidata.rating =  rating;
    nodeBaru->next = Nil;
    nodeBaru->prev = Nil;
    return nodeBaru;
}

void dealokasi(address &node) {
    node->next = Nil;
    node->prev = Nil;
    delete node;
}

void insertFirst(linkedlist &List, address nodeBaru){
    if (isEmpty(List)) {
        List.first = List.last = nodeBaru;
    } else {
        nodeBaru->next = List.first;
        List.first->prev = nodeBaru;
        List.first = nodeBaru;
    }
    cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan sebagai node pertama list" << endl;
}

void insertLast(linkedlist &List, address nodeBaru){
    if(isEmpty(List) == true){
        List.first = List.last = nodeBaru;
    } else {
        nodeBaru->prev = List.last;
        List.last->next = nodeBaru;
        List.last = nodeBaru;
    }
    cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan sebagai node terakhir list" << endl;
}

void insertAfter(linkedlist &List, address nodeBaru, address nodePrev){
    if(isEmpty(List) == true){
        List.first = List.last = nodeBaru;
    } else {
        if (nodePrev != Nil){
            if(nodePrev == List.last){
                insertLast(List, nodeBaru);
            } else {
                nodeBaru->next = nodePrev->next;
                nodeBaru->prev = nodePrev;
                (nodePrev->next)->prev = nodeBaru;
                nodePrev->next = nodeBaru;
                cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan setelah node " << nodePrev->isidata.nama << endl;
            }
        } else {
            cout << "node sebelumnya (nodePrev) tidak valid!" << endl;
        }
    }
}

void insertBefore(linkedlist &List, address nodeBaru, address nodeNext){
    if(isEmpty(List) == true){
        List.first = List.last = nodeBaru;
    } else {
        if (nodeNext != Nil){
            if(nodeNext == List.first){
                insertFirst(List, nodeBaru);
            } else {
                nodeBaru->next = nodeNext;
                nodeBaru->prev = nodeNext->prev;
                (nodeNext->prev)->next = nodeBaru;
                nodeNext->prev = nodeBaru;
                cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan sebelum node " << nodeNext->isidata.nama << endl;
            }
        } else {
            cout << "node setelahnya (nodeNext) tidak valid!" << endl;
        }
    }
}

void printList(linkedlist List) {
    if (isEmpty(List) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama makanan : " << nodeBantu->isidata.nama << endl;
            cout << "Jenis        : " << nodeBantu->isidata.jenis << endl;
            cout << "Harga        : " << nodeBantu->isidata.harga << endl; 
            cout << "Rating       : " << nodeBantu->isidata.rating << endl;
            cout << "-------------------------------" << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

void updateFirst(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node pertama : " << endl;
        cout << "Nama makanan : ";
        getline(cin, List.first->isidata.nama);
        cout << "Jenis makanan : ";
        getline(cin, List.first->isidata.jenis);
        cout << "Harga : ";
        cin >> List.first->isidata.harga;
        cout << "Rating : ";
        cin >> List.first->isidata.rating;
        cin.ignore(); //menghapus karakter newline (/n) dari input buffer
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl; 
    }
}

void updateLast(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node terakhir : " << endl;
        cout << "Nama makanan : ";
        getline(cin, List.last->isidata.nama);
        cout << "Jenis makanan : ";
        getline(cin, List.last->isidata.jenis);
        cout << "Harga : ";
        cin >> List.last->isidata.harga;
        cout << "Rating : ";
        cin >> List.last->isidata.rating;
        cin.ignore(); //menghapus karakter newline (/n) dari input buffer
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl; 
    }
}

void updateAfter(linkedlist List, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if(nodePrev != Nil && nodePrev->next != Nil){
            address nodeBantu = nodePrev->next;
            cout << "masukkan update data node setelah node " << nodePrev->isidata.nama << " : " << endl;
            cout << "Nama makanan : ";
            getline(cin, nodeBantu->isidata.nama);
            cout << "Jenis makanan : ";
            getline(cin, nodeBantu->isidata.jenis);
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Rating : ";
            cin >> nodeBantu->isidata.rating;
            cin.ignore(); //menghapus karakter newline (/n) dari input buffer
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (nodePrev) tidak valid!" << endl;
        }
    }
}

void updateBefore(linkedlist List, address nodeNext){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if (nodeNext != Nil && nodeNext->prev != Nil){
            address nodeBantu = nodeNext->prev;
            cout << "masukkan update data node sebelum node " << nodeNext->isidata.nama << " : " << endl;
            cout << "Nama makanan : ";
            getline(cin, nodeBantu->isidata.nama);
            cout << "Jenis makanan : ";
            getline(cin, nodeBantu->isidata.jenis);
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Rating : ";
            cin >> nodeBantu->isidata.rating;
            cin.ignore(); //menghapus karakter newline (/n) dari input buffer
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}
```

#### [main.cpp]
```C++
#include "listMakanan.h"
#include <iostream>

using namespace std;

int main(){
    linkedlist List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataMakanan dtMakanan;

    nodeA = alokasi("Nasi Rames", "Makanan Berat", 10000, 8.5);
    nodeB = alokasi("Ayam Geprek", "Makanan Berat", 13000, 9.0);
    nodeC = alokasi("Risol Mayo", "Makanan Ringan", 3500, 8.8);
    nodeD = alokasi("Mie Ayam", "Makanan Berat", 15000, 9.9);
    nodeE = alokasi("Donat", "Makanan Ringan", 2000, 7.7);

    insertFirst(List, nodeD);
    insertLast(List, nodeE);
    insertAfter(List, nodeA, nodeD);
    insertBefore(List, nodeC, nodeE);
    insertLast(List, nodeB);
    cout << endl;

    //D - A - C - E - B
    cout << "--- Isi List Setelah Insert ---" << endl;
    printList(List);
    cout << endl;

    updateFirst(List);
    updateLast(List);
    updateBefore(List, nodeC);
    updateAfter(List, nodeC);

    cout << "--- Isi List Setelah Update ---" << endl;
    printList(List);

    return 0;
}
```
Program ini mengimplementasikan struktur data double linked list untuk menyimpan, menampilkan, dan memperbarui data makanan. Setiap node dalam list berisi informasi berupa nama, jenis, harga, dan rating makanan. File listMakanan.h mendefinisikan struktur data dan deklarasi fungsi utama seperti insert, update, serta printList. Implementasi logika berada di listMakanan.cpp, di mana fungsi-fungsi tersebut diuraikan untuk menambah node di awal, akhir, sebelum, atau sesudah node tertentu, serta memperbarui isi node yang sudah ada. File main.cpp berfungsi sebagai program utama yang menginisialisasi list, membuat beberapa data makanan, menambahkannya ke dalam list, lalu menampilkan dan memperbarui data untuk menunjukkan cara kerja fungsi-fungsi yang telah dibuat. Program ini membantu memahami cara kerja linked list ganda (double linked list).

### 2. Program Manajemen Data Makanan Menggunakan Double Linked List dengan Operasi CRUD dan Pencarian
#### [listMakanan.h]
```C++
#ifndef LISTMAKANAN_H
#define LISTMAKANAN_H
#define Nil NULL

#include<iostream>
using namespace std;

struct makanan{
    string nama;
    string jenis; 
    float harga;
    float rating; 
};

typedef makanan dataMakanan;

typedef struct node *address;

struct node{
    dataMakanan isidata;
    address next;
    address prev;
};

struct linkedlist{
    address first;
    address last;
};

bool isEmpty(linkedlist List);
void createList(linkedlist &List);
address alokasi(string nama, string jenis, float harga, float rating);
void dealokasi(address &node);

void insertFirst(linkedlist &List, address nodeBaru);
void insertLast(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address Prev);
void insertBefore(linkedlist &List, address nodeBaru, address nodeNext);

void printList(linkedlist List);

void updateFirst(linkedlist List);
void updateLast(linkedlist List);
void updateAfter(linkedlist List, address prev);
void updateBefore(linkedlist List, address nodeNext);

// Searching
void findByName(linkedlist List, string nama);
void findByJenis(linkedlist List, string jenis);
void findByMinRating(linkedlist List, float minRating);

// Delete
void deleteFirst(linkedlist &List);
void deleteLast(linkedlist &List);
void deleteAfter(linkedlist &List, address Prev);
void deleteBefore(linkedlist &List, address nodeNext);

void deleteNode(linkedlist &List, address target);
void deleteByName(linkedlist &List, string nama);

#endif
```

#### [listMakanan.cpp]
```C++
#include "listMakanan.h"
#include <iostream>
#include <string>
using namespace std;

bool isEmpty(linkedlist List) {
    if(List.first == Nil){
        return true; 
    } else {
        return false;
    }
}

void createList(linkedlist &List) {
    List.first = Nil;
    List.last = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, string jenis, float harga, float rating) { 
    address nodeBaru = new node;
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.jenis = jenis; 
    nodeBaru->isidata.harga = harga;
    nodeBaru->isidata.rating =  rating;
    nodeBaru->next = Nil;
    nodeBaru->prev = Nil;
    return nodeBaru;
}

void dealokasi(address &node) {
    node->next = Nil;
    node->prev = Nil;
    delete node;
}

void insertFirst(linkedlist &List, address nodeBaru){
    if (isEmpty(List)) {
        List.first = List.last = nodeBaru;
    } else {
        nodeBaru->next = List.first;
        List.first->prev = nodeBaru;
        List.first = nodeBaru;
    }
    cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan sebagai node pertama list" << endl;
}

void insertLast(linkedlist &List, address nodeBaru){
    if(isEmpty(List) == true){
        List.first = List.last = nodeBaru;
    } else {
        nodeBaru->prev = List.last;
        List.last->next = nodeBaru;
        List.last = nodeBaru;
    }
    cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan sebagai node terakhir list" << endl;
}

void insertAfter(linkedlist &List, address nodeBaru, address nodePrev){
    if(isEmpty(List) == true){
        List.first = List.last = nodeBaru;
    } else {
        if (nodePrev != Nil){
            if(nodePrev == List.last){
                insertLast(List, nodeBaru);
            } else {
                nodeBaru->next = nodePrev->next;
                nodeBaru->prev = nodePrev;
                (nodePrev->next)->prev = nodeBaru;
                nodePrev->next = nodeBaru;
                cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan setelah node " << nodePrev->isidata.nama << endl;
            }
        } else {
            cout << "node sebelumnya (nodePrev) tidak valid!" << endl;
        }
    }
}

void insertBefore(linkedlist &List, address nodeBaru, address nodeNext){
    if(isEmpty(List) == true){
        List.first = List.last = nodeBaru;
    } else {
        if (nodeNext != Nil){
            if(nodeNext == List.first){
                insertFirst(List, nodeBaru);
            } else {
                nodeBaru->next = nodeNext;
                nodeBaru->prev = nodeNext->prev;
                (nodeNext->prev)->next = nodeBaru;
                nodeNext->prev = nodeBaru;
                cout << "Node " << nodeBaru->isidata.nama << " berhasil ditambahkan sebelum node " << nodeNext->isidata.nama << endl;
            }
        } else {
            cout << "node setelahnya (nodeNext) tidak valid!" << endl;
        }
    }
}

void printList(linkedlist List) {
    if (isEmpty(List) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama makanan : " << nodeBantu->isidata.nama << endl;
            cout << "Jenis        : " << nodeBantu->isidata.jenis << endl;
            cout << "Harga        : " << nodeBantu->isidata.harga << endl; 
            cout << "Rating       : " << nodeBantu->isidata.rating << endl;
            cout << "-------------------------------" << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

void updateFirst(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node pertama : " << endl;
        cout << "Nama makanan : ";
        getline(cin, List.first->isidata.nama);
        cout << "Jenis makanan : ";
        getline(cin, List.first->isidata.jenis);
        cout << "Harga : ";
        cin >> List.first->isidata.harga;
        cout << "Rating : ";
        cin >> List.first->isidata.rating;
        cin.ignore(); //menghapus karakter newline (/n) dari input buffer
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl; 
    }
}

void updateLast(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node terakhir : " << endl;
        cout << "Nama makanan : ";
        getline(cin, List.last->isidata.nama);
        cout << "Jenis makanan : ";
        getline(cin, List.last->isidata.jenis);
        cout << "Harga : ";
        cin >> List.last->isidata.harga;
        cout << "Rating : ";
        cin >> List.last->isidata.rating;
        cin.ignore(); //menghapus karakter newline (/n) dari input buffer
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl; 
    }
}

void updateAfter(linkedlist List, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if(nodePrev != Nil && nodePrev->next != Nil){
            address nodeBantu = nodePrev->next;
            cout << "masukkan update data node setelah node " << nodePrev->isidata.nama << " : " << endl;
            cout << "Nama makanan : ";
            getline(cin, nodeBantu->isidata.nama);
            cout << "Jenis makanan : ";
            getline(cin, nodeBantu->isidata.jenis);
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Rating : ";
            cin >> nodeBantu->isidata.rating;
            cin.ignore(); //menghapus karakter newline (/n) dari input buffer
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (nodePrev) tidak valid!" << endl;
        }
    }
}

void updateBefore(linkedlist List, address nodeNext){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if (nodeNext != Nil && nodeNext->prev != Nil){
            address nodeBantu = nodeNext->prev;
            cout << "masukkan update data node sebelum node " << nodeNext->isidata.nama << " : " << endl;
            cout << "Nama makanan : ";
            getline(cin, nodeBantu->isidata.nama);
            cout << "Jenis makanan : ";
            getline(cin, nodeBantu->isidata.jenis);
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Rating : ";
            cin >> nodeBantu->isidata.rating;
            cin.ignore(); //menghapus karakter newline (/n) dari input buffer
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

// SEARCHING
void findByName(linkedlist List, string nama){
    if(isEmpty(List)){
        cout << "List kosong!" << endl;
        return;
    }
    address p = List.first;
    while(p != Nil){
        if(p->isidata.nama == nama){
            cout << "Ditemukan (berdasarkan nama):" << endl;
            cout << "Nama makanan : " << p->isidata.nama << endl;
            cout << "Jenis        : " << p->isidata.jenis << endl;
            cout << "Harga        : " << p->isidata.harga << endl;
            cout << "Rating       : " << p->isidata.rating << endl;
            return;
        }
        p = p->next;
    }
    cout << "Data dengan nama \"" << nama << "\" tidak ditemukan." << endl;
}

void findByJenis(linkedlist List, string jenis){
    if(isEmpty(List)){
        cout << "List kosong!" << endl;
        return;
    }
    address p = List.first;
    while(p != Nil){
        if(p->isidata.jenis == jenis){
            cout << "Ditemukan (berdasarkan jenis):" << endl;
            cout << "Nama makanan : " << p->isidata.nama << endl;
            cout << "Jenis        : " << p->isidata.jenis << endl;
            cout << "Harga        : " << p->isidata.harga << endl;
            cout << "Rating       : " << p->isidata.rating << endl;
            return;
        }
        p = p->next;
    }
    cout << "Data dengan jenis \"" << jenis << "\" tidak ditemukan." << endl;
}

void findByMinRating(linkedlist List, float minRating){
    if(isEmpty(List)){
        cout << "List kosong!" << endl;
        return;
    }
    address p = List.first;
    while(p != Nil){
        if(p->isidata.rating >= minRating){
            cout << "Ditemukan (rating >= " << minRating << "):" << endl;
            cout << "Nama makanan : " << p->isidata.nama << endl;
            cout << "Jenis        : " << p->isidata.jenis << endl;
            cout << "Harga        : " << p->isidata.harga << endl;
            cout << "Rating       : " << p->isidata.rating << endl;
            return;
        }
        p = p->next;
    }
    cout << "Tidak ada data dengan rating >= " << minRating << "." << endl;
}

// DELETE
void deleteFirst(linkedlist &List){
    if(isEmpty(List) == true){
        cout << "List kosong! Tidak ada node yang dihapus." << endl;
        return;
    }
    address pDel = List.first;
    if(List.first == List.last){
        List.first = List.last = Nil;
    } else {
        List.first = pDel->next;
        List.first->prev = Nil;
        pDel->next = Nil;
    }
    pDel->prev = Nil;
    cout << "Node " << pDel->isidata.nama << " berhasil dihapus dari posisi pertama." << endl;
    dealokasi(pDel);
}

void deleteLast(linkedlist &List){
    if(isEmpty(List) == true){
        cout << "List kosong! Tidak ada node yang dihapus." << endl;
        return;
    }
    address pDel = List.last;
    if(List.first == List.last){
        List.first = List.last = Nil;
    } else {
        List.last = pDel->prev;
        List.last->next = Nil;
        pDel->prev = Nil;
    }
    pDel->next = Nil;
    cout << "Node " << pDel->isidata.nama << " berhasil dihapus dari posisi terakhir." << endl;
    dealokasi(pDel);
}

void deleteAfter(linkedlist &List, address Prev){
    if(isEmpty(List) == true){
        cout << "List kosong! Tidak ada node yang dihapus." << endl;
        return;
    }
    if(Prev == Nil || Prev->next == Nil){
        cout << "Node sebelumnya (Prev) tidak valid atau tidak ada node setelahnya!" << endl;
        return;
    }
    if(Prev->next == List.last){
        deleteLast(List);
        return;
    }
    address pDel = Prev->next;
    Prev->next = pDel->next;
    pDel->next->prev = Prev;
    pDel->next = Nil;
    pDel->prev = Nil;
    cout << "Node " << pDel->isidata.nama << " berhasil dihapus setelah node " << Prev->isidata.nama << "." << endl;
    dealokasi(pDel);
}

void deleteBefore(linkedlist &List, address nodeNext){
    if(isEmpty(List) == true){
        cout << "List kosong! Tidak ada node yang dihapus." << endl;
        return;
    }
    if(nodeNext == Nil || nodeNext->prev == Nil){
        cout << "Node setelahnya (nodeNext) tidak valid atau tidak ada node sebelumnya!" << endl;
        return;
    }
    if(nodeNext->prev == List.first){
        deleteFirst(List);
        return;
    }
    address pDel = nodeNext->prev;
    nodeNext->prev = pDel->prev;
    pDel->prev->next = nodeNext;
    pDel->next = Nil;
    pDel->prev = Nil;
    cout << "Node " << pDel->isidata.nama << " berhasil dihapus sebelum node " << nodeNext->isidata.nama << "." << endl;
    dealokasi(pDel);
}

void deleteNode(linkedlist &List, address target){
    if(isEmpty(List) == true || target == Nil){
        cout << "Target tidak valid atau list kosong!" << endl;
        return;
    }
    if(target == List.first){
        deleteFirst(List);
    } else if(target == List.last){
        deleteLast(List);
    } else {
        address L = target->prev;
        address R = target->next;
        L->next = R;
        R->prev = L;
        target->next = Nil;
        target->prev = Nil;
        cout << "Node " << target->isidata.nama << " berhasil dihapus dari tengah list." << endl;
        dealokasi(target);
    }
}

void deleteByName(linkedlist &List, string nama){
    if(isEmpty(List)){
        cout << "List kosong! Tidak ada node yang dihapus." << endl;
        return;
    }

    address target = List.first;
    while(target != Nil && target->isidata.nama != nama){
        target = target->next;
    }
    if(target == Nil){
        cout << "Node dengan nama \"" << nama << "\" tidak ditemukan." << endl;
        return;
    }

    deleteNode(List, target);
    cout << "Node dengan nama \"" << nama << "\" telah dihapus dan didealokasi." << endl;
}
```

#### [main.cpp]
```C++
	#include "listMakanan.h"
#include <iostream>

using namespace std;

int main(){
    linkedlist List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataMakanan dtMakanan;

    nodeA = alokasi("Nasi Rames", "Makanan Berat", 10000, 8.5);
    nodeB = alokasi("Ayam Geprek", "Makanan Berat", 13000, 9.0);
    nodeC = alokasi("Risol Mayo", "Makanan Ringan", 3500, 8.8);
    nodeD = alokasi("Mie Ayam", "Makanan Berat", 15000, 9.9);
    nodeE = alokasi("Donat", "Makanan Ringan", 2000, 7.7);

    insertFirst(List, nodeD);
    insertLast(List, nodeE);
    insertAfter(List, nodeA, nodeD);
    insertBefore(List, nodeC, nodeE);
    insertLast(List, nodeB);
    cout << endl;

    //D - A - C - E - B
    cout << "--- Isi List Setelah Insert ---" << endl;
    printList(List);
    cout << endl;

    updateFirst(List);
    updateLast(List);
    updateBefore(List, nodeC);
    updateAfter(List, nodeA);

    cout << "--- Isi List Setelah Update ---" << endl;
    printList(List);

    cout << endl;

    findByName(List, "Nasgor");

    deleteByName(List, "Nasgor");
    deleteFirst(List);
    deleteBefore(List, nodeE);

    cout << endl << "--- Isi List Setelah Delete ---" << endl;
    printList(List);

    return 0;
}
```
Program ini merupakan implementasi lengkap struktur data Double Linked List  untuk mengelola data makanan secara dinamis. Setiap node menyimpan informasi berupa nama, jenis, harga, dan rating makanan. File listMakanan.h berisi deklarasi struktur dan fungsi-fungsi utama seperti pembuatan list, penambahan (insert), pembaruan (update), pencarian (search), serta penghapusan data (delete). Implementasinya terdapat pada listMakanan.cpp, yang menangani seluruh logika manajemen memori, manipulasi node di awal, tengah, atau akhir list, hingga pencarian berdasarkan nama, jenis, dan rating minimal. Sementara itu, main.cpp berfungsi sebagai program utama untuk membuat beberapa data makanan, menambahkannya ke list, melakukan pembaruan, pencarian, dan penghapusan data. Secara keseluruhan, program ini menggambarkan bagaimana struktur double linked list dapat digunakan untuk mengelola kumpulan data secara fleksibel dan efisien.

## Unguided 

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan6_modul6/unguided1-modul6.png)

#### [doublylist.h]
```C++
#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include <string>
using namespace std;

struct kendaraan {
    string nomorPolisi;
    string warna;
    int tahunBuat;
};

using infotype = kendaraan;

typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
    address prev;
};

struct List {
    address First;
    address Last;
};

void CreateList(List &L);
address alokasi(const string &nomorPolisi, const string &warna, int tahunBuat);
void dealokasi(address &P);
void printInfo(const List &L);
void insertLast(List &L, address P);
void insertFirst(List &L, address P);
address findByNomorPolisi(const List &L, const string &nomorPolisi);

#endif
```

#### [doublylist.cpp]
```C++
#include "doublylist.h"
#include <iostream>
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
    L.Last = nullptr;
}

address alokasi(const string &nomorPolisi, const string &warna, int tahunBuat) {
    address P = new ElmList;
    if (P != nullptr) {
        P->info.nomorPolisi = nomorPolisi;
        P->info.warna = warna;
        P->info.tahunBuat = tahunBuat;
        P->next = nullptr;
        P->prev = nullptr;
    }
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void insertFirst(List &L, address P) {
    if (P == nullptr) return;
    if (L.First == nullptr) {
        L.First = L.Last = P;
    } else {
        P->next = L.First;
        L.First->prev = P;
        L.First = P;
    }
}

void insertLast(List &L, address P) {
    if (P == nullptr) return;
    if (L.First == nullptr) {
        L.First = L.Last = P;
    } else {
        L.Last->next = P;
        P->prev = L.Last;
        L.Last = P;
    }
}

address findByNomorPolisi(const List &L, const string &nomorPolisi) {
    address P = L.First;
    while (P != nullptr) {
        if (P->info.nomorPolisi == nomorPolisi) return P;
        P = P->next;
    }
    return nullptr;
}

void printInfo(const List &L) {
    cout << "\nDATA LIST 1" << endl << endl;
    address P = L.Last;
    while (P != nullptr) {
        cout << "nomor polisi : " << P->info.nomorPolisi << endl;
        cout << "warna        : " << P->info.warna << endl;
        cout << "tahun        : " << P->info.tahunBuat << endl << endl;
        P = P->prev;
    }
}
```

#### [main.cpp]
```C++
#include "doublylist.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    CreateList(L);

    for (int i = 0; i < 4; ++i) {
        string nomorPolisi, warna;
        int tahunBuat;
        cout << "masukkan nomor polisi: ";
        getline(cin, nomorPolisi);
        if (nomorPolisi.empty()) {
            --i;
            continue;
        }
        cout << "masukkan warna kendaraan: ";
        getline(cin, warna);
        cout << "masukkan tahun kendaraan: ";
        string line;
        getline(cin, line);
        try {
            tahunBuat = stoi(line);
        } catch (...) {
            tahunBuat = 0;
        }

        if (findByNomorPolisi(L, nomorPolisi) != nullptr) {
            cout << "nomor polisi sudah terdaftar" << endl << endl;
            continue; 
        }

        address node = alokasi(nomorPolisi, warna, tahunBuat);
        insertLast(L, node);
    }

    printInfo(L);

    address P = L.First;
    while (P != nullptr) {
        address next = P->next;
        dealokasi(P);
        P = next;
    }

    return 0;
}
```

### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan6_modul6/output1-unguided1-modul6.png)

Program ini mengimplementasikan struktur data double linked list untuk menyimpan dan menampilkan data kendaraan secara dinamis. Setiap node dalam list berisi informasi berupa nomor polisi, warna, dan tahun pembuatan kendaraan. File doublylist.h mendefinisikan struktur data dan deklarasi fungsi seperti pembuatan list, alokasi, penambahan data di awal dan akhir list, pencarian berdasarkan nomor polisi, serta penghapusan memori. Implementasinya terdapat di doublylist.cpp, yang mengatur logika pengelolaan node dua arah (maju dan mundur). File main.cpp berfungsi sebagai program utama untuk menerima input data kendaraan dari pengguna, memastikan nomor polisi tidak duplikat, menambahkannya ke list, lalu menampilkan seluruh data kendaraan. Program ini memperlihatkan bagaimana double linked list dapat digunakan untuk pengelolaan data yang efisien dan fleksibel.

### 2. ![Screenshot Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan6_modul6/unguided2-modul6.png)

#### [doublylist.h]
```C++
#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include <string>
using namespace std;

struct kendaraan {
	string nomorPolisi;
	string warna;
	int tahunBuat;
};

using infotype = kendaraan;

typedef struct ElmList *address;

struct ElmList {
	infotype info;
	address next;
	address prev;
};

struct List {
	address First;
	address Last;
};

void CreateList(List &L);
address alokasi(const string &nomorPolisi, const string &warna, int tahunBuat);
void dealokasi(address &P);
void printInfo(const List &L);
void insertLast(List &L, address P);
void insertFirst(List &L, address P);
address findByNomorPolisi(const List &L, const string &nomorPolisi);

#endif
```

#### [doublylist.cpp]
```C++
#include "doublylist.h"
#include <iostream>
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
    L.Last = nullptr;
}

address alokasi(const string &nomorPolisi, const string &warna, int tahunBuat) {
    address P = new ElmList;
    if (P != nullptr) {
        P->info.nomorPolisi = nomorPolisi;
        P->info.warna = warna;
        P->info.tahunBuat = tahunBuat;
        P->next = nullptr;
        P->prev = nullptr;
    }
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void insertFirst(List &L, address P) {
    if (P == nullptr) return;
    if (L.First == nullptr) {
        L.First = L.Last = P;
    } else {
        P->next = L.First;
        L.First->prev = P;
        L.First = P;
    }
}

void insertLast(List &L, address P) {
    if (P == nullptr) return;
    if (L.First == nullptr) {
        L.First = L.Last = P;
    } else {
        L.Last->next = P;
        P->prev = L.Last;
        L.Last = P;
    }
}

address findByNomorPolisi(const List &L, const string &nomorPolisi) {
    address P = L.First;
    while (P != nullptr) {
        if (P->info.nomorPolisi == nomorPolisi) return P;
        P = P->next;
    }
    return nullptr;
}

void printInfo(const List &L) {
    cout << "\nDATA LIST 1" << endl << endl;
    address P = L.Last;
    while (P != nullptr) {
        cout << "nomor polisi : " << P->info.nomorPolisi << endl;
        cout << "warna        : " << P->info.warna << endl;
        cout << "tahun        : " << P->info.tahunBuat << endl << endl;
        P = P->prev;
    }
}
```

#### [main.cpp]
```C++
#include "doublylist.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    CreateList(L);

    for (int i = 0; i < 4; ++i) {
        string nomorPolisi, warna;
        int tahunBuat;
        cout << "masukkan nomor polisi: ";
        getline(cin, nomorPolisi);
        if (nomorPolisi.empty()) {
            --i;
            continue;
        }
        cout << "masukkan warna kendaraan: ";
        getline(cin, warna);
        cout << "masukkan tahun kendaraan: ";
        string line;
        getline(cin, line);
        try {
            tahunBuat = stoi(line);
        } catch (...) {
            tahunBuat = 0;
        }

        if (findByNomorPolisi(L, nomorPolisi) != nullptr) {
            cout << "nomor polisi sudah terdaftar" << endl << endl;
            continue; 
        }

        address node = alokasi(nomorPolisi, warna, tahunBuat);
        insertLast(L, node);
    }

    printInfo(L);

    cout << "Masukkan Nomor Polisi yang dicari  : ";
    string cari;
    getline(cin, cari);

    address found = findByNomorPolisi(L, cari);
    if (found != nullptr) {
        cout << endl;
        cout << "Nomor Polisi : " << found->info.nomorPolisi << endl;
        cout << "Warna        : " << found->info.warna << endl;
        cout << "Tahun        : " << found->info.tahunBuat << endl;
    } else {
        cout << "Data dengan nomor polisi '" << cari << "' tidak ditemukan." << endl;
    }

    address P = L.First;
    while (P != nullptr) {
        address next = P->next;
        dealokasi(P);
        P = next;
    }

    return 0;
}
```

### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan6_modul6/output1-unguided2-modul6.png)

Program ini mengimplementasikan struktur data double linked list untuk menyimpan, menampilkan, dan mencari data kendaraan secara dinamis. Setiap elemen (node) menyimpan informasi tentang nomor polisi, warna, dan tahun pembuatan kendaraan, yang dihubungkan dua arah menggunakan pointer next dan prev. File doublylist.h mendefinisikan struktur data dan deklarasi fungsi utama seperti pembuatan list, alokasi node baru, penambahan data di awal atau akhir list, pencarian berdasarkan nomor polisi, dan penghapusan memori. Implementasi logika terdapat di doublylist.cpp, sedangkan main.cpp berfungsi sebagai program utama untuk menerima input dari pengguna, menambahkan data kendaraan ke dalam list tanpa duplikasi nomor polisi, menampilkan seluruh data dari belakang ke depan, serta melakukan pencarian data kendaraan berdasarkan nomor polisi tertentu. Program ini memperlihatkan penerapan double linked list untuk pengelolaan data yang efisien, fleksibel, dan terstruktur.

### 3. ![Screenshot Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan6_modul6/unguided3-modul6.png)

#### [doublylist.h]
```C++
#ifndef DOUBLYLIST_H
#define DOUBLYLIST_H

#include <iostream>
#include <string>
using namespace std;

struct kendaraan {
	string nomorPolisi;
	string warna;
	int tahunBuat;
};

using infotype = kendaraan;

typedef struct ElmList *address;

struct ElmList {
	infotype info;
	address next;
	address prev;
};

struct List {
	address First;
	address Last;
};

void CreateList(List &L);
address alokasi(const string &nomorPolisi, const string &warna, int tahunBuat);
void dealokasi(address &P);
void printInfo(const List &L);
void insertLast(List &L, address P);
void insertFirst(List &L, address P);
address findByNomorPolisi(const List &L, const string &nomorPolisi);

#endif
```
#### [doublylist.cpp]
```C++
#include "doublylist.h"
#include <iostream>
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
    L.Last = nullptr;
}

address alokasi(const string &nomorPolisi, const string &warna, int tahunBuat) {
    address P = new ElmList;
    if (P != nullptr) {
        P->info.nomorPolisi = nomorPolisi;
        P->info.warna = warna;
        P->info.tahunBuat = tahunBuat;
        P->next = nullptr;
        P->prev = nullptr;
    }
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void insertFirst(List &L, address P) {
    if (P == nullptr) return;
    if (L.First == nullptr) {
        L.First = L.Last = P;
    } else {
        P->next = L.First;
        L.First->prev = P;
        L.First = P;
    }
}

void insertLast(List &L, address P) {
    if (P == nullptr) return;
    if (L.First == nullptr) {
        L.First = L.Last = P;
    } else {
        L.Last->next = P;
        P->prev = L.Last;
        L.Last = P;
    }
}

address findByNomorPolisi(const List &L, const string &nomorPolisi) {
    address P = L.First;
    while (P != nullptr) {
        if (P->info.nomorPolisi == nomorPolisi) return P;
        P = P->next;
    }
    return nullptr;
}

void printInfo(const List &L) {
    cout << "\nDATA LIST 1" << endl << endl;
    address P = L.Last;
    while (P != nullptr) {
        cout << "Nomor Polisi : " << P->info.nomorPolisi << endl;
        cout << "Warna        : " << P->info.warna << endl;
        cout << "Tahun        : " << P->info.tahunBuat << endl << endl;
        P = P->prev;
    }
}
```
#### [main.cpp]
```C++
#include "doublylist.h"
#include <iostream>
using namespace std;

void deleteFirst(List &L) {
    if (L.First == nullptr) return;
    address P = L.First;
    if (L.First == L.Last) {
        L.First = L.Last = nullptr;
    } else {
        L.First = P->next;
        L.First->prev = nullptr;
    }
    dealokasi(P);
}

void deleteLast(List &L) {
    if (L.Last == nullptr) return;
    address P = L.Last;
    if (L.First == L.Last) {
        L.First = L.Last = nullptr;
    } else {
        L.Last = P->prev;
        L.Last->next = nullptr;
    }
    dealokasi(P);
}

void deleteAfter(List &L, address Prec) {
    if (Prec == nullptr || Prec->next == nullptr) return;
    address P = Prec->next;
    Prec->next = P->next;
    if (P->next != nullptr) P->next->prev = Prec;
    if (P == L.Last) L.Last = Prec;
    dealokasi(P);
}

int main() {
    List L;
    CreateList(L);

    insertLast(L, alokasi("D001", "hitam", 90));
    insertLast(L, alokasi("D004", "kuning", 90));

    cout << "Masukkan Nomor Polisi yang akan dihapus  : ";
    string target;
    getline(cin, target);

    address node = findByNomorPolisi(L, target);
    if (node == nullptr) {
        cout << "Data dengan nomor polisi " << target << " tidak ditemukan." << endl;
    } else {
        if (node == L.First) {
            deleteFirst(L);
        } else if (node == L.Last) {
            deleteLast(L);
        } else {
            deleteAfter(L, node->prev);
        }
        cout << "Data dengan nomor polisi " << target << " berhasil dihapus." << endl;
    }

    cout << "\nDATA LIST 1" << endl << endl;
    address P = L.Last;
    while (P != nullptr) {
        cout << "Nomor Polisi : " << P->info.nomorPolisi << endl;
        cout << "Warna        : " << P->info.warna << endl;
        cout << "Tahun        : " << P->info.tahunBuat << endl;
        if (P->prev != nullptr) cout << "\n";
        P = P->prev;
    }

    P = L.First;
    while (P != nullptr) {
        address next = P->next;
        dealokasi(P);
        P = next;
    }

    return 0;
}
```

### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan6_modul6/output1-unguided3-modul6.png)

Program ini merupakan implementasi struktur data Double Linked List untuk menyimpan dan menghapus data kendaraan secara dinamis. Setiap node menyimpan informasi kendaraan berupa nomor polisi, warna, dan tahun pembuatan, serta dihubungkan dua arah menggunakan pointer next dan prev. File doublylist.h berisi deklarasi struktur dan fungsi dasar seperti pembuatan list, alokasi node, penambahan elemen, pencarian data, dan pencetakan isi list. File doublylist.cpp mengimplementasikan logika dasar operasi tersebut. Sementara itu, main.cpp berfokus pada operasi penghapusan data, yang mencakup penghapusan node pertama, terakhir, dan di tengah list berdasarkan nomor polisi yang dimasukkan pengguna. Program ini menggambarkan cara kerja manipulasi node dua arah untuk mengelola dan menghapus data secara efisien dalam struktur Double Linked List.

## Kesimpulan
Doubly Linked List merupakan struktur data yang menawarkan fleksibilitas tinggi melalui dua pointer (next dan previous). Hal ini memungkinkan traversal dua arah dan operasi insert/delete yang efisien.

Walaupun memerlukan memori lebih besar dan manajemen pointer yang lebih kompleks, DLL tetap relevan dalam berbagai aplikasi modern yang membutuhkan manipulasi data dinamis, seperti sistem simulasi, pengolahan teks, dan aplikasi multithreaded.
Dalam konteks implementasi dengan bahasa Go, DLL dapat digunakan untuk mengelola histori atau daftar transaksi dinamis dalam simulasi pasar saham virtual, dengan pertimbangan efisiensi terhadap kebutuhan traversal bolak-balik.

## Referensi
[1]Sundell, Håkan, and Philippas Tsigas. “Lock-Free Deques and Doubly Linked Lists.” Journal of Parallel and Distributed Computing, vol. 68, no. 10, Oct 2008, pp. 1429–1440.

<br>[2]Khan, Adnan, et al. “Skeleton Based Human Action Recognition Using Doubly Linked List.” International Journal of Computer Trends and Technology (IJCTT), vol. 70, no. 2, 2022, pp. 43–47.

<br>[3]Prasad, S., Sharma, A., and Kumar, V. “Comparative Analysis of Singly and Doubly Linked Lists in Terms of Time and Space Complexity.” International Journal of Advanced Computer Science and Applications, vol. 11, no. 5, May 2020, pp. 120–126.

<br>[4]Alghamdi, H. “A Memory-Efficient Doubly Linked List Implementation.” Linux Journal, no. 118, Jun 2003, pp. 1–8.

<br>[5]Bhatnagar, Sarvesh Rakesh. “Speeding Up Search in Singly Linked List.” International Journal of Computer Applications, vol. 182, no. 18, Sep 2018, pp. 19–24.

<br>[6]Wikipedia Contributors. “Doubly Linked List.” Wikipedia, The Free Encyclopedia, 2024, https://en.wikipedia.org/wiki/Doubly_linked_list