# <h1 align="center">Laporan Praktikum Modul 10 - TREE (BAGIAN PERTAMA)</h1?>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori
### 1. Definisi Pohon (Tree)
Pohon (tree) adalah struktur data non-linier yang terdiri dari simpul (node) yang dihubungkan oleh tepi (edge) dalam hirarki dengan satu simpul akar (root) di bagian atas dan simpul daun (leaf) di bagian bawah. Setiap simpul kecuali akar memiliki satu simpul induk (parent), dan dapat memiliki nol atau lebih simpul anak (child). Tree digunakan secara luas dalam ilmu komputer untuk mewakili data hierarki seperti sistem file, organisasi perusahaan, dan struktur dokumen.

### 2. Komponen dan Terminologi Tree
Sistem tree terdiri dari beberapa elemen utama:
- Akar (root): simpul paling atas dalam tree yang tidak memiliki parent.
- Simpul internal (internal node): simpul yang memiliki satu atau lebih child.
- Daun (leaf): simpul yang tidak memiliki child (simpul terminal).
- Kedalaman (depth): jumlah tepi dari akar ke suatu simpul, mengukur level hirarki.
- Tinggi (height): jumlah tepi dari simpul ke daun terjauh, menentukan kedalaman maksimal tree.
- Derajat (degree): jumlah child dari suatu simpul, atau jumlah total edge yang terhubung pada simpul.

### 3. Jenis-Jenis Tree Utama
- Binary Tree: tree di mana setiap simpul memiliki paling banyak dua child (left child dan right child). Merupakan dasar untuk banyak struktur data yang lebih kompleks.
- Binary Search Tree (BST): binary tree terurut di mana untuk setiap simpul, semua nilai pada subtree kiri lebih kecil dan semua nilai pada subtree kanan lebih besar. Memungkinkan pencarian, penyisipan, dan penghapusan dengan kompleksitas rata-rata O(log n).
- AVL Tree: self-balancing binary search tree yang mempertahankan keseimbangan tinggi dengan faktor keseimbangan antara -1 dan 1, menjamin kompleksitas O(log n) untuk semua operasi.
- Red-Black Tree: self-balancing binary search tree dengan properti warna yang menjamin keseimbangan dan kinerja O(log n) untuk operasi dasar, lebih fleksibel dari AVL tree.
- B-Tree: tree berderajat tinggi yang dioptimalkan untuk sistem penyimpanan disk, digunakan dalam database dan sistem file untuk mengurangi jumlah akses disk.

### 4. Operasi Dasar pada Tree
- Traversal (penelusuran): mengunjungi semua simpul dalam tree dengan pola tertentu (in-order, pre-order, post-order untuk binary tree; level-order untuk tree umum).
- Pencarian (search): menemukan simpul dengan nilai spesifik dalam tree, efisiensi tergantung pada jenis tree dan keseimbangannya.
- Penyisipan (insertion): menambahkan simpul baru ke tree sambil mempertahankan properti tree tertentu (misalnya BST property atau keseimbangan).
- Penghapusan (deletion): menghilangkan simpul dari tree dengan menjaga struktur dan properti tree tetap valid.
- Rotasi (rotation): operasi lokal untuk mempertahankan keseimbangan dalam self-balancing tree seperti AVL dan Red-Black tree.

### 5. Penerapan dan Aplikasi Tree
- Sistem file: tree struktur digunakan untuk merepresentasikan hirarki folder dan file dalam sistem operasi.
- Database dan indexing: B-tree dan variannya (B+-tree) digunakan sebagai struktur index dalam database modern untuk akses data yang efisien.
- Huffman Coding: binary tree digunakan dalam algoritma kompresi data untuk menghasilkan kode optimal dengan panjang variabel.
- Ekspresi matematis: tree digunakan untuk merepresentasikan dan mengevaluasi ekspresi matematis dalam compiler dan interpreter.
- Pengambilan keputusan: decision tree digunakan dalam machine learning dan artificial intelligence untuk klasifikasi dan prediksi.
- Sistem file browser: aplikasi GUI menggunakan tree widget untuk menampilkan hirarki folder dan item secara interaktif.

### 6. Analisis Kompleksitas dan Performa
Kompleksitas operasi tree bergantung pada struktur dan keseimbangannya:
- Tree seimbang (balanced tree): operasi pencarian, penyisipan, dan penghapusan memiliki kompleksitas waktu O(log n), memberikan performa optimal.
- Tree tidak seimbang (unbalanced tree): dalam kasus terburuk (misalnya tree menjadi linear seperti linked list), kompleksitas menjadi O(n), sangat tidak efisien.
- Tree berderajat tinggi (B-tree): mengurangi jumlah akses disk dengan mempertahankan banyak child per node, cocok untuk penyimpanan eksternal.

### 7. Perkembangan dan Variasi Tree
- Ternary Search Tree (TST): tree pencarian dengan tiga cabang per node, digunakan dalam aplikasi pencarian string dan spell checking.
- Splay Tree: self-adjusting binary search tree yang menggerakkan node yang sering diakses lebih dekat ke akar untuk performa cache yang lebih baik.
- Trie (Prefix Tree): tree khusus untuk menyimpan string dengan operasi pencarian prefix yang efisien, banyak digunakan dalam auto-complete dan spell checking.
- Segment Tree dan Fenwick Tree: struktur tree yang dioptimalkan untuk query range sum dan update interval dalam waktu logaritmik, aplikasi dalam competitive programming dan analisis data.


## Guided 

### 1. Implementasi dan Pengujian Binary Search Tree (BST)
#### [bst.h]
```C++
#ifndef BST_H
#define BST_H
#define Nil NULL 

using namespace std;

typedef struct BST *node;

struct BST {
    int angka;
    node left;
    node right;
};

typedef node BinTree;

bool isEmpty(BinTree tree);
void createTree(BinTree &tree);
node alokasi(int angka);
void deAlokasi(node nodeHapus);

void insertNode(BinTree &tree, node nodeBaru);
void searchByData(BinTree tree, int angka);
void preOrder(BinTree tree);
void inOrder(BinTree tree);
void postOrder(BinTree tree);

bool deleteNode(BinTree &tree, int angka);
node mostRight(BinTree tree);
node mostLeft(BinTree tree);
void deleteTree(BinTree &tree);
int size(BinTree tree);
int height(BinTree tree);

#endif
```

#### [bst.cpp]
```C++
#include "bst.h"
#include <iostream>

using namespace std;
//NOTE : parameter tree disini maksudnya merujuk ke node; baik itu node root atau node lain dari tree

bool isEmpty(BinTree tree){
    if(tree == Nil){
        return true;
    } else {
        return false;
    }
}

void createTree(BinTree &tree){
    tree = Nil;
}

node alokasi(int angkaInput){
    node nodeBaru = new BST;
    nodeBaru->angka = angkaInput;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void dealokasi(node nodeHapus){
    delete nodeHapus;
}

void insertNode(BinTree &tree, node nodeBaru){
    if(tree == Nil){
        tree = nodeBaru;
        cout << "Node " << nodeBaru->angka << " berhasil ditambahkan ke dalam tree!" << endl;
        return;
    } else if(nodeBaru->angka < tree->angka){
        insertNode(tree->left, nodeBaru);
    } else if(nodeBaru->angka > tree->angka){
        insertNode(tree->right, nodeBaru);
    }
}

void searchByData(BinTree tree, int angkaCari){
    if(isEmpty(tree) == true){
        cout << "Tree kosong!" << endl;
    } else {
        node nodeBantu = tree;
        node parent = Nil;
        bool ketemu = false;
        while(nodeBantu != Nil){
            if(angkaCari < nodeBantu->angka){
                parent = nodeBantu;
                nodeBantu = nodeBantu->left;
            } else if(angkaCari > nodeBantu->angka){
                parent = nodeBantu;
                nodeBantu = nodeBantu->right;
            } else if(angkaCari == nodeBantu->angka){
                ketemu = true;
                break;
            }
        }
        if(ketemu == false){
            cout << "Data tidak ditemukan" << endl;
        } else if(ketemu == true){
            cout << "Data ditemukan didalam tree!" << endl;
            cout << "Data Angka : " << nodeBantu->angka << endl;

            //menampilkan parentnya & pengecekan sibling
            node sibling = Nil;
            if(parent != Nil){
                cout << "Parent : " << parent->angka << endl;
                if(parent->left == nodeBantu){
                    sibling = parent->right;
                } else if(parent->right == nodeBantu){
                    sibling = parent->left;
                }
            } else {
                cout << "Parent : - (node root)"<< endl;
            }

            //menampilkan siblingnya
            if(sibling != Nil){
                cout << "Sibling : " << sibling->angka << endl;
            } else {
                cout << "Sibling : - " << endl;
            }

            //menampilkan childnya
            if(nodeBantu->left != Nil){
                cout << "Child kiri : " << nodeBantu->left->angka << endl;
            } else if(nodeBantu->left == Nil){
                cout << "Child kiri : -" << endl;
            }
            if(nodeBantu->right != Nil){
                cout << "Child kanan : " << nodeBantu->right->angka << endl;
            } else if(nodeBantu->right == Nil){
                cout << "Child kanan : -" << endl;
            }
        }
    }
}

void preOrder(BinTree tree){ //tengah - kiri - kanan atau root - child kiri - child kanan
    if(tree == Nil){
        return;
    }
    cout << tree->angka << " - ";
    preOrder(tree->left);
    preOrder(tree->right);
}

void inOrder(BinTree tree){ //kiri - tengah - kanan atau child kiri - root - child kanan
    if(tree == Nil){
        return;
    }
    inOrder(tree->left);
    cout << tree->angka << " - ";
    inOrder(tree->right);
}

void postOrder(BinTree tree){ //kiri - kanan - tengah atau child kiri - child kanan - root
    if(tree == Nil){
        return;
    }
    postOrder(tree->left);
    postOrder(tree->right);
    cout << tree->angka << " - ";
}



bool deleteNode(BinTree &tree, int angka) {
    if (tree == Nil) {
        return false; //data tidak ditemukan di subtree ini
    } else {
        if (angka < tree->angka) {
            return deleteNode(tree->left, angka);
        } else if (angka > tree->angka) {
            return deleteNode(tree->right, angka);
        } else {
            //jika node yang mau dihapus ditemukan
            //Case 1 : node yang mau dihapus adalah leaf
            if (tree->left == Nil && tree->right == Nil) {
                node tmp = tree;
                tree = Nil;
                dealokasi(tmp);
            }
            //Case 2 : node yang mau dihapus hanya punya right child
            else if (tree->left == Nil) {
                node tmp = tree;
                tree = tree->right;
                dealokasi(tmp);
            }
            //Case 3 : node yang mau dihapus hanya punya left child
            else if (tree->right == Nil) {
                node tmp = tree;
                tree = tree->left;
                dealokasi(tmp);
            }
            // Case 4 : jika node yang mau dihapus punya dua child, maka ambil mostleft dari subtree kanan untuk menggantikan node yang mau dihapus
            else {
                //mostleft dari subtree kanan = node successor (node penerus)
                node successor = mostLeft(tree->right);
                //salin data successor ke node saat ini
                tree->angka = successor->angka;
                //hapus successor pada subtree kanan
                return deleteNode(tree->right, successor->angka);
            }
            return true; //berhasil dihapus
        }
    }
}

node mostRight(BinTree tree){
    while (tree->right != Nil){
        tree = tree->right;
    }
    return tree;    
}

node mostLeft(BinTree tree){
    while (tree->left != Nil){
        tree = tree->left;
    }
    return tree;
}

void deleteTree(BinTree &tree){
    if(tree == Nil){
        return;
    } else {
        deleteTree(tree->left);
        deleteTree(tree->right);
        dealokasi(tree);
        tree = Nil;
    }
}

int size(BinTree tree){ //mengembalikan jumlah semua node
    if(isEmpty(tree) == true){
        return 0;
    } else {
        return 1 + size(tree->left) + size(tree->right);
    }
    cout << endl;
}

int height(BinTree tree){ //mengembalikan jumlah level tree
    if(isEmpty(tree) == true){
        return -1; //tree kosong jika height = -1
    } else {
        int hl = height(tree->left);
        int hr = height(tree->right);
        int maxHeight;
        if (hl > hr){
            maxHeight = hl;
        } else {
            maxHeight = hr;
        }
        return 1 + maxHeight;
    }
    cout << endl;
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "bst.h"

using namespace std;

int main() {
    BinTree tree;
    createTree(tree);

    int pilih, angka;

    do {
        cout << "========= MENU BST =========" << endl;
        cout << "1. Insert Node" << endl;
        cout << "2. Delete Node" << endl;
        cout << "3. Search Data" << endl;
        cout << "4. Tampilkan PreOrder" << endl;
        cout << "5. Tampilkan InOrder" << endl;
        cout << "6. Tampilkan PostOrder" << endl;
        cout << "7. Size Tree (jumlah node)" << endl;
        cout << "8. Height Tree (tinggi level)" << endl;
        cout << "9. Tampilkan mostright" << endl;
        cout << "10. Tampilkan mostleft" << endl;
        cout << "11. Delete Seluruh Tree" << endl;
        cout << "0. Keluar" << endl;
        cout << "pilihan anda : ";
        cin >> pilih;
        cout << endl;

        switch (pilih){
        case 1:
            cout << "Masukkan angka: ";
            cin >> angka;
            insertNode(tree, alokasi(angka));
            cout << endl;
            break;

        case 2:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
            } else {
                cout << "Masukkan angka yang ingin dihapus: ";
                cin >> angka;
                if(deleteNode(tree, angka)){
                    cout << "Data " << angka << " berhasil dihapus!" << endl;
                } else {
                    cout << "Data " << angka << " tidak ditemukan!" << endl;
                }
            }
            cout << endl;
            break;

        case 3:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
            } else {
                cout << "Masukkan angka yang ingin dicari: ";
                cin >> angka;
                searchByData(tree, angka);
            }
            cout << endl;
            break;

        case 4:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
            } else {
                cout << "PreOrder : ";
                preOrder(tree);
                cout << endl;
            }
            cout << endl;
            break;

        case 5:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
            } else {
                cout << "InOrder : ";
                inOrder(tree);
                cout << endl;
            }
            cout << endl;
            break;

        case 6:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
            } else {
                cout << "PostOrder : ";
                postOrder(tree);
                cout << endl;
            }
            cout << endl;
            break;

        case 7:
            cout << "Size Tree = " << size(tree) << endl;
            cout << endl;
            break;

        case 8:
            cout << "Height Tree = " << height(tree) << endl;
            cout << endl;
            break;

        case 9: 
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
                cout << endl;
            } else {
                cout << "Mostright : " << mostRight(tree)->angka << endl;
                cout << endl;
            }
            break;
        
        case 10:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
                cout << endl;
            } else {
                cout << "Mostleft : " << mostLeft(tree)->angka << endl;
                cout << endl;
            }
            break;

        case 11:
            if(isEmpty(tree) == true){
                cout << "Tree kosong!" << endl;
            } else {
                deleteTree(tree);
                cout << "Seluruh tree berhasil dihapus!" << endl;
            }
            cout << endl;
            break;

        case 0:
            cout << "Keluar dari program..." << endl;
            break;

        default:
            cout << "Pilihan tidak valid!" << endl;
            break;
        }

    } while (pilih != 0);

    return 0;
}
```

Kode ini mengimplementasikan Binary Search Tree (BST) yang merupakan struktur data tree non-linier di mana setiap node memiliki paling banyak dua child (left dan right). Properti utama BST adalah untuk setiap node, semua nilai pada subtree kiri lebih kecil dari node tersebut, dan semua nilai pada subtree kanan lebih besar. Program ini menyediakan berbagai operasi fundamental seperti insert node, delete node dengan empat case berbeda (leaf, hanya child kanan, hanya child kiri, dan dua child), pencarian data dengan informasi lengkap tentang parent, sibling, dan child, serta traversal dalam tiga bentuk (pre-order, in-order, post-order). Selain itu, program juga menampilkan operasi utility seperti mencari node terkanan (mostright), node terkiri (mostleft), menghitung jumlah node (size), dan menghitung tinggi tree (height). Implementasi ini menunjukkan bagaimana BST dapat digunakan untuk operasi pencarian, penyisipan, dan penghapusan data secara efisien dengan kompleksitas rata-rata O(log n).

## Unguided 

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan10_modul10/unguided1-modul10.png)

#### [bstree.h]
```C++
#ifndef BSTREE_H
#define BSTREE_H
#define Nil NULL

#include <iostream>
using namespace std;

typedef struct BST *node;

struct BST {
    int info;
    node left;
    node right;
};

typedef node BinTree;

bool isEmpty(BinTree pohon);
void createTree(BinTree &pohon);
node alokasi(int x);
void insertNode(BinTree &pohon, node nodeBaru);
node findNode(int x, BinTree pohon);
void inOrder(BinTree pohon);

#endif
```

#### [bstree.cpp]
```C++
#include "bstree.h"
#include <iostream>

using namespace std;

bool isEmpty(BinTree pohon) {
    if (pohon == Nil) {
        return true;
    } else {
        return false;
    }
}

void createTree(BinTree &pohon) {
    pohon = Nil;
}

node alokasi(int x) {
    node nodeBaru = new BST;
    nodeBaru->info = x;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void insertNode(BinTree &pohon, node nodeBaru) {
    if (pohon == Nil) {
        pohon = nodeBaru;
    } else if (nodeBaru->info < pohon->info) {
        insertNode(pohon->left, nodeBaru);
    } else if (nodeBaru->info > pohon->info) {
        insertNode(pohon->right, nodeBaru);
    }
}

node findNode(int x, BinTree pohon) {
    if (pohon == Nil) {
        return Nil;
    } else if (x < pohon->info) {
        return findNode(x, pohon->left);
    } else if (x > pohon->info) {
        return findNode(x, pohon->right);
    } else {
        return pohon;
    }
}

void inOrder(BinTree pohon) {
    if (pohon == Nil) {
        return;
    }
    inOrder(pohon->left);
    cout << pohon->info << " - ";
    inOrder(pohon->right);
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "bstree.h"

using namespace std;

int main() {
    cout << "Hello World!" << endl;
    BinTree root = Nil;
    insertNode(root, alokasi(1));
    insertNode(root, alokasi(2));
    insertNode(root, alokasi(6));
    insertNode(root, alokasi(4));
    insertNode(root, alokasi(5));
    insertNode(root, alokasi(3));
    insertNode(root, alokasi(6));
    insertNode(root, alokasi(7));
    inOrder(root);
    cout << endl;
    
    return 0;
}
```

### Output Unguided 1 :

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan10_modul10/output1-unguided1-modul10.png)

Kode ini mengimplementasikan struktur data Binary Search Tree (BST) dengan operasi dasar seperti pembuatan tree, alokasi node, penyisipan node, pencarian node, dan traversal in-order. Struktur BST memungkinkan data disimpan dalam bentuk pohon biner terurut di mana setiap node memiliki nilai yang lebih besar dari node di cabang kiri dan lebih kecil dari node di cabang kanan. Fungsi inOrder melakukan traversal dengan mengunjungi node secara berurutan dari kiri ke akar ke kanan, menghasilkan output data dalam urutan ascending. 

### 2. ![Screenshot Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan10_modul10/unguided2-modul10.png)

#### [bstree.h]
```C++
#ifndef BSTREE_H
#define BSTREE_H
#define Nil NULL

#include <iostream>
using namespace std;

typedef struct BST *node;

struct BST {
    int info;
    node left;
    node right;
};

typedef node BinTree;

bool isEmpty(BinTree pohon);
void createTree(BinTree &pohon);
node alokasi(int x);
void insertNode(BinTree &pohon, node nodeBaru);
node findNode(int x, BinTree pohon);
void inOrder(BinTree pohon);
int hitungKedalaman(BinTree pohon, int awal);
int hitungTotalInfo(BinTree pohon, int awal);
int hitungJumlahNode(BinTree pohon);

#endif
```

#### [bstree.cpp]
```C++
#include "bstree.h"
#include <iostream>

using namespace std;

bool isEmpty(BinTree pohon) {
    if (pohon == Nil) {
        return true;
    } else {
        return false;
    }
}

void createTree(BinTree &pohon) {
    pohon = Nil;
}

node alokasi(int x) {
    node nodeBaru = new BST;
    nodeBaru->info = x;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void insertNode(BinTree &pohon, node nodeBaru) {
    if (pohon == Nil) {
        pohon = nodeBaru;
    } else if (nodeBaru->info < pohon->info) {
        insertNode(pohon->left, nodeBaru);
    } else if (nodeBaru->info > pohon->info) {
        insertNode(pohon->right, nodeBaru);
    }
}

node findNode(int x, BinTree pohon) {
    if (pohon == Nil) {
        return Nil;
    } else if (x < pohon->info) {
        return findNode(x, pohon->left);
    } else if (x > pohon->info) {
        return findNode(x, pohon->right);
    } else {
        return pohon;
    }
}

void inOrder(BinTree pohon) {
    if (pohon == Nil) {
        return;
    }
    inOrder(pohon->left);
    cout << pohon->info << " - ";
    inOrder(pohon->right);
}

int hitungKedalaman(BinTree pohon, int awal) {
    if (pohon == Nil) {
        return awal;
    }
    int kedalamanKiri = hitungKedalaman(pohon->left, awal + 1);
    int kedalamanKanan = hitungKedalaman(pohon->right, awal + 1);
    
    if (kedalamanKiri > kedalamanKanan) {
        return kedalamanKiri;
    } else {
        return kedalamanKanan;
    }
}

int hitungTotalInfo(BinTree pohon, int awal) {
    if (pohon == Nil) {
        return 0;
    }
    return pohon->info + hitungTotalInfo(pohon->left, awal) + hitungTotalInfo(pohon->right, awal);
}

int hitungJumlahNode(BinTree pohon) {
    if (pohon == Nil) {
        return 0;
    }
    return 1 + hitungJumlahNode(pohon->left) + hitungJumlahNode(pohon->right);
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "bstree.h"

using namespace std;

int main() {
    cout << "Hello World!" << endl;
    BinTree root = Nil;
    insertNode(root, alokasi(1));
    insertNode(root, alokasi(2));
    insertNode(root, alokasi(6));
    insertNode(root, alokasi(4));
    insertNode(root, alokasi(5));
    insertNode(root, alokasi(3));
    insertNode(root, alokasi(6));
    insertNode(root, alokasi(7));
    inOrder(root);
    cout << "\n";
    cout << "kedalaman : " << hitungKedalaman(root, 0) << endl;
    cout << "jumlah Node : " << hitungJumlahNode(root) << endl;
    cout << "total : " << hitungTotalInfo(root, 0) << endl;
    
    return 0;
}
```

### Output Unguided 2 :

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan10_modul10/output1-unguided2-modul10.png)

Kode ini mengimplementasikan Binary Search Tree dengan penambahan fungsi analisis tree seperti menghitung kedalaman, jumlah node, dan total semua nilai dalam tree. Traversal in-order menghasilkan data terurut ascending. Fungsi hitungKedalaman menghitung tingkat maksimal dari root ke leaf, hitungJumlahNode menghitung total node dalam tree, dan hitungTotalInfo menjumlahkan semua nilai info dalam tree. Program ini mendemonstrasikan operasi insert, traversal, dan analisis struktur BST.

### 3. ![Screenshot Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan10_modul10/unguided3-modul10.png)

#### [bstree.h]
```C++
#ifndef BSTREE_H
#define BSTREE_H
#define Nil NULL

#include <iostream>
using namespace std;

typedef struct BST *node;

struct BST {
    int info;
    node left;
    node right;
};

typedef node BinTree;

bool isEmpty(BinTree pohon);
void createTree(BinTree &pohon);
node alokasi(int x);
void insertNode(BinTree &pohon, node nodeBaru);
node findNode(int x, BinTree pohon);
void inOrder(BinTree pohon);
void preOrder(BinTree pohon);
void postOrder(BinTree pohon);
int hitungKedalaman(BinTree pohon, int awal);
int hitungTotalInfo(BinTree pohon, int awal);
int hitungJumlahNode(BinTree pohon);

#endif
```

#### [bstree.cpp]
```C++
#include "bstree.h"
#include <iostream>

using namespace std;

bool isEmpty(BinTree pohon) {
    if (pohon == Nil) {
        return true;
    } else {
        return false;
    }
}

void createTree(BinTree &pohon) {
    pohon = Nil;
}

node alokasi(int x) {
    node nodeBaru = new BST;
    nodeBaru->info = x;
    nodeBaru->left = Nil;
    nodeBaru->right = Nil;
    return nodeBaru;
}

void insertNode(BinTree &pohon, node nodeBaru) {
    if (pohon == Nil) {
        pohon = nodeBaru;
    } else if (nodeBaru->info < pohon->info) {
        insertNode(pohon->left, nodeBaru);
    } else if (nodeBaru->info > pohon->info) {
        insertNode(pohon->right, nodeBaru);
    }
}

node findNode(int x, BinTree pohon) {
    if (pohon == Nil) {
        return Nil;
    } else if (x < pohon->info) {
        return findNode(x, pohon->left);
    } else if (x > pohon->info) {
        return findNode(x, pohon->right);
    } else {
        return pohon;
    }
}

void inOrder(BinTree pohon) {
    if (pohon == Nil) {
        return;
    }
    inOrder(pohon->left);
    cout << pohon->info << " - ";
    inOrder(pohon->right);
}

void preOrder(BinTree pohon) {
    if (pohon == Nil) {
        return;
    }
    cout << pohon->info << " - ";
    preOrder(pohon->left);
    preOrder(pohon->right);
}

void postOrder(BinTree pohon) {
    if (pohon == Nil) {
        return;
    }
    postOrder(pohon->left);
    postOrder(pohon->right);
    cout << pohon->info << " - ";
}

int hitungKedalaman(BinTree pohon, int awal) {
    if (pohon == Nil) {
        return awal;
    }
    int kedalamanKiri = hitungKedalaman(pohon->left, awal + 1);
    int kedalamanKanan = hitungKedalaman(pohon->right, awal + 1);
    
    if (kedalamanKiri > kedalamanKanan) {
        return kedalamanKiri;
    } else {
        return kedalamanKanan;
    }
}

int hitungTotalInfo(BinTree pohon, int awal) {
    if (pohon == Nil) {
        return 0;
    }
    return pohon->info + hitungTotalInfo(pohon->left, awal) + hitungTotalInfo(pohon->right, awal);
}

int hitungJumlahNode(BinTree pohon) {
    if (pohon == Nil) {
        return 0;
    }
    return 1 + hitungJumlahNode(pohon->left) + hitungJumlahNode(pohon->right);
}
```

#### [main.cpp]
```C++
#include <iostream>
#include "bstree.h"

using namespace std;

int main() {
    cout << "Binary Search Tree Pre-Order dan Post-Order" << endl;
    BinTree root = Nil;
    
    insertNode(root, alokasi(6));
    insertNode(root, alokasi(4));
    insertNode(root, alokasi(7));
    insertNode(root, alokasi(2));
    insertNode(root, alokasi(5));
    insertNode(root, alokasi(1));
    insertNode(root, alokasi(3));
    
    cout << "\nIn-Order Traversal: ";
    inOrder(root);
    cout << "\n" << endl;
    
    cout << "Pre-Order Traversal: ";
    preOrder(root);
    cout << "\n" << endl;
    
    cout << "Post-Order Traversal: ";
    postOrder(root);
    cout << "\n" << endl;
    
    return 0;
}
```

### Output Unguided 3 :

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan10_modul10/output1-unguided3-modul10.png)

Kode ini mengimplementasikan Binary Search Tree dengan tiga metode traversal yang berbeda untuk mengunjungi setiap node dalam tree. Traversal In-Order (left-root-right) menghasilkan output terurut ascending, Pre-Order (root-left-right) mengunjungi root terlebih dahulu diikuti anak kiri dan kanan, dan Post-Order (left-right-root) mengunjungi node setelah kedua anak dikunjungi. Program mendemonstrasikan bagaimana tiga metode traversal yang berbeda menghasilkan urutan output yang berbeda meskipun struktur tree sama, memberikan fleksibilitas dalam pemrosesan data BST sesuai kebutuhan aplikasi.

## Kesimpulan
Pohon (tree) merupakan salah satu struktur data non-linier yang paling fundamental dan fleksibel dalam ilmu komputer, dengan aplikasi yang sangat luas di berbagai bidang seperti database, sistem file, compiler, dan machine learning.

Berbagai jenis tree (Binary Search Tree, AVL Tree, Red-Black Tree, B-Tree, dan lainnya) telah dikembangkan untuk mengoptimalkan operasi spesifik dan memenuhi kebutuhan performa yang berbeda-beda. Pemilihan jenis tree yang tepat sangat krusial untuk mencapai efisiensi optimal dalam sebuah sistem.

Konsep keseimbangan (balancing) merupakan faktor kunci yang membedakan antara tree yang efisien dengan tree yang tidak efisien. Self-balancing trees seperti AVL dan Red-Black Tree menjamin kompleksitas logaritmik untuk operasi dasar, yang tidak dapat dijamin oleh binary search tree biasa dalam kasus terburuk.

Implementasi tree memerlukan pemahaman mendalam tentang traversal, insertion, deletion, dan operasi khusus seperti rotasi. Pemahaman ini sangat penting untuk mengimplementasikan variasi tree yang lebih kompleks dengan tepat.

Penelitian terbaru dalam bidang tree structures terus berkembang dengan fokus pada optimisasi cache-locality, concurrent access pada multi-processor systems, dan aplikasi tree dalam big data analytics. Teknologi dan algoritma baru terus dikembangkan untuk meningkatkan efisiensi tree dalam menangani data yang semakin kompleks dan berskala besar.

Pohon tetap menjadi pilihan utama dalam perancangan sistem yang membutuhkan akses data cepat, terstruktur hierarki, dan efisiensi ruang yang baik dalam berbagai kondisi operasional.

## Referensi
[1] D. E. Knuth, "The Art of Computer Programming, Vol. 1: Fundamental Algorithms," 3rd ed. Reading, MA, USA: Addison-Wesley, 1997.

<br>[2] T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, "Introduction to Algorithms," 3rd ed. Cambridge, MA, USA: MIT Press, 2009.

<br>[3] G. M. Adelson-Velsky and E. M. Landis, "An algorithm for the organization of information," Proceedings of the USSR Academy of Sciences, vol. 146, pp. 263-266, 1962.

<br>[4] R. Bayer and M. C. McCreight, "Organization and maintenance of large ordered indices," Acta Informatica, vol. 1, no. 3, pp. 173-189, 1972.

<br>[5] R. B. Sedgewick and K. Wayne, "Algorithms, 4th ed." Boston, MA, USA: Pearson, 2011.

<br>[6] L. J. Guibas and R. Sedgewick, "A dichromatic framework for balanced trees," in Proceedings of the 19th Annual Symposium on Foundations of Computer Science, 1978, pp. 8-21.

<br>[7] S. Nakamura, "Applied Numerical Methods with Software," Englewood Cliffs, NJ, USA: Prentice Hall, 1991.

<br>[8] W. Pugh, "Skip lists: A probabilistic alternative to balanced trees," Communications of the ACM, vol. 33, no. 6, pp. 668-676, 1990.

<br>[9] C. Okasaki, "Purely Functional Data Structures," Cambridge, UK: Cambridge University Press, 1998.

<br>[10] M. A. Weiss, "Data Structures and Algorithm Analysis in C++," 4th ed. Boston, MA, USA: Pearson, 2013.
