# <h1 align="center">Laporan Praktikum Modul 14 - GRAPH </h1>
<p align="center">Tedy Permana Putra - 103112430157</p>

## Dasar Teori

### 1. Definisi dan Struktur Dasar
Dalam konteks matematika dan ilmu komputer, graph adalah struktur matematika yang digunakan untuk memodelkan hubungan antara objek-objek diskrit. Graph terdiri dari dua himpunan utama:
- Vertex/V: Titik-titik atau simpul yang merepresentasikan objek.
- Edge/E: Hubungan atau garis yang menghubungkan dua simpul.

Secara formal, graph didefinisikan sebagai pasangan himpunan G = (V, E), di mana V adalah himpunan simpul tidak kosong dan E adalah himpunan sisi yang menghubungkan pasangan simpul dalam V.

Dalam graph:
- Undirected Graph memiliki sisi tanpa arah. 
- Directed Graph (Digraph) memiliki sisi yang memiliki arah tertentu. 
- Simple Graph tidak memiliki sisi ganda atau loop.

### 2. Terminologi Dasar
Beberapa istilah penting dalam teori graf:
- Vertex (simpul) — unit dasar pada graph.
- Edge (sisi) — koneksi antara simpul.
- Degree — jumlah sisi yang menempel pada sebuah simpul.
- Connectiviy — menentukan apakah setiap simpul dalam graph dapat saling dijangkau melalui jalur tertentu.


### 3. Aplikasi Teori Graf
Teori graf bukan hanya abstrak tetapi memiliki banyak penerapan, antara lain dalam:
- Desain jaringan komunikasi seperti routing data dan struktur jaringan. 
- Analisis jejaring sosial, untuk memetakan hubungan antar entitas. 
- Optimisasi jalur terpendek (misalnya Dijkstra) dalam graph. 
- Pengaturan sistem transportasi dan jaringan listrik. 

## Guided 

### 1. 

#### [graph.h]
```C++
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>

using namespace std;

typedef char infoGraph;
typedef struct ElmNode *adrNode;
typedef struct ElmEdge *adrEdge;

struct ElmNode {
    infoGraph info;
    int visited;
    adrEdge firstEdge;
    adrNode Next;
};

struct ElmEdge {
    adrNode Node;
    adrEdge Next;
};

struct Graph {
    adrNode First;
};

void createGraph(Graph &G);
adrNode AlokasiNode(infoGraph data);
adrEdge AlokasiEdge(adrNode nodeTujuan);

void InsertNode(Graph &G, infoGraph data);
adrNode FindNode(Graph G, infoGraph data);
void ConnectNode(Graph &G, infoGraph info1, infoGraph info2);
void DisconnectNode(adrNode node1, adrNode node2);
void DeleteNode(Graph &G, infoGraph X);

void PrintInfoGraph(Graph G);
void ResetVisited(Graph &G);
void PrintBFS(Graph G, infoGraph StartInfo);
void PrintDFS(Graph G, infoGraph StartInfo);

#endif
```

#### [graph.cpp]
```C++
#include "graph.h"
#include <iostream>
#include <queue> //library queue untuk BFS
#include <stack> //library stack untuk DFS

using namespace std;

//prosedur untuk mengeset first dari graph sebagai NULL
void CreateGraph(Graph &G) {
    G.First = NULL;
}

//alokasi Node baru
adrNode AlokasiNode(infoGraph data) {
    adrNode nodeBaru = new ElmNode;
    nodeBaru->info = data;
    nodeBaru->visited = 0; //isinya 0/1
    nodeBaru->firstEdge = NULL;
    nodeBaru->Next = NULL;
    return nodeBaru;
}

//alokasi Edge baru
adrEdge AlokasiEdge(adrNode nodeTujuan) {
    adrEdge edgeBaru = new ElmEdge;
    edgeBaru->Node = nodeTujuan;
    edgeBaru->Next = NULL;
    return edgeBaru;
}

//Menambahkan Node ke dalam Graph
void InsertNode(Graph &G, infoGraph data) {
    adrNode nodeBaru = AlokasiNode(data);
    if (G.First == NULL) {
        G.First = nodeBaru;
    } else {
        //konsepnya insert last
        adrNode nodeBantu = G.First;
        while (nodeBantu->Next != NULL) {
            nodeBantu = nodeBantu->Next;
        }
        nodeBantu->Next = nodeBaru;
    }
}

//function untuk mencari alamat Node berdasarkan infonya
adrNode FindNode(Graph G, infoGraph data) {
    adrNode nodeBantu = G.First;
    while (nodeBantu != NULL) {
        if (nodeBantu->info == data) {
            return nodeBantu;
        }
        nodeBantu = nodeBantu->Next;
    }
    return NULL;
}

//prosedur untuk menghubungkan dua Node (Undirected Graph)
void ConnectNode(Graph &G, infoGraph info1, infoGraph info2) {
    adrNode node1 = FindNode(G, info1);
    adrNode node2 = FindNode(G, info2);

    if (node1 != NULL && node2 != NULL) {
        //Hubungkan node1 ke node2
        adrEdge Edge1 = AlokasiEdge(node2);
        Edge1->Next = node1->firstEdge; // Insert First pada list edge
        node1->firstEdge = Edge1;

        //Hubungkan node2 ke node1 (Karena Undirected/Bolak-balik)
        adrEdge Edge2 = AlokasiEdge(node1);
        Edge2->Next = node2->firstEdge;
        node2->firstEdge = Edge2;
    } else {
        cout << "Node tidak ditemukan!" << endl;
    }
}

//prosedur untuk memutuskan hubungan dua node
void DisconnectNode(adrNode node1, adrNode node2) {
    if (node1 != NULL && node2 != NULL) {
        adrEdge edgeBantu = node1->firstEdge;
        adrEdge PrevE = NULL;

        //Cari edge yang mengarah ke node2 di dalam list milik node1
        while (edgeBantu != NULL && edgeBantu->Node != node2) {
            PrevE = edgeBantu;
            edgeBantu = edgeBantu->Next;
        }

        if (edgeBantu != NULL) { //jika Edge ditemukan
            if (PrevE == NULL) {
                //Hapus edge pertama
                node1->firstEdge = edgeBantu->Next;
            } else {
                //Hapus edge di tengah/akhir
                PrevE->Next = edgeBantu->Next;
            }
            delete edgeBantu;
        }
    }
}

//prosedur untuk menghapus Node X beserta semua edge yang berhubungan dengannya
void DeleteNode(Graph &G, infoGraph X) {
    //1. Cari Node yang akan dihapus (nodeHapus)
    adrNode nodeHapus = FindNode(G, X);
    if (nodeHapus == NULL) {
        cout << "Node tidak ditemukan." << endl;
        return;
    }

    //2. Hapus semua Edge yang MENGARAH ke nodeHapus (Incoming Edges)
    //cek setiap node di graph, apakah punya edge ke nodeHapus
    adrNode nodeLainnya = G.First;
    while (nodeLainnya != NULL) {
        DisconnectNode(nodeLainnya, nodeHapus); //putus hubungan nodeLainnya ke nodeHapus
        nodeLainnya = nodeLainnya->Next;
    }

    //3. Hapus semua Edge yang KELUAR dari nodeHapus (Outgoing Edges)
    //Deallokasi list edge milik nodeHapus
    adrEdge edgeBantu = nodeHapus->firstEdge;
    while (edgeBantu != NULL) {
        adrEdge tempE = edgeBantu;
        edgeBantu = edgeBantu->Next;
        delete tempE;
    }
    nodeHapus->firstEdge = NULL;

    //4. Hapus nodeHapus dari List Utama Graph
    if (G.First == nodeHapus) {
        //jika nodeHapus di awal
        G.First = nodeHapus->Next;
    } else {
        //jika nodeHapus di tengah/akhir
        adrNode nodeBantu = G.First;
        while (nodeBantu->Next != nodeHapus) {
            nodeBantu = nodeBantu->Next;
        }
        nodeBantu->Next = nodeHapus->Next;
    }

    //5. delete nodeHapus
    delete nodeHapus;
}

//Menampilkan isi Graph (Adjacency List) 
void PrintInfoGraph(Graph G) {
    adrNode nodeBantu = G.First;
    while (nodeBantu != NULL) {
        cout << "Node " << nodeBantu->info << " terhubung ke: ";
        adrEdge edgeBantu = nodeBantu->firstEdge;
        while (edgeBantu != NULL) {
            cout << edgeBantu->Node->info << " "; //Akses info dari node tujuan
            edgeBantu = edgeBantu->Next;
        }
        cout << endl;
        nodeBantu = nodeBantu->Next;
    }
}

//Reset status visited sebelum traversal
void ResetVisited(Graph &G) {
    adrNode nodeReset = G.First;
    while (nodeReset != NULL) {
        nodeReset->visited = 0;
        nodeReset = nodeReset->Next;
    }
}

//traversal Breadth First Search / BFS (Menggunakan Queue)
void PrintBFS(Graph G, infoGraph StartInfo) {
    ResetVisited(G);
    adrNode StartNode = FindNode(G, StartInfo);
    
    if (StartNode == NULL) return;

    queue<adrNode> Qyu;
    
    //Enqueue start
    Qyu.push(StartNode);
    StartNode->visited = 1;

    cout << "BFS Traversal: ";
    while (!Qyu.empty()) {
        adrNode nodeBantu = Qyu.front();
        Qyu.pop();
        cout << nodeBantu->info << " - ";

        //Cek semua tetangga atau edge nya
        adrEdge edgeBantu = nodeBantu->firstEdge;
        while (edgeBantu != NULL) {
            if (edgeBantu->Node->visited == 0) {
                edgeBantu->Node->visited = 1;
                Qyu.push(edgeBantu->Node);
            }
            edgeBantu = edgeBantu->Next;
        }
    }
    cout << endl;
}

//Traversal Depth First Search / DFS (Menggunakan Stack)
void PrintDFS(Graph G, infoGraph StartInfo) {
    ResetVisited(G);
    adrNode StartNode = FindNode(G, StartInfo);
    
    if (StartNode == NULL) return;

    stack<adrNode> Stak;
    
    Stak.push(StartNode);

    cout << "DFS Traversal: ";
    while (!Stak.empty()) {
        adrNode nodeBantu = Stak.top();
        Stak.pop();

        if (nodeBantu->visited == 0) {
            nodeBantu->visited = 1;
            cout << nodeBantu->info << " - ";

            //masukkan tetangga ke stack
            adrEdge edgeBantu = nodeBantu->firstEdge;
            while (edgeBantu != NULL) {
                if (edgeBantu->Node->visited == 0) {
                    Stak.push(edgeBantu->Node);
                }
                edgeBantu = edgeBantu->Next;
            }
        }
    }
    cout << endl;
}
```

#### [main.cpp]
```C++
#include "graph.h"
#include <iostream>
#include <queue> //library queue untuk BFS
#include <stack> //library stack untuk DFS
using namespace std;

int main() {
    Graph G;
    CreateGraph(G);

    InsertNode(G, 'A');
    InsertNode(G, 'B');
    InsertNode(G, 'C');
    InsertNode(G, 'D');
    InsertNode(G, 'E');
    InsertNode(G, 'F');

    ConnectNode(G, 'A', 'B');
    ConnectNode(G, 'A', 'D');
    ConnectNode(G, 'B', 'C');
    ConnectNode(G, 'D', 'C');
    ConnectNode(G, 'B', 'E');
    ConnectNode(G, 'C', 'E');
    ConnectNode(G, 'C', 'F');
    ConnectNode(G, 'E', 'F');

    cout <<  "=== REPRESENTASI ADJACENCY LIST ===" << endl;
    PrintInfoGraph(G);
    cout << endl;

    cout << "=== HASIL TRAVERSAL ===" << endl;
    PrintBFS(G, 'A');
    PrintDFS(G, 'A');
    cout << endl;

    cout << "=== HAPUS NODE E ===" << endl;
    DeleteNode(G, 'E');
    if(FindNode(G, 'E') == NULL) {
        cout << "Node E berhasil terhapus" << endl;
    } else {
        cout << "Node E tidak berhasil terhapus" << endl;
    }
    cout << endl;

    cout <<  "=== REPRESENTASI ADJACENCY LIST ===" << endl;
    PrintInfoGraph(G);
    cout << endl;

    cout << "=== HASIL TRAVERSAL ===" << endl;
    PrintBFS(G, 'A');
    PrintDFS(G, 'A');

    return 0;
}
```

## Unguided

### 1. ![Screenshot Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan14_modul14/unguided1-modul14.png)


#### [MultiLL.h]
```C++
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

typedef char infoGraph;

struct ElementNode;
struct ElementEdge;

typedef ElementNode* addressNode;
typedef ElementEdge* addressEdge;

struct ElementNode {
    infoGraph info;
    int visited;
    addressEdge firstEdge;
    addressNode next;
};

struct ElementEdge {
    addressNode node;
    addressEdge next;
};

struct Graph {
    addressNode first;
};

void CreateGraph(Graph &graph);
void InsertNode(Graph &graph, infoGraph value);
addressNode FindNode(Graph graph, infoGraph value);
void ConnectNode(addressNode firstNode, addressNode secondNode);
void PrintInfoGraph(Graph graph);

#endif
```

#### [MultiLL.cpp]
```C++
#include "graph.h"
#include <iostream>
using namespace std;

void CreateGraph(Graph &graph) {
    graph.first = nullptr;
}

void InsertNode(Graph &graph, infoGraph value) {
    addressNode newNode = new ElementNode;
    newNode->info = value;
    newNode->visited = 0;
    newNode->firstEdge = nullptr;
    newNode->next = nullptr;

    if (graph.first == nullptr) {
        graph.first = newNode;
    } else {
        addressNode temp = graph.first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

addressNode FindNode(Graph graph, infoGraph value) {
    addressNode temp = graph.first;
    while (temp != nullptr) {
        if (temp->info == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void ConnectNode(addressNode firstNode, addressNode secondNode) {
    addressEdge newEdge1 = new ElementEdge;
    newEdge1->node = secondNode;
    newEdge1->next = firstNode->firstEdge;
    firstNode->firstEdge = newEdge1;

    addressEdge newEdge2 = new ElementEdge;
    newEdge2->node = firstNode;
    newEdge2->next = secondNode->firstEdge;
    secondNode->firstEdge = newEdge2;
}

void PrintInfoGraph(Graph graph) {
    addressNode tempNode = graph.first;
    while (tempNode != nullptr) {
        std::cout << tempNode->info << " : ";
        addressEdge tempEdge = tempNode->firstEdge;
        while (tempEdge != nullptr) {
            std::cout << tempEdge->node->info << " ";
            tempEdge = tempEdge->next;
        }
        std::cout << std::endl;
        tempNode = tempNode->next;
    }
}
```

#### [main.cpp]
```C++
#include "graph.h"
#include <iostream>
using namespace std;

int main() {
    Graph graph;
    CreateGraph(graph);

    InsertNode(graph, 'A');
    InsertNode(graph, 'B');
    InsertNode(graph, 'C');
    InsertNode(graph, 'D');
    InsertNode(graph, 'E');
    InsertNode(graph, 'F');
    InsertNode(graph, 'G');
    InsertNode(graph, 'H');

    addressNode A = FindNode(graph, 'A');
    addressNode B = FindNode(graph, 'B');
    addressNode C = FindNode(graph, 'C');
    addressNode D = FindNode(graph, 'D');
    addressNode E = FindNode(graph, 'E');
    addressNode F = FindNode(graph, 'F');
    addressNode G = FindNode(graph, 'G');
    addressNode H = FindNode(graph, 'H');

    ConnectNode(A, B);
    ConnectNode(A, C);
    ConnectNode(B, D);
    ConnectNode(B, E);
    ConnectNode(C, F);
    ConnectNode(C, G);
    ConnectNode(D, H);
    ConnectNode(E, H);
    ConnectNode(F, H);
    ConnectNode(G, H);

    PrintInfoGraph(graph);

    return 0;
}
```

##### Output 1
![Screenshot Output Unguided 1_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan14_modul14/output1-unguided1-modul14.png)

Kode ini mengimplementasikan struktur data graph tak berarah (undirected graph) menggunakan adjacency list berbasis pointer, di mana setiap simpul (ElementNode) menyimpan data bertipe karakter, penanda kunjungan (visited), daftar sisi yang terhubung (firstEdge), dan penunjuk ke simpul berikutnya. File graph.cpp berisi fungsi untuk membuat graph, menambahkan simpul ke dalam daftar, mencari simpul berdasarkan nilainya, menghubungkan dua simpul secara dua arah, serta menampilkan isi graph dalam bentuk daftar ketetanggaan. Pada main.cpp, graph dibangun dengan simpul A sampai H, kemudian dihubungkan sesuai relasi yang ditentukan, dan akhirnya struktur graph ditampilkan ke layar.

### 2. Buatlah prosedur untuk menampilkanhasil penelusuran DFS. prosedur PrintDFS (Graph G, adrNode N);prosedur PrintDFS (Graph G, adrNode N);

#### [MultiLL.h]
```C++
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

typedef char infoGraph;

struct ElementNode;
struct ElementEdge;

typedef ElementNode* addressNode;
typedef ElementEdge* addressEdge;

struct ElementNode {
    infoGraph info;
    int visited;
    addressEdge firstEdge;
    addressNode next;
};

struct ElementEdge {
    addressNode node;
    addressEdge next;
};

struct Graph {
    addressNode first;
};

void CreateGraph(Graph &graph);
void InsertNode(Graph &graph, infoGraph value);
addressNode FindNode(Graph graph, infoGraph value);
void ConnectNode(addressNode firstNode, addressNode secondNode);
void PrintInfoGraph(Graph graph);
void ResetVisited(Graph &graph);
void PrintDFS(Graph &graph, addressNode node);

#endif
```

#### [MultiLL.cpp] 
```C++
#include "graph.h"
#include <iostream>
using namespace std;

void CreateGraph(Graph &graph) {
    graph.first = nullptr;
}

void InsertNode(Graph &graph, infoGraph value) {
    addressNode newNode = new ElementNode;
    newNode->info = value;
    newNode->visited = 0;
    newNode->firstEdge = nullptr;
    newNode->next = nullptr;

    if (graph.first == nullptr) {
        graph.first = newNode;
    } else {
        addressNode temp = graph.first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

addressNode FindNode(Graph graph, infoGraph value) {
    addressNode temp = graph.first;
    while (temp != nullptr) {
        if (temp->info == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void ConnectNode(addressNode firstNode, addressNode secondNode) {
    addressEdge newEdge1 = new ElementEdge;
    newEdge1->node = secondNode;
    newEdge1->next = firstNode->firstEdge;
    firstNode->firstEdge = newEdge1;

    addressEdge newEdge2 = new ElementEdge;
    newEdge2->node = firstNode;
    newEdge2->next = secondNode->firstEdge;
    secondNode->firstEdge = newEdge2;
}

void PrintInfoGraph(Graph graph) {
    addressNode tempNode = graph.first;
    while (tempNode != nullptr) {
        std::cout << tempNode->info << " : ";
        addressEdge tempEdge = tempNode->firstEdge;
        while (tempEdge != nullptr) {
            std::cout << tempEdge->node->info << " ";
            tempEdge = tempEdge->next;
        }
        std::cout << std::endl;
        tempNode = tempNode->next;
    }
}

void ResetVisited(Graph &graph) {
    addressNode temp = graph.first;
    while (temp != nullptr) {
        temp->visited = 0;
        temp = temp->next;
    }
}

void PrintDFS(Graph &graph, addressNode node) {
    if (node == nullptr) {
        return;
    }

    node->visited = 1;
    std::cout << node->info << " ";

    addressEdge tempEdge = node->firstEdge;
    while (tempEdge != nullptr) {
        if (tempEdge->node->visited == 0) {
            PrintDFS(graph, tempEdge->node);
        }
        tempEdge = tempEdge->next;
    }
}
```

#### [main.cpp]
```C++
#include "graph.h"
#include <iostream>
using namespace std;

int main() {
    Graph graph;
    CreateGraph(graph);

    InsertNode(graph, 'A');
    InsertNode(graph, 'B');
    InsertNode(graph, 'C');
    InsertNode(graph, 'D');
    InsertNode(graph, 'E');
    InsertNode(graph, 'F');
    InsertNode(graph, 'G');
    InsertNode(graph, 'H');

    addressNode A = FindNode(graph, 'A');
    addressNode B = FindNode(graph, 'B');
    addressNode C = FindNode(graph, 'C');
    addressNode D = FindNode(graph, 'D');
    addressNode E = FindNode(graph, 'E');
    addressNode F = FindNode(graph, 'F');
    addressNode G = FindNode(graph, 'G');
    addressNode H = FindNode(graph, 'H');

    ConnectNode(A, B);
    ConnectNode(A, C);
    ConnectNode(B, D);
    ConnectNode(B, E);
    ConnectNode(C, F);
    ConnectNode(C, G);
    ConnectNode(D, H);
    ConnectNode(E, H);
    ConnectNode(F, H);
    ConnectNode(G, H);

    PrintInfoGraph(graph);

    ResetVisited(graph);
    PrintDFS(graph, A);

    return 0;
}
```

##### Output 1
![Screenshot Output Unguided 2_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan14_modul14/output1-unguided2-modul14.png)

Kode ini mengimplementasikan graph tak berarah (undirected graph) menggunakan adjacency list berbasis pointer, di mana setiap simpul (ElementNode) menyimpan data karakter, status kunjungan (visited), daftar sisi yang terhubung (firstEdge), dan penunjuk ke simpul berikutnya. File graph.cpp menyediakan fungsi untuk membuat graph, menambahkan simpul, mencari simpul tertentu, menghubungkan dua simpul secara dua arah, menampilkan struktur graph dalam bentuk daftar ketetanggaan, serta melakukan penelusuran Depth First Search (DFS) secara rekursif dengan memanfaatkan atribut visited agar simpul tidak dikunjungi berulang. Pada main.cpp, graph dibangun dengan simpul A sampai H, dihubungkan sesuai relasi yang ditentukan, lalu ditampilkan isi graph dan hasil penelusuran DFS yang dimulai dari simpul A.

### 3. Buatlah prosedur untuk menampilkanhasil penelusuran DFS. prosedur PrintBFS (Graph G, adrNode N);

#### [graph.h]
```C++
#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
using namespace std;

typedef char infoGraph;

struct ElementNode;
struct ElementEdge;

typedef ElementNode* addressNode;
typedef ElementEdge* addressEdge;

struct ElementNode {
    infoGraph info;
    int visited;
    addressEdge firstEdge;
    addressNode next;
};

struct ElementEdge {
    addressNode node;
    addressEdge next;
};

struct Graph {
    addressNode first;
};

void CreateGraph(Graph &graph);
void InsertNode(Graph &graph, infoGraph value);
addressNode FindNode(Graph graph, infoGraph value);
void ConnectNode(addressNode firstNode, addressNode secondNode);
void PrintInfoGraph(Graph graph);
void ResetVisited(Graph &graph);
void PrintDFS(Graph &graph, addressNode node);
void PrintBFS(Graph &graph, addressNode node);

#endif
```

#### [graph.cpp]
```C++
#include "graph.h"
#include <queue>
#include <iostream>
using namespace std;

void CreateGraph(Graph &graph) {
    graph.first = nullptr;
}

void InsertNode(Graph &graph, infoGraph value) {
    addressNode newNode = new ElementNode;
    newNode->info = value;
    newNode->visited = 0;
    newNode->firstEdge = nullptr;
    newNode->next = nullptr;

    if (graph.first == nullptr) {
        graph.first = newNode;
    } else {
        addressNode temp = graph.first;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = newNode;
    }
}

addressNode FindNode(Graph graph, infoGraph value) {
    addressNode temp = graph.first;
    while (temp != nullptr) {
        if (temp->info == value) {
            return temp;
        }
        temp = temp->next;
    }
    return nullptr;
}

void ConnectNode(addressNode firstNode, addressNode secondNode) {
    addressEdge newEdge1 = new ElementEdge;
    newEdge1->node = secondNode;
    newEdge1->next = firstNode->firstEdge;
    firstNode->firstEdge = newEdge1;

    addressEdge newEdge2 = new ElementEdge;
    newEdge2->node = firstNode;
    newEdge2->next = secondNode->firstEdge;
    secondNode->firstEdge = newEdge2;
}

void PrintInfoGraph(Graph graph) {
    addressNode tempNode = graph.first;
    while (tempNode != nullptr) {
        std::cout << tempNode->info << " : ";
        addressEdge tempEdge = tempNode->firstEdge;
        while (tempEdge != nullptr) {
            std::cout << tempEdge->node->info << " ";
            tempEdge = tempEdge->next;
        }
        std::cout << std::endl;
        tempNode = tempNode->next;
    }
}

void ResetVisited(Graph &graph) {
    addressNode temp = graph.first;
    while (temp != nullptr) {
        temp->visited = 0;
        temp = temp->next;
    }
}

void PrintDFS(Graph &graph, addressNode node) {
    if (node == nullptr) {
        return;
    }

    node->visited = 1;
    std::cout << node->info << " ";

    addressEdge tempEdge = node->firstEdge;
    while (tempEdge != nullptr) {
        if (tempEdge->node->visited == 0) {
            PrintDFS(graph, tempEdge->node);
        }
        tempEdge = tempEdge->next;
    }
}

void PrintBFS(Graph &graph, addressNode node) {
    if (node == nullptr) {
        return;
    }

    std::queue<addressNode> queueNode;
    node->visited = 1;
    queueNode.push(node);

    while (!queueNode.empty()) {
        addressNode current = queueNode.front();
        queueNode.pop();
        std::cout << current->info << " ";

        addressEdge tempEdge = current->firstEdge;
        while (tempEdge != nullptr) {
            if (tempEdge->node->visited == 0) {
                tempEdge->node->visited = 1;
                queueNode.push(tempEdge->node);
            }
            tempEdge = tempEdge->next;
        }
    }
}
```

#### [main.cpp]
```C++
#include "graph.h"
#include <iostream>
#include <queue>
using namespace std;

int main() {
    Graph graph;
    CreateGraph(graph);

    InsertNode(graph, 'A');
    InsertNode(graph, 'B');
    InsertNode(graph, 'C');
    InsertNode(graph, 'D');
    InsertNode(graph, 'E');
    InsertNode(graph, 'F');
    InsertNode(graph, 'G');
    InsertNode(graph, 'H');

    addressNode A = FindNode(graph, 'A');
    addressNode B = FindNode(graph, 'B');
    addressNode C = FindNode(graph, 'C');
    addressNode D = FindNode(graph, 'D');
    addressNode E = FindNode(graph, 'E');
    addressNode F = FindNode(graph, 'F');
    addressNode G = FindNode(graph, 'G');
    addressNode H = FindNode(graph, 'H');

    ConnectNode(A, B);
    ConnectNode(A, C);
    ConnectNode(B, D);
    ConnectNode(B, E);
    ConnectNode(C, F);
    ConnectNode(C, G);
    ConnectNode(D, H);
    ConnectNode(E, H);
    ConnectNode(F, H);
    ConnectNode(G, H);

    PrintInfoGraph(graph);

    ResetVisited(graph);
    PrintDFS(graph, A);

    std::cout << std::endl;

    ResetVisited(graph);
    PrintBFS(graph, A);

    return 0;
}
```

##### Output 1
![Screenshot Output Unguided 3_1](https://github.com/Tedyy1/103112430157_Tedy-Permana-Putra/blob/main/pertemuan14_modul14/output1-unguided3-modul14.png)

Kode ini mengimplementasikan struktur data graph tak berarah (undirected graph) menggunakan adjacency list berbasis pointer, di mana setiap simpul (ElementNode) menyimpan data (info), penanda kunjungan (visited), daftar sisi (firstEdge), dan penunjuk ke simpul berikutnya, sedangkan sisi (ElementEdge) menyimpan referensi ke simpul tujuan. File graph.cpp berisi fungsi untuk membuat graph, menambah simpul, mencari simpul, menghubungkan dua simpul secara dua arah, menampilkan isi graph, serta melakukan penelusuran DFS (Depth First Search) secara rekursif dan BFS (Breadth First Search) menggunakan queue dengan memanfaatkan atribut visited. Pada main.cpp, graph dibangun dengan simpul A–H, dihubungkan membentuk struktur tertentu, lalu ditampilkan adjacency list-nya, diikuti hasil penelusuran DFS dan BFS mulai dari simpul A.

## Kesimpulan

Teori graf adalah cabang utama dari matematika diskrit yang memodelkan objek serta hubungan antar objek melalui simpul (vertices) dan sisi (edges). 

Struktur dan properti graf memungkinkan pemetaan dan analisis relasi kompleks dalam sistem nyata seperti jaringan komputer, komunikasi, dan transportasi. 

Pengenalan terminologi dasar seperti graf sederhana, graf berarah/ tak berarah, serta derajat simpul menjadi fondasi penting untuk memahami konsep lanjutan seperti optimasi jaringan dan algoritma graf. 

Graph theory menyediakan kerangka kerja untuk menyelesaikan berbagai permasalahan terapan dan teoritis pada jaringan, termasuk menentukan jalur optimal, struktur konektivitas, dan analisis hubungan antar titik. 

## Referensi

[1] R. Diestel, Graph Theory, 5th ed. Berlin, Germany: Springer-Verlag, 2017.

[2] D. B. West, Introduction to Graph Theory, 2nd ed. Upper Saddle River, NJ, USA: Prentice Hall, 2001.

[3] J. A. Bondy and U. S. R. Murty, Graph Theory, New York, NY, USA: Springer, 2008.

[4] T. H. Cormen, C. E. Leiserson, R. L. Rivest, and C. Stein, Introduction to Algorithms, 3rd ed. Cambridge, MA, USA: MIT Press, 2009.

[5] R. L. Graham, D. E. Knuth, and O. Patashnik, Concrete Mathematics: A Foundation for Computer Science, 2nd ed. Boston, MA, USA: Addison-Wesley, 1994.

[6] J. Gross and J. Yellen, Graph Theory and Its Applications, 2nd ed. Boca Raton, FL, USA: CRC Press, 2005.
