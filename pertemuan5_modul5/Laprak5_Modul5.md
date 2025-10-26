# <h1 align="center">Laporan Praktikum Modul 5 - SINGLY LINKED LIST (BAGIAN KEDUA) </h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
Singly linked list adalah sebuah struktur data linear di mana setiap elemen (node) berisi dua bagian utama:

- data (atau nilai)
- sebuah pointer/link ke node berikutnya

Dengan demikian, setiap node menunjuk ke node “selanjutnya” dalam urutan, dan node terakhir menunjuk ke NULL (atau tidak mempunyai link ke node berikutnya)[1]. Karena tidak memerlukan blok memori yang berurutan (contiguous) seperti array, linked list bisa secara dinamis menambah atau menghapus elemen (node) dengan lebih fleksibel[2].

### Karakteristik utama

- Setiap node mempunyai link ke node selanjutnya saja (tidak ke node sebelumnya) → satu arah traversal.
- Tidak perlu ukuran (size) didefinisikan sebelumnya; pertumbuhan (growth) bersifat dinamis selama runtime.
- Elemen-elemen tidak harus berada secara berurutan dalam memori; pointer yang menghubungkan antar-node lah yang menyusun struktur.

### A. Operasi Dasar <br/>
Berikut beberapa operasi dasar yang umum dilakukan pada SLL:
#### 1. Traversal (pengaksesan semua node)
Dimulai dari head, kemudian ikuti pointer next dari satu node ke node selanjutnya hingga next == NULL.

#### 2. Insertion (penyisipan node)
Beberapa lokasi penyisipan umum: di awal list, di akhir list, atau di antara dua node.

- Penyisipan di awal list sangat cepat (O(1)), karena hanya perlu membuat node baru dan mengubah head. 
- Penyisipan di akhir (jika hanya punya pointer head, dan tidak punya tail) bisa O(n), sebab perlu traversing hingga akhir.
- Penyisipan setelah node tertentu juga bisa O(1) jika pointer ke node tersebut sudah diketahui.

#### 3. Deletion (penghapusan node)
- Penghapusan di awal sangat cepat (O(1)).
- Penghapusan di tengah/akhir membutuhkan pointer ke node sebelumnya (untuk mengubah next) dan kadang traversing O(n).
- Karena hanya link ke “next”, maka penghapusan node yang diketahui (tanpa pointer ke node sebelumnya) agak sulit langsung tanpa traversing.

#### 4. Pencarian (search)
Untuk mencari elemen dengan nilai tertentu, harus traversing dari head hingga ditemukan atau mencapai akhir → O(n). Ada penelitian yang mencoba mempercepat pencarian pada SLL misalnya dengan indeks tambahan. Contoh: Speeding Up Search in Singly Linked List oleh Bhatnagar (2018) yang mengusulkan indexing-lane tambahan untuk mempercepat pencarian di SLL.

#### 5. Kompleksitas ruang dan waktu
- Akses elemen: O(n) waktu. 
- Insert di awal: O(1) waktu.
- Delete di awal: O(1) waktu.
- Insert/Delete di akhir/tengah: O(n) kalau pointer ke lokasi sebelumnya tidak disimpan.
- Ruang tambahan: pointer next untuk setiap node (overhead dibanding array).

### B. Kelebihan dan Kekurangan<br/>
#### Kelebihan
- Memori dinamis: ukuran list bisa bertambah atau berkurang sesuai kebutuhan runtime. 
- Pemakaian memori tidak harus berurutan: cocok untuk alokasi yang tersebar.
- Operasi penyisipan/penghapusan di awal atau saat pointer sudah diketahui bisa sangat efisien (O(1)).

#### Kekurangan
- Akses acak (random access) sulit/impossible secara langsung: harus traversing dari head untuk mencapai node ke-k. 
- Overhead pointer: tiap node perlu menyimpan link ke node selanjutnya → penggunaan memori sedikit lebih besar dibanding struktur yang hanya menyimpan data. 
- Traversal satu arah saja: tidak bisa mundur (backwards) kecuali disimpan pointer tambahan (yang membuat jadi doubly linked list). 
- Untuk akses ke akhir list secara cepat atau penghapusan di tengah tanpa pointer ke node sebelumnya, bisa jadi tidak efisien.

### C. Aplikasi dan Varian <br/>
- SLL sering digunakan sebagai dasar untuk struktur data lain seperti stack, queue, grafik, dll. 
- SLL juga digunakan dalam bahasa pemrograman fungsional sebagai list “cons” (contoh: Lisp) karena kemudahan alokasi dinamis dan berbagi struktur. 
- Varian-nya antara lain: doubly linked list (link ke next & prev), circular linked list (node terakhir menunjuk ke head), dan lainnya. 
- Beberapa penelitian lanjut juga melihat SLL dalam konteks analisis heap, verifikasi program, concurrent data structures, misalnya:
    - Quantified Data Automata on Skinny Trees (2013) yang membahas abstraksi domain untuk linked list dalam analisis heap.
    - Distributing Context‑Aware Shared Memory Data Structures: A Case Study on Singly‑Linked Lists (2024) yang membahas transformasi SLL ke distributed context-aware data structure.

## Guided 

### 1. Program Implementasi Singly Linked List untuk Data Buah
#### [listBuah.h]
```C++
//Header guard digunakan untuk mencegah file header yang sama 
//di-include lebih dari sekali dalam satu program.
#ifndef LISTBUAH_H
#define LISTBUAH_H
#define Nil NULL

#include<iostream>
using namespace std;

struct buah{
    string nama;
    int jumlah; 
    float harga;
};

typedef buah dataBuah; //Memberikan nama alias databuah untuk struct buah.

typedef struct node *address; //Mendefinisikan alias address sebagai pointer ke struct node

struct node{ // node untuk isi dari linked listnya, isi setiap node adalah data & pointer next
    dataBuah isidata;
    address next;
};

struct linkedlist{ //ini linked list nya
    address first;
};

//semua function & prosedur yang akan dipakai
//Materi modul 4
bool isEmpty(linkedlist List);
void createList(linkedlist &List);
address alokasi(string nama, int jumlah, float harga);
void dealokasi(address &node);
void printList(linkedlist List);
void insertFirst(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address Prev);
void insertLast(linkedlist &List, address nodeBaru);
void delFirst(linkedlist &List);
void delLast(linkedlist &List);
void delAfter(linkedlist &List, address nodeHapus, address nodePrev);
int nbList(linkedlist List);
void deleteList(linkedlist &List);

//materi modul 5 (part 1 - update)
void updateFirst(linkedlist List);
void updateLast(linkedlist List);
void updateAfter(linkedlist List, address prev);

//materi modul 5 (part 2 - searching)
void FindNodeByData(linkedlist list, string data);
void FindNodeByAddress(linkedlist list, address node);
void FindNodeByRange(linkedlist list, float hargaAwal, float HargaAkhir);

#endif
```

#### [listBuah.cpp]
```C++
#include "listBuah.h"
#include <iostream>
using namespace std;

//fungsi untuk cek apakah list kosong atau tidak
bool isEmpty(linkedlist List) {
    if(List.first == Nil){
        return true; 
    } else {
        return false;
    }
}

//pembuatan linked list kosong
void createList(linkedlist &List) {
    List.first = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, int jumlah, float harga) { 
    address nodeBaru = new node; 
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.jumlah = jumlah; 
    nodeBaru->isidata.harga = harga;
    nodeBaru->next = Nil;
    return nodeBaru;
}

//penghapusan node dengan menerapkan manajemen memori
void dealokasi(address &node) {
    node->next = Nil;
    delete node;
}

//prosedur-prosedur untuk insert / menambahkan node baru kedalam list
void insertFirst(linkedlist &List, address nodeBaru) {
    nodeBaru->next = List.first; 
    List.first = nodeBaru;
}

void insertAfter(linkedlist &List, address nodeBaru, address Prev) {
    if (Prev != Nil) {
        nodeBaru->next = Prev->next;
        Prev->next = nodeBaru;
    } else {
        cout << "Node sebelumnya tidak valid!" << endl;
    }
}

void insertLast(linkedlist &List, address nodeBaru) {
    if (isEmpty(List)) {
        List.first = nodeBaru;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        nodeBantu->next = nodeBaru;
    }
}

//prosedur-prosedur untuk delete / menghapus node yang ada didalam list
void delFirst(linkedlist &List){
    address nodeHapus;
    if (isEmpty(List) == false) {
        nodeHapus = List.first;
        List.first = List.first->next;
        nodeHapus->next = Nil;
        dealokasi(nodeHapus);
        cout << "Node pertama berhasil terhapus!" << endl;
    } else {
        cout << "List kosong!" << endl;
    }
}

void delLast(linkedlist &List){
    address nodeHapus, nodePrev;
    if(isEmpty(List) == false){
        nodeHapus = List.first;
        if(nodeHapus->next == Nil){
            List.first->next = Nil;
            dealokasi(nodeHapus);
        } else { 
            while(nodeHapus->next != Nil){
                nodePrev = nodeHapus; 
                nodeHapus = nodeHapus->next;
            }
            nodePrev->next = Nil; 
            dealokasi(nodeHapus);
        }
        cout << "Node terakhir berhasil terhapus!" << endl;
    } else {
        cout << "list kosong" << endl;
    }
}

void delAfter(linkedlist &List, address nodeHapus, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else { //jika list tidak kosong
        if (nodePrev != Nil && nodePrev->next != Nil) { 
            nodeHapus = nodePrev->next;       
            nodePrev->next = nodeHapus->next;  
            nodeHapus->next = Nil;         
            dealokasi(nodeHapus);
            cout << "Node setelah node " << nodePrev->isidata.nama << " berhasil terhapus!" << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

//prosedur untuk menampilkan isi list
void printList(linkedlist List) {
    if (isEmpty(List)) {
        cout << "List kosong." << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

//function untuk menampilkan jumlah node didalam list
int nbList(linkedlist List) {
    int count = 0;
    address nodeBantu = List.first;
    while (nodeBantu != Nil) {
        count++;
        nodeBantu = nodeBantu->next; 
    }
    return count;
}

//prosedur untuk menghapus list (menghapus semua node didalam list)
void deleteList(linkedlist &List){
    address nodeBantu, nodeHapus;
    nodeBantu = List.first;
    while(nodeBantu != Nil){
        nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        dealokasi(nodeHapus); 
    }
    List.first = Nil; 
    cout << "List berhasil terhapus!" << endl;
}

/*----- MATERI PERTEMUAN 5 - SINGLY LINKED LIST (BAGIAN KEDUA) - PART 1 (UPDATE) -----*/
//prosedur-prosedur untuk melakukan update data node
void updateFirst(linkedlist List){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        cout << "Masukkan update data node pertama : " << endl;
        cout << "Nama buah : ";
        cin >> List.first->isidata.nama;
        cout << "Jumlah : ";
        cin >> List.first->isidata.jumlah;
        cout << "Harga : ";
        cin >> List.first->isidata.harga;
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl;
    }
}

void updateLast(linkedlist List){
    if (isEmpty(List) == true) {
        cout << "List Kosong!" << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu->next != Nil) {
            nodeBantu = nodeBantu->next;
        }
        cout << "masukkan update data node terakhir : " << endl;
        cout << "Nama buah : ";
        cin >> nodeBantu->isidata.nama;
        cout << "Jumlah : ";
        cin >> nodeBantu->isidata.jumlah;
        cout << "Harga : ";
        cin >> nodeBantu->isidata.harga;
        cout << "Data Berhasil Diupdate!" << endl;
        cout << endl;
    }
}

void updateAfter(linkedlist List, address nodePrev){
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else {
        if (nodePrev != Nil && nodePrev->next != Nil){
            address nodeBantu = nodePrev->next;
            cout << "masukkan update data node setelah node " << nodePrev->isidata.nama << " : " << endl;
            cout << "Nama buah : ";
            cin >> nodeBantu->isidata.nama;
            cout << "Jumlah : ";
            cin >> nodeBantu->isidata.jumlah;
            cout << "Harga : ";
            cin >> nodeBantu->isidata.harga;
            cout << "Data Berhasil Diupdate!" << endl;
            cout << endl;
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

/*----- MATERI PERTEMUAN 5 - SINGLY LINKED LIST (BAGIAN KEDUA) - PART 2 (SEARCHING) -----*/
//prosedur-prosedur untuk searching data
//prosedur untuk mencari node berdasarkan data
void FindNodeByData(linkedlist list, string data){
    if(isEmpty(list) == true){
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        while(nodeBantu != Nil){
            posisi++;
            if(nodeBantu->isidata.nama == data){
                cout << "Data " << data << " ditemukan pada posisi ke-" << posisi << "!" << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                found = true;
                break;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false){
            cout << "Node dengan data " << data << " tidak ditemukan!" << endl;
        }
    }
    cout << endl;
}

//prosedur untuk mencari node berdasarkan alamat node
void FindNodeByAddress(linkedlist list, address node) {
    if(isEmpty(list) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        while (nodeBantu != Nil) {
            posisi++;
            if(nodeBantu == node) {
                cout << "Node ditemukan pada posisi ke-" << posisi << "!" << endl;
                cout << "Alamat node : " << nodeBantu << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                found = true;
                break;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false) {
            cout << "Node dengan alamat " << node << " tidak ditemukan dalam list!" << endl;
        }
    }
    cout << endl;
}

//prosedur untuk mencari node berdasarkan range data (range harga)
void FindNodeByRange(linkedlist list, float hargaAwal, float hargaAkhir) {
    if(isEmpty(list) == true) {
        cout << "List kosong!" << endl;
    } else {
        address nodeBantu = list.first;
        int posisi = 0;
        bool found = false;
        cout << "--- Buah dalam range harga " << hargaAwal << " - " << hargaAkhir << " ---" << endl;
        cout << "-------------------------------------------" << endl;
        while (nodeBantu != Nil) {
            posisi++;
            float harga = nodeBantu->isidata.harga;
            if(harga >= hargaAwal && harga <= hargaAkhir) {
                cout << "Data ditemukan pada posisi ke-" << posisi << " :" << endl;
                cout << "Nama Buah : " << nodeBantu->isidata.nama << ", Jumlah : " << nodeBantu->isidata.jumlah << ", Harga : " << nodeBantu->isidata.harga << endl;
                cout << "-------------------------------------------" << endl;
                found = true;
            }
            nodeBantu = nodeBantu->next;
        }
        if(found == false) {
            cout << "Tidak ada data buah dalam range harga tersebut!" << endl;
            cout << "-------------------------------------------" << endl;
        }
    }
    cout << endl;
}
```

#### [main.cpp]
```C++
#include "listBuah.h"

#include<iostream>
using namespace std;

int main(){
    linkedlist List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataBuah dtBuah;

    nodeA = alokasi("Jeruk", 100, 3000);
    nodeB = alokasi("Apel", 75, 4000);
    nodeC = alokasi("Pir", 87, 5000);
    nodeD = alokasi("Semangka", 43, 11500);
    nodeE = alokasi("Durian", 15, 31450);

    insertFirst(List, nodeA);
    insertLast(List, nodeB);
    insertAfter(List, nodeC, nodeA);
    insertAfter(List, nodeD, nodeC);
    insertLast(List, nodeE);

    cout << "--- ISI LIST SETELAH DILAKUKAN INSERT ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    updateFirst(List);
    updateLast(List);
    updateAfter(List, nodeD);

    cout << "--- ISI LIST SETELAH DILAKUKAN UPDATE ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    FindNodeByData(List, "kelapa");
    FindNodeByAddress(List, nodeC);
    FindNodeByRange(List, 5000, 10000);

    delFirst(List);
    delLast(List);
    delAfter(List, nodeD, nodeC);

    cout << "--- ISI LIST SETELAH DILAKUKAN DELETE ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    deleteList(List);
    cout << "--- ISI LIST SETELAH DILAKUKAN HAPUS LIST ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

    return 0;
}
```
Kode ini merupakan implementasi lengkap struktur data Singly Linked List untuk menyimpan, memanipulasi, dan menampilkan data buah yang terdiri dari nama, jumlah, dan harga. File listBuah.h berisi deklarasi struktur data (struct buah, struct node, dan struct linkedlist) serta prototipe fungsi dan prosedur untuk operasi dasar linked list seperti insert, delete, update, dan search. File listBuah.cpp berisi implementasi dari semua operasi tersebut, termasuk fungsi untuk menambahkan node di awal, tengah, atau akhir list, menghapus node, memperbarui data, dan mencari data berdasarkan kriteria tertentu. Sedangkan file main.cpp berperan sebagai program utama yang mendemonstrasikan penggunaan semua fungsi dengan membuat beberapa node buah, melakukan berbagai operasi (insert, update, delete, search), dan menampilkan hasilnya ke layar. Program ini menjadi contoh praktis penerapan konsep linked list dinamis dengan manajemen memori manual dalam pemrograman terstruktur.

## Unguided 

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan5_modul5/unguided1-modul5.png)

#### [listAngka.h]
```C++
#ifndef LISTANGKA_H
#define LISTANGKA_H

#include <iostream>
using namespace std;

using dataAngka = int;

struct node {
    dataAngka Angka;
    node* Next;
};

using address = node*;

struct List {
    address First;
};

void CreateList(List &L);
address alokasi(dataAngka x);
void dealokasi(address &P);
void printList(const List &L);
void insertFirst(List &L, address nodeBaru);
void insertLast(List &L, address nodeBaru);
void insertAfter(List &L, address nodeBaru, address nodePrev);
int nbList(const List &L);
void delAfter(List &L, address nodePrev);

void updateFirst(List &L, dataAngka newVal);
void updateLast(List &L, dataAngka newVal);
void updateAfter(List &L, address nodePrev, dataAngka newVal);

#endif 
```

#### [listAngka.cpp]
```C++
#include "listAngka.h"
#include <iostream>
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
}

address alokasi(dataAngka x) {
    address P = new node;
    if (P != nullptr) {
        P->Angka = x;
        P->Next = nullptr;
    }
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void printList(const List &L) {
    address P = L.First;
    while (P != nullptr) {
        std::cout << P->Angka << " - ";
        P = P->Next;
    }
    std::cout << std::endl;
}

void insertFirst(List &L, address nodeBaru) {
    if (nodeBaru == nullptr) return;
    nodeBaru->Next = L.First;
    L.First = nodeBaru;
}

void insertLast(List &L, address nodeBaru) {
    if (nodeBaru == nullptr) return;
    if (L.First == nullptr) {
        L.First = nodeBaru;
    } else {
        address P = L.First;
        while (P->Next != nullptr) P = P->Next;
        P->Next = nodeBaru;
    }
}

void insertAfter(List &L, address nodeBaru, address nodePrev) {
    if (nodeBaru == nullptr || nodePrev == nullptr) return;
    nodeBaru->Next = nodePrev->Next;
    nodePrev->Next = nodeBaru;
}

int nbList(const List &L) {
    int cnt = 0;
    address P = L.First;
    while (P != nullptr) {
        cnt++;
        P = P->Next;
    }
    return cnt;
}

void delAfter(List &L, address nodePrev) {
    if (nodePrev == nullptr || nodePrev->Next == nullptr) return;
    address hapus = nodePrev->Next;
    nodePrev->Next = hapus->Next;
    dealokasi(hapus);
}

void updateFirst(List &L, dataAngka newVal) {
    if (L.First != nullptr) L.First->Angka = newVal;
}

void updateLast(List &L, dataAngka newVal) {
    if (L.First == nullptr) return;
    address P = L.First;
    while (P->Next != nullptr) P = P->Next;
    P->Angka = newVal;
}

void updateAfter(List &L, address nodePrev, dataAngka newVal) {
    if (nodePrev == nullptr || nodePrev->Next == nullptr) return;
    nodePrev->Next->Angka = newVal;
}
```

#### [main.cpp]
```C++
#include "listAngka.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    CreateList(L);

    address nodeA = alokasi(8);
    address nodeB = alokasi(13);
    address nodeC = alokasi(18);
    address nodeD = alokasi(25);
    address nodeE = alokasi(33);
    address nodeF = alokasi(40);

    insertFirst(L, nodeB);    
    insertLast(L, nodeA);     
    insertAfter(L, nodeD, nodeB); 

    insertFirst(L, nodeC);  
    insertLast(L, nodeE);      
    insertFirst(L, nodeF);    
    delAfter(L, nodeC);

    cout << "List setelah operasi insert/del: " << endl;
    printList(L);

    int nilai;

    cout << "\nMasukkan update data node pertama :" << endl;
    cout << "masukkan angka : ";
    if (cin >> nilai) {
        updateFirst(L, nilai);
        cout << "Data Berhasil Diupdate!" << endl << endl;
    }

    cout << "masukkan update data node setelah node 25 :" << endl;
    cout << "Masukkan angka : ";
    if (cin >> nilai) {
        updateAfter(L, nodeD, nilai);
        cout << "Data Berhasil Diupdate!" << endl << endl;
    }

    cout << "masukkan update data node terakhir :" << endl;
    cout << "Masukkan angka : ";
    if (cin >> nilai) {
        updateLast(L, nilai);
        cout << "Data Berhasil Diupdate!" << endl << endl;
    }

    cout << "masukkan update data node setelah node 50 :" << endl;
    cout << "Masukkan angka : ";
    if (cin >> nilai) {
        updateAfter(L, L.First, nilai);
        cout << "Data Berhasil Diupdate!" << endl << endl;
    }

    cout << "List setelah update: " << endl;
    printList(L);

    while (L.First != nullptr) {
        address temp = L.First;
        L.First = L.First->Next;
        dealokasi(temp);
    }

    return 0;
}
```

### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan5_modul5/output1-unguided1-modul5.png)

Program ini mengimplementasikan struktur data linked list sederhana untuk menyimpan dan memanipulasi data bertipe int. File listAngka.h mendefinisikan struktur node dan List, serta deklarasi fungsi operasi dasar seperti membuat list, alokasi/dealokasi node, mencetak isi list, serta operasi penyisipan (insert), penghapusan (delete), dan pembaruan (update) data. File listAngka.cpp berisi implementasi fungsi-fungsi tersebut, misalnya insertFirst, insertLast, delAfter, dan updateAfter. Di main.cpp, program membuat beberapa node berisi angka, melakukan serangkaian operasi penyisipan dan penghapusan node, kemudian memungkinkan pengguna memperbarui nilai pada node pertama, terakhir, atau setelah node tertentu melalui input. Akhirnya, program mencetak hasil akhir list dan membebaskan seluruh memori yang telah dialokasikan.

### 2. ![Screenshot Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan5_modul5/unguided2-modul5.png)

#### [listAngka.h]
```C++
#ifndef LISTANGKA_H
#define LISTANGKA_H

#include <iostream>
using namespace std;

using dataAngka = int;

struct node {
    dataAngka Angka;
    node* Next;
};

using address = node*;

struct List {
    address First;
};

void CreateList(List &L);
address alokasi(dataAngka x);
void dealokasi(address &P);
void printList(const List &L);
void insertFirst(List &L, address nodeBaru);
void insertLast(List &L, address nodeBaru);
void insertAfter(List &L, address nodeBaru, address nodePrev);
int nbList(const List &L);
void delAfter(List &L, address nodePrev);

void updateFirst(List &L, dataAngka newVal);
void updateLast(List &L, dataAngka newVal);
void updateAfter(List &L, address nodePrev, dataAngka newVal);

address SearchByData(const List &L, dataAngka x);
int SearchByAddress(const List &L, address node);
void SearchByRange(const List &L, dataAngka nilaiMin);

#endif
```

#### [listAngka.cpp]
```C++
#include "listAngka.h"
#include <iostream>
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
}

address alokasi(dataAngka x) {
    address P = new node;
    if (P != nullptr) {
        P->Angka = x;
        P->Next = nullptr;
    }
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void printList(const List &L) {
    address P = L.First;
    while (P != nullptr) {
        std::cout << P->Angka << " - ";
        P = P->Next;
    }
    std::cout << std::endl;
}

void insertFirst(List &L, address nodeBaru) {
    if (nodeBaru == nullptr) return;
    nodeBaru->Next = L.First;
    L.First = nodeBaru;
}

void insertLast(List &L, address nodeBaru) {
    if (nodeBaru == nullptr) return;
    if (L.First == nullptr) {
        L.First = nodeBaru;
    } else {
        address P = L.First;
        while (P->Next != nullptr) P = P->Next;
        P->Next = nodeBaru;
    }
}

void insertAfter(List &L, address nodeBaru, address nodePrev) {
    if (nodeBaru == nullptr || nodePrev == nullptr) return;
    nodeBaru->Next = nodePrev->Next;
    nodePrev->Next = nodeBaru;
}

int nbList(const List &L) {
    int cnt = 0;
    address P = L.First;
    while (P != nullptr) {
        cnt++;
        P = P->Next;
    }
    return cnt;
}

void delAfter(List &L, address nodePrev) {
    if (nodePrev == nullptr || nodePrev->Next == nullptr) return;
    address hapus = nodePrev->Next;
    nodePrev->Next = hapus->Next;
    dealokasi(hapus);
}

void updateFirst(List &L, dataAngka newVal) {
    if (L.First != nullptr) L.First->Angka = newVal;
}

void updateLast(List &L, dataAngka newVal) {
    if (L.First == nullptr) return;
    address P = L.First;
    while (P->Next != nullptr) P = P->Next;
    P->Angka = newVal;
}

void updateAfter(List &L, address nodePrev, dataAngka newVal) {
    if (nodePrev == nullptr || nodePrev->Next == nullptr) return;
    nodePrev->Next->Angka = newVal;
}

address SearchByData(const List &L, dataAngka x) {
    address P = L.First;
    while (P != nullptr) {
        if (P->Angka == x) return P;
        P = P->Next;
    }
    return nullptr;
}

int SearchByAddress(const List &L, address node) {
    address P = L.First;
    int pos = 1;
    while (P != nullptr) {
        if (P == node) return pos;
        P = P->Next;
        pos++;
    }
    return -1;
}

void SearchByRange(const List &L, dataAngka nilaiMin) {
    address P = L.First;
    int pos = 1;
    bool found = false;
    cout << "--- Data diatas nilai " << nilaiMin << " ---" << endl;
    cout << "----------------------------------------" << endl;
    while (P != nullptr) {
        if (P->Angka >= nilaiMin) {
            cout << "Data ditemukan pada posisi ke-" << pos << ", nilai : " << P->Angka << endl;
            cout << "----------------------------------------" << endl;
            found = true;
        }
        P = P->Next;
        pos++;
    }
    if (!found) {
        cout << "Tidak ada data di atas nilai " << nilaiMin << endl;
    }
}

```

#### [main.cpp]
```C++
#include "listAngka.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    CreateList(L);

    address node1 = alokasi(50);
    address node2 = alokasi(20);
    address node3 = alokasi(25);
    address node4 = alokasi(29); 
    address node5 = alokasi(45);

    address nodeA = node4;

    address nodeB = alokasi(999);

    insertLast(L, node1);
    insertLast(L, node2);
    insertLast(L, node3);
    insertLast(L, node4);
    insertLast(L, node5);

    cout << "List setelah operasi insert/del: " << endl;
    printList(L);

    cout << endl;
    cout << "Mencari data nilai 20" << endl;
    address found = SearchByData(L, 20);
    if (found != nullptr) {
        int pos = SearchByAddress(L, found);
        cout << "Data 20 ditemukan pada posisi ke-" << pos << "!" << endl;
    } else {
        cout << "Data 20 tidak ditemukan!" << endl;
    }

    cout << endl;
    cout << "Mencari data nilai 55" << endl;
    found = SearchByData(L, 55);
    if (found != nullptr) {
        int pos = SearchByAddress(L, found);
        cout << "Data 55 ditemukan pada posisi ke-" << pos << "!" << endl;
    } else {
        cout << "Node dengan data 55 tidak ditemukan!" << endl;
    }

    cout << endl;
    cout << "Mencari data alamat nodeB" << endl;
    int posB = SearchByAddress(L, nodeB);
    if (posB == -1) {
        cout << "Node dengan alamat " << nodeB << " tidak ditemukan dalam list!" << endl;
    } else {
        cout << "Node ditemukan pada posisi ke-" << posB << "!" << endl;
        cout << "Alamat node : " << nodeB << endl;
    }

    cout << endl;
    cout << "Mencari data alamat nodeA" << endl;
    int posA = SearchByAddress(L, nodeA);
    if (posA == -1) {
        cout << "Node dengan alamat " << nodeA << " tidak ditemukan dalam list!" << endl;
    } else {
        cout << "Node ditemukan pada posisi ke-" << posA << "!" << endl;
        cout << "Alamat node : " << nodeA << endl;
    }

    cout << endl;
    cout << "Mencari data dengan nilai minimal 40" << endl;
    SearchByRange(L, 40);

    while (L.First != nullptr) {
        address temp = L.First;
        L.First = L.First->Next;
        dealokasi(temp);
    }

    return 0;
}
```

### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan5_modul5/output1-unguided2-modul5.png)

Program ini mengimplementasikan linked list satu arah untuk menyimpan dan mencari data bertipe int menggunakan pointer dinamis. File listAngka.h mendefinisikan struktur list serta deklarasi fungsi untuk operasi dasar seperti membuat list, menambah, menghapus, memperbarui, dan mencari data. Implementasinya di listAngka.cpp mencakup fungsi pencarian tambahan: SearchByData untuk menemukan node berdasarkan nilai, SearchByAddress untuk menemukan posisi node berdasarkan alamatnya, dan SearchByRange untuk menampilkan semua data yang nilainya di atas batas tertentu. Pada main.cpp, program membuat beberapa node angka, menambahkannya ke list, lalu melakukan serangkaian pencarian berdasarkan nilai, alamat, dan rentang nilai. Hasil pencarian ditampilkan di layar, dan pada akhir program, semua node dihapus dari memori untuk mencegah kebocoran data.

### 3. ![Screenshot Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan5_modul5/unguided3-modul5.png)

#### [listAngka.h]
```C++
#ifndef LISTANGKA_H
#define LISTANGKA_H

#include <iostream>
using namespace std;

using dataAngka = int;

struct node {
    dataAngka Angka;
    node* Next;
};

using address = node*;

struct List {
    address First;
};

void CreateList(List &L);
address alokasi(dataAngka x);
void dealokasi(address &P);
void printList(const List &L);
void insertFirst(List &L, address nodeBaru);
void insertLast(List &L, address nodeBaru);
void insertAfter(List &L, address nodeBaru, address nodePrev);
int nbList(const List &L);
void delAfter(List &L, address nodePrev);

void updateFirst(List &L, dataAngka newVal);
void updateLast(List &L, dataAngka newVal);
void updateAfter(List &L, address nodePrev, dataAngka newVal);

long long SumList(const List &L);
long long SubtractList(const List &L);
long long MultiplyList(const List &L);

#endif
```
#### [listAngka.cpp]
```C++
#include "listAngka.h"
#include <iostream>
using namespace std;

void CreateList(List &L) {
    L.First = nullptr;
}

address alokasi(dataAngka x) {
    address P = new node;
    if (P != nullptr) {
        P->Angka = x;
        P->Next = nullptr;
    }
    return P;
}

void dealokasi(address &P) {
    if (P != nullptr) {
        delete P;
        P = nullptr;
    }
}

void printList(const List &L) {
    address P = L.First;
    while (P != nullptr) {
        std::cout << P->Angka << " - ";
        P = P->Next;
    }
    std::cout << std::endl;
}

void insertFirst(List &L, address nodeBaru) {
    if (nodeBaru == nullptr) return;
    nodeBaru->Next = L.First;
    L.First = nodeBaru;
}

void insertLast(List &L, address nodeBaru) {
    if (nodeBaru == nullptr) return;
    if (L.First == nullptr) {
        L.First = nodeBaru;
    } else {
        address P = L.First;
        while (P->Next != nullptr) P = P->Next;
        P->Next = nodeBaru;
    }
}

void insertAfter(List &L, address nodeBaru, address nodePrev) {
    if (nodeBaru == nullptr || nodePrev == nullptr) return;
    nodeBaru->Next = nodePrev->Next;
    nodePrev->Next = nodeBaru;
}

int nbList(const List &L) {
    int cnt = 0;
    address P = L.First;
    while (P != nullptr) {
        cnt++;
        P = P->Next;
    }
    return cnt;
}

void delAfter(List &L, address nodePrev) {
    if (nodePrev == nullptr || nodePrev->Next == nullptr) return;
    address hapus = nodePrev->Next;
    nodePrev->Next = hapus->Next;
    dealokasi(hapus);
}

void updateFirst(List &L, dataAngka newVal) {
    if (L.First != nullptr) L.First->Angka = newVal;
}

void updateLast(List &L, dataAngka newVal) {
    if (L.First == nullptr) return;
    address P = L.First;
    while (P->Next != nullptr) P = P->Next;
    P->Angka = newVal;
}

void updateAfter(List &L, address nodePrev, dataAngka newVal) {
    if (nodePrev == nullptr || nodePrev->Next == nullptr) return;
    nodePrev->Next->Angka = newVal;
}

long long SumList(const List &L) {
    long long sum = 0;
    address P = L.First;
    while (P != nullptr) {
        sum += P->Angka;
        P = P->Next;
    }
    return sum;
}

long long SubtractList(const List &L) {
    if (L.First == nullptr) return 0;
    long long acc = L.First->Angka;
    address P = L.First;
    while (P != nullptr) {
        acc -= P->Angka; 
        P = P->Next;
    }
    return acc;
}

long long MultiplyList(const List &L) {
    long long prod = 1;
    address P = L.First;
    while (P != nullptr) {
        prod *= P->Angka;
        P = P->Next;
    }
    return prod;
}
```

#### [main.cpp]
```C++
#include "listAngka.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    CreateList(L);

    insertLast(L, alokasi(50));
    insertLast(L, alokasi(20));
    insertLast(L, alokasi(25));
    insertLast(L, alokasi(29));
    insertLast(L, alokasi(45));

    cout << "List: ";
    printList(L);

    long long totalSum = SumList(L);
    long long totalSub = SubtractList(L);
    long long totalMul = MultiplyList(L);

    cout << "\nTotal penjumlahan : " << totalSum << endl << endl;
    cout << "Total pengurangan : " << totalSub << endl << endl;
    cout << "Total perkalian : " << totalMul << endl;

    while (L.First != nullptr) {
        address temp = L.First;
        L.First = L.First->Next;
        dealokasi(temp);
    }

    return 0;
}
```

### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan5_modul5/output1-unguided3-modul5.png)

Program ini mengimplementasikan struktur data linked list satu arah untuk menyimpan dan melakukan operasi aritmatika pada sekumpulan bilangan bulat. File listAngka.h mendefinisikan struktur node dan List, serta fungsi dasar seperti membuat list, menambah, menghapus, memperbarui, dan mencetak data. Pada listAngka.cpp, selain operasi dasar, terdapat tiga fungsi baru yaitu SumList untuk menghitung total penjumlahan seluruh elemen list, SubtractList untuk menghitung hasil pengurangan berurutan dari elemen-elemen list, dan MultiplyList untuk menghitung hasil perkalian semua elemen. Di main.cpp, program membuat list berisi beberapa angka, menampilkannya, lalu menampilkan hasil dari ketiga operasi aritmatika tersebut sebelum akhirnya menghapus semua node untuk membebaskan memori.

## Kesimpulan
SLL adalah struktur data yang fundamental dan sangat berguna untuk berbagai aplikasi karena fleksibilitas alokasi memori dan kemampuan penyisipan/penghapusan yang efisien pada posisi yang diketahui.

Namun, SLL memiliki keterbatasan terutama dalam hal akses acak yang lambat (harus traversing), dan traversal hanya satu arah. Oleh karena itu, pemilihan SLL harus mempertimbangkan kebutuhan aplikasi (apakah banyak akses acak atau lebih banyak insert/delete di awal).

Untuk aplikasi yang memerlukan traversal dua arah atau akses cepat ke node sebelumnya, varian seperti doubly linked list atau struktur data lain mungkin lebih cocok.

Dalam penelitian terkini, SLL masih menjadi objek studi penting — misalnya dalam analisis program, struktur data paralel/distribusi, dan optimasi algoritma pencarian — yang menunjukkan bahwa meskipun sederhana, SLL punya relevansi tinggi dalam ilmu komputer dan engineering.

## Referensi
[1]Bhatnagar, Sarvesh Rakesh. “Speeding Up Search in Singly Linked List.” International Journal of Computer Applications, vol. 182, no. 18, Sep 2018, pp. 19-24.

<br>[2]Garg, Pranav; Madhusudan, P.; Parlato, Gennaro. “Quantified Data Automata on Skinny Trees: an Abstract Domain for Lists.” 2013.

<br>[3]Ravishankar, Raaghav; Kulkarni, Sandeep; Peri, Sathya; Sharma, Gokarna. “Distributing Context-Aware Shared Memory Data Structures: A Case Study on Singly-Linked Lists.” 2024.