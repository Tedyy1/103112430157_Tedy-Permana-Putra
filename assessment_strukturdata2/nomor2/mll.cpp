#include "mll.h"

#include <iostream>
using namespace std;

void createListParent(ListParent &L) {
    L.first = NULL;
    L.last = NULL;
}

adrParent alokasiNodeParent(string id, string nama) {
    adrParent P = new elmParent;
    P->info.idGenre = id;
    P->info.namaGenre = nama;
    P->next = NULL;
    P->prev = NULL;
    P->firstChild = NULL;
    P->lastChild = NULL;
    return P;
}

adrChild alokasiNodeChild(string id, string judul, int durasi, int tahun, float rating) {
    adrChild C = new elmChild;
    C->info.idFilm = id;
    C->info.judulFilm = judul;
    C->info.durasiFilm = durasi;
    C->info.tahunTayang = tahun;
    C->info.ratingFilm = rating;
    C->next = NULL;
    C->prev = NULL;
    return C;
}

void dealokasiNodeParent(adrParent P) {
    delete P;
}

void dealokasiNodeChild(adrChild C) {
    delete C;
}

void insertFirstParent(ListParent &L, adrParent P) {
    if (L.first == NULL) {
        L.first = P;
        L.last = P;
    } else {
        P->next = L.first;
        L.first->prev = P;
        L.first = P;
    }
}

void insertLastChild(adrParent P, adrChild C) {
    if (P->firstChild == NULL) {
        P->firstChild = C;
        P->lastChild = C;
    } else {
        P->lastChild->next = C;
        C->prev = P->lastChild;
        P->lastChild = C;
    }
}

void hapusListChild(adrParent P) {
    adrChild C = P->firstChild;
    while (C != NULL) {
        adrChild temp = C;
        C = C->next;
        dealokasiNodeChild(temp);
    }
    P->firstChild = NULL;
    P->lastChild = NULL;
}

void deleteAfterParent(ListParent &L, adrParent Prec) {
    if (Prec != NULL && Prec->next != NULL) {
        adrParent Del = Prec->next;
        hapusListChild(Del);

        Prec->next = Del->next;
        if (Del->next != NULL) {
            Del->next->prev = Prec;
        } else {
            L.last = Prec;
        }

        dealokasiNodeParent(Del);
    }
}

void searchFilmByRatingRange(ListParent L, float minRating, float maxRating) {
    cout << "4) searchFilmByRatingRange() dengan rentang rating " << minRating << " - " << maxRating << endl;
    cout << "ekspektasi output :" << endl;
    
    adrParent P = L.first;
    int idxParent = 1;
    bool foundAny = false;

    while (P != NULL) {
        adrChild C = P->firstChild;
        int idxChild = 1;
        while (C != NULL) {
            if (C->info.ratingFilm >= minRating && C->info.ratingFilm <= maxRating) {
                foundAny = true;
                cout << "Data Film ditemukan pada list child dari node parent " << P->info.namaGenre << " pada posisi ke-" << idxChild << "!" << endl;
                cout << "--- Data Film (Child) ---" << endl;
                cout << "Judul Film : " << C->info.judulFilm << endl;
                cout << "Posisi dalam list child : posisi ke-" << idxChild << endl;
                cout << "ID Film : " << C->info.idFilm << endl;
                cout << "Durasi Film : " << C->info.durasiFilm << " menit" << endl;
                cout << "Tahun Tayang : " << C->info.tahunTayang << endl;
                cout << "Rating Film : " << C->info.ratingFilm << endl;
                cout << "-------------------------" << endl;
                
                cout << "--- Data Genre (Parent) ---" << endl;
                cout << "ID Genre : " << P->info.idGenre << endl;
                cout << "Posisi dalam list parent : posisi ke-" << idxParent << endl;
                cout << "Nama Genre : " << P->info.namaGenre << endl;
                cout << "==========================================" << endl;
            }
            C = C->next;
            idxChild++;
        }
        P = P->next;
        idxParent++;
    }
    
    if (!foundAny) {
        cout << "Tidak ada film dalam rentang rating tersebut." << endl;
    }
    cout << endl;
}

void printStrukturMLL(ListParent L) {
    adrParent P = L.first;
    int i = 1;
    while (P != NULL) {
        cout << "=== Parent " << i << " ===" << endl;
        cout << "ID Genre : " << P->info.idGenre << endl;
        cout << "Nama Genre : " << P->info.namaGenre << endl;

        adrChild C = P->firstChild;
        int j = 1;
        while (C != NULL) {
            cout << "  - Child " << j << " :" << endl;
            cout << "      ID Film : " << C->info.idFilm << endl;
            cout << "      Judul Film : " << C->info.judulFilm << endl;
            cout << "      Durasi Film : " << C->info.durasiFilm << " menit" << endl;
            cout << "      Tahun Tayang : " << C->info.tahunTayang << endl;
            cout << "      Rating Film : " << C->info.ratingFilm << endl;
            C = C->next;
            j++;
        }
        cout << "------------------------------" << endl;
        P = P->next;
        i++;
    }
}

adrParent findParent(ListParent L, string namaGenre) {
    adrParent P = L.first;
    while (P != NULL) {
        if (P->info.namaGenre == namaGenre) {
            return P;
        }
        P = P->next;
    }
    return NULL;
}