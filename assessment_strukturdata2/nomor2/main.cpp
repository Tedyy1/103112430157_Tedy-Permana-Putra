#include "mll.h"

int main() {
    ListParent L;  
    createListParent(L);
    
    adrParent P1 = alokasiNodeParent("G004", "Romance");
    insertFirstParent(L, P1);
    adrParent P2 = alokasiNodeParent("G003", "Horror");
    insertFirstParent(L, P2);
    adrParent P3 = alokasiNodeParent("G002", "Comedy");
    insertFirstParent(L, P3);
    adrParent P4 = alokasiNodeParent("G001", "Action");
    insertFirstParent(L, P4);

    adrChild C1 = alokasiNodeChild("FA001", "The Raid", 101, 2011, 7.6);
    insertLastChild(P4, C1);
    adrChild C2 = alokasiNodeChild("FC001", "Agak Laen", 119, 2024, 8.0);
    insertLastChild(P3, C2);
    adrChild C3 = alokasiNodeChild("FC002", "My Stupid Boss", 108, 2016, 6.8);
    insertLastChild(P3, C3);
    adrChild C4 = alokasiNodeChild("FH001", "Pengabdi Setan", 107, 2017, 8.4);
    insertLastChild(P2, C4);
    adrChild C5 = alokasiNodeChild("FR001", "Habibie & Ainun", 118, 2012, 7.6);
    insertLastChild(P1, C5);
    adrChild C6 = alokasiNodeChild("FR002", "Dilan 1990", 110, 2018, 6.6);
    insertLastChild(P1, C6);

    cout << "3) printStrukturMLL() (pastikan output struktur MLL sesuai dengan gambar MLL diatas)" << endl;
    cout << "ekspektasi output :" << endl;
    printStrukturMLL(L);
    cout << endl;

    searchFilmByRatingRange(L, 8.0, 8.5);

    cout << "5) deleteAfterParent(), delete node G002 (berarti node prev nya adalah G001)" << endl;
    deleteAfterParent(L, P4); 
    cout << "(Proses delete selesai)\n" << endl;

    cout << "6) printStrukturMLL() (pastikan node yang tadi dihapus sudah tidak ada dalam struktur MLL)" << endl;
    cout << "ekspektasi output :" << endl;
    printStrukturMLL(L);

    return 0;
}