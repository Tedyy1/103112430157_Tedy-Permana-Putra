#ifndef MLL_H
#define MLL_H

#include <iostream>
#include <string>

using namespace std;

struct infotypeParent {
    string idGenre;
    string namaGenre;
};

struct infotypeChild {
    string idFilm;
    string judulFilm;
    int durasiFilm;
    int tahunTayang;
    float ratingFilm;
};

typedef struct elmParent* adrParent;
typedef struct elmChild* adrChild;

struct elmChild {
    infotypeChild info;
    adrChild next;
    adrChild prev;
};

struct elmParent {
    infotypeParent info;
    adrParent next;
    adrParent prev;
    adrChild firstChild;
    adrChild lastChild;
};

struct ListParent {
    adrParent first;
    adrParent last;
};

void createListParent(ListParent &L);

adrParent alokasiNodeParent(string id, string nama);
adrChild alokasiNodeChild(string id, string judul, int durasi, int tahun, float rating);

void dealokasiNodeParent(adrParent P);
void dealokasiNodeChild(adrChild C);

void insertFirstParent(ListParent &L, adrParent P);
void insertLastChild(adrParent P, adrChild C);

void hapusListChild(adrParent P);
void deleteAfterParent(ListParent &L, adrParent Prec);

void searchFilmByRatingRange(ListParent L, float minRating, float maxRating);
void printStrukturMLL(ListParent L);

adrParent findParent(ListParent L, string namaGenre);

#endif