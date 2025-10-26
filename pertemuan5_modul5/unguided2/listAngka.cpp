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
