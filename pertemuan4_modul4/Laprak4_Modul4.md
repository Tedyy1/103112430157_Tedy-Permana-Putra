# <h1 align="center">Laporan Praktikum Modul 4 - SINGLY LINKED LIST (BAGIAN PERTAMA) </h1>
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

### 1. Implementasi Linked List Sederhana untuk Data Mahasiswa
```C++
[list.h] 
#ifndef LIST_H
#define LIST_H
#define Nil NULL

#include<iostream>
using namespace std;

struct mahasiswa {
    string nama;
    string nim;
    int umur;
};

typedef mahasiswa dataMahasiswa;

typedef struct node *address;

struct node {
    dataMahasiswa isidata;
    address next;
};

struct linkedlist {
    address first;
};

bool isEmpty(linkedlist List);
void createList(linkedlist &L);
address alokasi(string nama, string nim, int umur);
void dealokasi(address &node);
void printList(linkedlist List);

void insertFirst(linkedlist &List, address nodeBaru);
void insertAfter(linkedlist &List, address nodeBaru, address Prev);
void insertLast(linkedlist &List, address nodeBaru);

#endif

[list.cpp]
#include "list.h"
#include <iostream>
using namespace std;

//I.S = Initial State / kondisi awal
//F.S = Final State / kondisi akhir

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
    /* I.S. sembarang
       F.S. terbentuk list kosong */
    List.first = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, string nim, int umur) { 
    /* I.S. sembarang
       F.S. mengembalikan alamat node baru dengan isidata = sesuai parameter dan next = Nil */
    address nodeBaru = new node; 
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.nim = nim; 
    nodeBaru->isidata.umur = umur;
    nodeBaru->next = Nil;
    return nodeBaru;
}

//penghapusan node dengan menerapkan manajemen memori
void dealokasi(address &node) {
    /* I.S. P terdefinisi
       F.S. memori yang digunakan node dikembalikan ke sistem */
    node->next = Nil;
    delete node;
}

//prosedur-prosedur untuk insert / menambahkan node baru kedalam list
void insertFirst(linkedlist &List, address nodeBaru) {
    /* I.S. sembarang, P sudah dialokasikan
       F.S. menempatkan elemen list (node) pada awal list */
    nodeBaru->next = List.first; 
    List.first = nodeBaru;
}

void insertAfter(linkedlist &List, address nodeBaru, address Prev) {
    /* I.S. sembarang, nodeBaru dan Prev alamat salah satu elemen list (node)
       F.S. menempatkan elemen (node) sesudah elemen node Prev */
    if (Prev != Nil) {
        nodeBaru->next = Prev->next;
        Prev->next = nodeBaru;
    } else {
        cout << "Node sebelumnya tidak valid!" << endl;
    }
}

void insertLast(linkedlist &List, address nodeBaru) {
    /* I.S. sembarang, nodeBaru sudah dialokasikan
       F.S. menempatkan elemen nodeBaru pada akhir list */
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

//prosedur untuk menampilkan isi list
void printList(linkedlist List) {
    /* I.S. list mungkin kosong
       F.S. jika list tidak kosong menampilkan semua info yang ada pada list */
    if (isEmpty(List)) {
        cout << "List kosong." << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama : " << nodeBantu->isidata.nama << ", NIM : " << nodeBantu->isidata.nim 
            << ", Usia : " << nodeBantu->isidata.umur << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

[main.cpp]
#include "list.h"

#include<iostream>
using namespace std;

int main(){
    linkedlist List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataMahasiswa mhs;

    nodeA = alokasi("Dhimas", "2311102151", 20);
    nodeB = alokasi("Arvin", "2211110014", 21);
    nodeC = alokasi("Rizal", "2311110029", 20);
    nodeD = alokasi("Satrio", "2211102173", 21);
    nodeE = alokasi("Joshua", "2311102133", 21);

    insertFirst(List, nodeA);
    insertLast(List, nodeB);
    insertAfter(List, nodeC, nodeA);
    insertAfter(List, nodeD, nodeC);
    insertLast(List, nodeE);
    
    cout << "--- ISI LIST SETELAH DILAKUKAN INSERT ---" << endl;
    printList(List);

    return 0;
}
```
Kode ini mengimplementasikan linked list sederhana untuk menyimpan data mahasiswa. File list.h berisi definisi struktur dan deklarasi fungsi, list.cpp mengimplementasikan operasi seperti membuat list, menambah node, dan menampilkan isi list, sedangkan main.cpp berfungsi untuk menjalankan program utama dengan menambahkan beberapa data mahasiswa ke dalam list dan mencetak hasilnya. Program ini menunjukkan penggunaan pointer dan manajemen memori dasar dalam pengelolaan data dinamis.

### 2. Program Implementasi Linked List Lengkap untuk Data Mahasiswa

```C++
[list.h]
#ifndef LIST_H
#define LIST_H
#define Nil NULL

#include<iostream>
using namespace std;

struct mahasiswa {
    string nama;
    string nim;
    int umur;
};

typedef mahasiswa dataMahasiswa;

typedef struct node *address;

struct node {
    dataMahasiswa isidata;
    address next;
};

struct linkedlist {
    address first;
};

bool isEmpty(linkedlist List);
void createList(linkedlist &L);
address alokasi(string nama, string nim, int umur);
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

#endif

[list.cpp]
#include "list.h"
#include <iostream>
using namespace std;

//I.S = Initial State / kondisi awal
//F.S = Final State / kondisi akhir

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
    /* I.S. sembarang
       F.S. terbentuk list kosong */
    List.first = Nil;
}

//pembuatan node baru dengan menerapkan manajemen memori
address alokasi(string nama, string nim, int umur) { 
    /* I.S. sembarang
       F.S. mengembalikan alamat node baru dengan isidata = sesuai parameter dan next = Nil */
    address nodeBaru = new node; 
    nodeBaru->isidata.nama = nama;
    nodeBaru->isidata.nim = nim; 
    nodeBaru->isidata.umur = umur;
    nodeBaru->next = Nil;
    return nodeBaru;
}

//penghapusan node dengan menerapkan manajemen memori
void dealokasi(address &node) {
    /* I.S. P terdefinisi
       F.S. memori yang digunakan node dikembalikan ke sistem */
    node->next = Nil;
    delete node;
}

//prosedur-prosedur untuk insert / menambahkan node baru kedalam list
void insertFirst(linkedlist &List, address nodeBaru) {
    /* I.S. sembarang, P sudah dialokasikan
       F.S. menempatkan elemen list (node) pada awal list */
    nodeBaru->next = List.first; 
    List.first = nodeBaru;
}

void insertAfter(linkedlist &List, address nodeBaru, address Prev) {
    /* I.S. sembarang, nodeBaru dan Prev alamat salah satu elemen list (node)
       F.S. menempatkan elemen (node) sesudah elemen node Prev */
    if (Prev != Nil) {
        nodeBaru->next = Prev->next;
        Prev->next = nodeBaru;
    } else {
        cout << "Node sebelumnya tidak valid!" << endl;
    }
}

void insertLast(linkedlist &List, address nodeBaru) {
    /* I.S. sembarang, nodeBaru sudah dialokasikan
       F.S. menempatkan elemen nodeBaru pada akhir list */
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
    /* I.S. list tidak kosong
    F.S. node pertama di list terhapus*/
    address nodeHapus;
    if (isEmpty(List) == false) {
        nodeHapus = List.first;
        List.first = List.first->next;
        nodeHapus->next = Nil;
        dealokasi(nodeHapus);
    } else {
        cout << "List kosong!" << endl;
    }
}

void delLast(linkedlist &List){
    /* I.S. list tidak kosong
    F.S. node terakhir di list terhapus */
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
    } else {
        cout << "list kosong" << endl;
    }
}

void delAfter(linkedlist &List, address nodeHapus, address nodePrev){
    /* I.S. list tidak kosng, Prev alamat salah satu elemen list
    F.S. nodeBantu adalah alamat dari Prev→next, menghapus Prev→next dari list */
    if(isEmpty(List) == true){
        cout << "List kosong!" << endl;
    } else { //jika list tidak kosong
        if (nodePrev != Nil && nodePrev->next != Nil) { 
            nodeHapus = nodePrev->next;       
            nodePrev->next = nodeHapus->next;  
            nodeHapus->next = Nil;         
            dealokasi(nodeHapus);
        } else {
            cout << "Node sebelumnya (prev) tidak valid!" << endl;
        }
    }
}

//prosedur untuk menampilkan isi list
void printList(linkedlist List) {
    /* I.S. list mungkin kosong
       F.S. jika list tidak kosong menampilkan semua info yang ada pada list */
    if (isEmpty(List)) {
        cout << "List kosong." << endl;
    } else {
        address nodeBantu = List.first;
        while (nodeBantu != Nil) { 
            cout << "Nama : " << nodeBantu->isidata.nama << ", NIM : " << nodeBantu->isidata.nim << ", Usia : " << nodeBantu->isidata.umur << endl;
            nodeBantu = nodeBantu->next;
        }
    }
}

//function untuk menampilkan jumlah node didalam list
int nbList(linkedlist List) {
    /* I.S. list sudah ada
       F.S. menampilkan jumlah node didalam list*/
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
    /* I.S. list sudah ada
       F.S. menghapus semua node didalam list*/
    address nodeBantu, nodeHapus;
    nodeBantu = List.first;
    while(nodeBantu != Nil){
        nodeHapus = nodeBantu;
        nodeBantu = nodeBantu->next;
        dealokasi(nodeHapus); 
    }
    List.first = Nil; 
    cout << "List sudah terhapus!" << endl;
}

[main.cpp]
#include "list.h"

#include<iostream>
using namespace std;

int main(){
    linkedlist List;
    address nodeA, nodeB, nodeC, nodeD, nodeE = Nil;
    createList(List);

    dataMahasiswa mhs;

    nodeA = alokasi("Dhimas", "2311102151", 20);
    nodeB = alokasi("Arvin", "2211110014", 21);
    nodeC = alokasi("Rizal", "2311110029", 20);
    nodeD = alokasi("Satrio", "2211102173", 21);
    nodeE = alokasi("Joshua", "2311102133", 21);

    insertFirst(List, nodeA);
    insertLast(List, nodeB);
    insertAfter(List, nodeC, nodeA);
    insertAfter(List, nodeD, nodeC);
    insertLast(List, nodeE);

    cout << "--- ISI LIST SETELAH DILAKUKAN INSERT ---" << endl;
    printList(List);
    cout << "jumlah node : " << nbList(List) << endl;
    cout << endl;

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
Kode ini merupakan implementasi linked list lengkap untuk mengelola data mahasiswa yang mencakup operasi penambahan, penghapusan, pencetakan, dan penghitungan jumlah node. File list.h berisi definisi struktur data dan deklarasi fungsi, list.cpp mengimplementasikan seluruh fungsi seperti insertFirst, insertLast, delFirst, delLast, delAfter, nbList, dan deleteList, sedangkan main.cpp berperan sebagai program utama untuk menguji operasi-operasi tersebut. Program ini menunjukkan cara mengelola data secara dinamis menggunakan pointer dan memori heap, sekaligus memperlihatkan konsep dasar manajemen memori dan manipulasi node dalam linked list.

## Unguided 

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan4_modul4/unguided1_1-modul4.png)

### ![Screenshot Unguided 1_2](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan4_modul4/unguided1_2-modul4.png)

```C++
[singlylist.h]
#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include <iostream>
using namespace std;

#define Nil NULL

typedef int infotype;
typedef struct ElmList *address;

struct ElmList {
    infotype info;
    address next;
};

struct List {
    address first;
};

void createList(List &L);
address alokasi(infotype x);
void dealokasi(address P);
void insertFirst(List &L, address P);
void printInfo(List L);

#endif

[singlylist.cpp]
#include "Singlylist.h"

void createList(List &L) {
    L.first = Nil;
}

address alokasi(infotype x) {
    address P = new ElmList;
    P->info = x;
    P->next = Nil;
    return P;
}

void dealokasi(address P) {
    delete P;
}

void insertFirst(List &L, address P) {
    P->next = L.first;
    L.first = P;
}

void printInfo(List L) {
    address P = L.first;
    while (P != Nil) {
        cout << P->info << " ";
        P = P->next;
    }
    cout << endl;
}

[main.cpp]
#include "Singlylist.h"

int main() {
    List L;
    address P1, P2, P3, P4, P5 = Nil;

    createList(L);

    P1 = alokasi(2);
    insertFirst(L, P1);

    P2 = alokasi(0);
    insertFirst(L, P2);

    P3 = alokasi(8);
    insertFirst(L, P3);

    P4 = alokasi(12);
    insertFirst(L, P4);

    P5 = alokasi(9);
    insertFirst(L, P5);

    printInfo(L); 

    return 0;
}
```
### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan4_modul4/output1-unguided1-modul4.png)

Kode ini merupakan implementasi singly linked list sederhana yang menyimpan data bertipe int. File singlylist.h mendefinisikan struktur node (ElmList) dan list (List) serta deklarasi fungsi dasar seperti createList, alokasi, insertFirst, dan printInfo. File singlylist.cpp berisi implementasinya, di mana list dibuat kosong, node baru dialokasikan secara dinamis, dan elemen baru selalu disisipkan di awal list. Pada main.cpp, program membuat lima node dengan nilai berbeda, menambahkannya ke dalam list menggunakan insertFirst, lalu mencetak seluruh isi list. Program ini menggambarkan konsep dasar pembuatan, penyisipan, dan traversal pada singly linked list.

### 2. ![Screenshot Soal Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan4_modul4/unguided1-modul4.png)

```C++ 
[Singlylist.h]
#ifndef SINGLYLIST_H
#define SINGLYLIST_H

#include <iostream>
using namespace std;

struct Node {
    int data;
    Node* next;
};

struct List {
    Node* first;
};

void createList(List &L);
void insertFirst(List &L, int nilai);
void insertAfter(Node* prevNode, int nilai);
void insertLast(List &L, int nilai);
void deleteFirst(List &L);
void deleteAfter(Node* prevNode);
void deleteLast(List &L);
void deleteList(List &L);
void printList(List L);
int nbList(List L);

#endif

[Singlylist.cpp]
#include "Singlylist.h"
#include <iostream>
using namespace std;

void createList(List &L) {
    L.first = NULL;
}

void insertFirst(List &L, int nilai) {
    Node* newNode = new Node;
    newNode->data = nilai;
    newNode->next = L.first;
    L.first = newNode;
}

void insertAfter(Node* prevNode, int nilai) {
    if (prevNode != NULL) {
        Node* newNode = new Node;
        newNode->data = nilai;
        newNode->next = prevNode->next;
        prevNode->next = newNode;
    }
}

void insertLast(List &L, int nilai) {
    Node* newNode = new Node;
    newNode->data = nilai;
    newNode->next = NULL;

    if (L.first == NULL) {
        L.first = newNode;
    } else {
        Node* temp = L.first;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = newNode;
    }
}

void deleteFirst(List &L) {
    if (L.first != NULL) {
        Node* temp = L.first;
        L.first = temp->next;
        delete temp;
    }
}

void deleteAfter(Node* prevNode) {
    if (prevNode != NULL && prevNode->next != NULL) {
        Node* temp = prevNode->next;
        prevNode->next = temp->next;
        delete temp;
    }
}

void deleteLast(List &L) {
    if (L.first != NULL) {
        if (L.first->next == NULL) {
            delete L.first;
            L.first = NULL;
        } else {
            Node* temp = L.first;
            while (temp->next->next != NULL)
                temp = temp->next;
            delete temp->next;
            temp->next = NULL;
        }
    }
}

void deleteList(List &L) {
    while (L.first != NULL) {
        deleteFirst(L);
    }
}

void printList(List L) {
    Node* temp = L.first;
    while (temp != NULL) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int nbList(List L) {
    int count = 0;
    Node* temp = L.first;
    while (temp != NULL) {
        count++;
        temp = temp->next;
    }
    return count;
}

[main.cpp]
#include "Singlylist.h"
#include <iostream>
using namespace std;

int main() {
    List L;
    createList(L);

    insertFirst(L, 9);
    insertLast(L, 12);
    insertLast(L, 8);
    insertLast(L, 0);
    insertLast(L, 2);

    printList(L); 

    deleteFirst(L);     
    deleteLast(L);
    deleteAfter(L.first); 

    printList(L);
    cout << "Jumlah node : " << nbList(L) << endl;

    deleteList(L);
    cout << "\n- List Berhasil Terhapus -" << endl;
    cout << "Jumlah node : " << nbList(L) << endl;

    return 0;
}
```
### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan4_modul4/output1-unguided2-modul4.png)

Kode ini merupakan implementasi singly linked list lengkap yang mendukung operasi dasar seperti penambahan, penghapusan, pencetakan, dan perhitungan jumlah node. File Singlylist.h mendefinisikan struktur Node dan List serta deklarasi fungsi-fungsi operasi, sedangkan Singlylist.cpp mengimplementasikan logika untuk membuat list, menambah node di awal, tengah, dan akhir, menghapus node dari berbagai posisi, serta menghapus seluruh isi list. Pada main.cpp, program menguji fungsi-fungsi tersebut dengan menambahkan beberapa angka ke list, menampilkan isi list, menghapus beberapa elemen, menghitung jumlah node, dan akhirnya mengosongkan list. Program ini menunjukkan cara kerja manipulasi data dinamis menggunakan pointer dalam struktur data linked list.

## Kesimpulan
SLL adalah struktur data yang fundamental dan sangat berguna untuk berbagai aplikasi karena fleksibilitas alokasi memori dan kemampuan penyisipan/penghapusan yang efisien pada posisi yang diketahui.

Namun, SLL memiliki keterbatasan terutama dalam hal akses acak yang lambat (harus traversing), dan traversal hanya satu arah. Oleh karena itu, pemilihan SLL harus mempertimbangkan kebutuhan aplikasi (apakah banyak akses acak atau lebih banyak insert/delete di awal).

Untuk aplikasi yang memerlukan traversal dua arah atau akses cepat ke node sebelumnya, varian seperti doubly linked list atau struktur data lain mungkin lebih cocok.

Dalam penelitian terkini, SLL masih menjadi objek studi penting — misalnya dalam analisis program, struktur data paralel/distribusi, dan optimasi algoritma pencarian — yang menunjukkan bahwa meskipun sederhana, SLL punya relevansi tinggi dalam ilmu komputer dan engineering.

## Referensi
[1]Bhatnagar, Sarvesh Rakesh. “Speeding Up Search in Singly Linked List.” International Journal of Computer Applications, vol. 182, no. 18, Sep 2018, pp. 19-24.

<br>[2]Garg, Pranav; Madhusudan, P.; Parlato, Gennaro. “Quantified Data Automata on Skinny Trees: an Abstract Domain for Lists.” 2013.

<br>[3]Ravishankar, Raaghav; Kulkarni, Sandeep; Peri, Sathya; Sharma, Gokarna. “Distributing Context-Aware Shared Memory Data Structures: A Case Study on Singly-Linked Lists.” 2024.