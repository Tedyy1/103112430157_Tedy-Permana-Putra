#include "graphKota.h"
#include <queue>
#include <stack>

#include <iostream>
using namespace std;

void createGraph(GraphKota &G) {
    G.first = NULL;
}

adrKota alokasiNode(string nama) {
    adrKota P = new ElmKota;
    P->namaKota = nama;
    P->visited = 0;
    P->firstEdge = NULL;
    P->next = NULL;
    return P;
}

adrEdge alokasiEdge(adrKota tujuan, int jarak) {
    adrEdge E = new ElmEdge;
    E->kotaTujuan = tujuan;
    E->jarak = jarak;
    E->next = NULL;
    return E;
}

void insertNode(GraphKota &G, adrKota P) {
    P->next = G.first;
    G.first = P;
}

adrKota findNode(GraphKota G, string nama) {
    adrKota P = G.first;
    while (P != NULL) {
        if (P->namaKota == nama)
            return P;
        P = P->next;
    }
    return NULL;
}

void connectNode(GraphKota &G, string kota1, string kota2, int jarak) {
    adrKota A = findNode(G, kota1);
    adrKota B = findNode(G, kota2);

    if (A != NULL && B != NULL) {
        adrEdge E1 = alokasiEdge(B, jarak);
        E1->next = A->firstEdge;
        A->firstEdge = E1;

        adrEdge E2 = alokasiEdge(A, jarak);
        E2->next = B->firstEdge;
        B->firstEdge = E2;
    }
}

void disconnectNode(GraphKota &G, string kota1, string kota2) {
    adrKota A = findNode(G, kota1);
    adrKota B = findNode(G, kota2);

    if (A && B) {
        adrEdge *p = &A->firstEdge;
        while (*p && (*p)->kotaTujuan != B)
            p = &(*p)->next;
        if (*p) *p = (*p)->next;

        p = &B->firstEdge;
        while (*p && (*p)->kotaTujuan != A)
            p = &(*p)->next;
        if (*p) *p = (*p)->next;
    }
}

void deleteNode(GraphKota &G, string nama) {
    adrKota P = G.first, prev = NULL;

    while (P && P->namaKota != nama) {
        prev = P;
        P = P->next;
    }

    if (!P) return;

    adrKota Q = G.first;
    while (Q) {
        disconnectNode(G, Q->namaKota, nama);
        Q = Q->next;
    }

    if (prev == NULL)
        G.first = P->next;
    else
        prev->next = P->next;

    delete P;
}

void printGraph(GraphKota G) {
    cout << "=== REPRESENTASI ADJACENCY LIST GRAPH ===" << endl;
    adrKota P = G.first;
    while (P) {
        cout << "Node " << P->namaKota << " terhubung ke: ";
        adrEdge E = P->firstEdge;
        while (E) {
            cout << E->kotaTujuan->namaKota
                 << "(" << E->jarak << " KM), ";
            E = E->next;
        }
        cout << endl;
        P = P->next;
    }
}

void resetVisited(GraphKota &G) {
    adrKota P = G.first;
    while (P) {
        P->visited = 0;
        P = P->next;
    }
}

void printBFS(GraphKota G, string start) {
    resetVisited(G);
    queue<adrKota> Q;

    adrKota S = findNode(G, start);
    if (!S) return;

    S->visited = 1;
    Q.push(S);

    cout << "BFS Traversal: ";
    while (!Q.empty()) {
        adrKota P = Q.front(); Q.pop();
        cout << P->namaKota << " - ";

        adrEdge E = P->firstEdge;
        while (E) {
            if (!E->kotaTujuan->visited) {
                E->kotaTujuan->visited = 1;
                Q.push(E->kotaTujuan);
            }
            E = E->next;
        }
    }
    cout << endl;
}

void printDFS(GraphKota G, string start) {
    resetVisited(G);
    stack<adrKota> S;

    adrKota P = findNode(G, start);
    if (!P) return;

    S.push(P);

    cout << "DFS Traversal: ";
    while (!S.empty()) {
        P = S.top(); S.pop();

        if (!P->visited) {
            P->visited = 1;
            cout << P->namaKota << " - ";

            adrEdge E = P->firstEdge;
            while (E) {
                if (!E->kotaTujuan->visited)
                    S.push(E->kotaTujuan);
                E = E->next;
            }
        }
    }
    cout << endl;
}
