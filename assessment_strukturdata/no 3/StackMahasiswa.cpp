#include "StackMahasiswa.h"

bool isEmpty(StackMahasiswa S) {
    return S.top == -1;
}

bool isFull(StackMahasiswa S) {
    return S.top == MAX_STACK - 1;
}

void createStack(StackMahasiswa& S) {
    S.top = -1;
}

void push(StackMahasiswa& S, Mahasiswa mhs) {
    if (!isFull(S)) {
        S.top++;
        S.data[S.top] = mhs;
    } else {
        cout << "Stack penuh! Tidak bisa menambah data." << endl;
    }
}

Mahasiswa pop(StackMahasiswa& S) {
    Mahasiswa mhs;
    if (!isEmpty(S)) {
        mhs = S.data[S.top];
        S.top--;
        return mhs;
    } else {
        cout << "Stack kosong! Tidak ada data yang bisa dihapus." << endl;
        return mhs;
    }
}

Mahasiswa update(StackMahasiswa S) {
    Mahasiswa mhs;
    int posisi;
    
    if (!isEmpty(S)) {
        cout << "Masukkan posisi yang ingin diupdate (1-" << S.top + 1 << "): ";
        cin >> posisi;
        
        if (posisi >= 1 && posisi <= S.top + 1) {
            int index = S.top - posisi + 1;
            
            cout << "Masukkan nama: ";
            cin.ignore();
            getline(cin, mhs.nama);
            
            cout << "Masukkan NIM: ";
            getline(cin, mhs.nim);
            
            cout << "Masukkan Nilai Tugas: ";
            cin >> mhs.nilaiTugas;
            
            cout << "Masukkan Nilai UTS: ";
            cin >> mhs.nilaiUTS;
            
            cout << "Masukkan Nilai UAS: ";
            cin >> mhs.nilaiUAS;
            
            S.data[index] = mhs;
            return mhs;
        } else {
            cout << "Posisi tidak valid!" << endl;
        }
    } else {
        cout << "Stack kosong!" << endl;
    }
    
    return mhs;
}

void view(StackMahasiswa S) {
    if (isEmpty(S)) {
        cout << "Stack kosong!" << endl;
        return;
    }
    
    cout << "\n=== Data Mahasiswa dalam Stack ===" << endl;
    cout << "---------------------------------" << endl;
    
    for (int i = S.top; i >= 0; i--) {
        cout << "Posisi " << S.top - i + 1 << ":" << endl;
        cout << "  Nama: " << S.data[i].nama << endl;
        cout << "  NIM: " << S.data[i].nim << endl;
        cout << "  Nilai Tugas: " << S.data[i].nilaiTugas << endl;
        cout << "  Nilai UTS: " << S.data[i].nilaiUTS << endl;
        cout << "  Nilai UAS: " << S.data[i].nilaiUAS << endl;
        
        float nilaiAkhir = (S.data[i].nilaiTugas * 0.2) + 
                          (S.data[i].nilaiUTS * 0.4) + 
                          (S.data[i].nilaiUAS * 0.4);
        cout << "  Nilai Akhir: " << nilaiAkhir << endl;
        cout << "---------------------------------" << endl;
    }
}

void searchnilaiakhir(StackMahasiswa S, float minNilaiAkhir, float maxNilaiAkhir) {
    if (isEmpty(S)) {
        cout << "Stack kosong!" << endl;
        return;
    }
    
    bool ditemukan = false;
    
    cout << "\n=== Hasil Pencarian Nilai Akhir (" << minNilaiAkhir << " - " << maxNilaiAkhir << ") ===" << endl;
    cout << "---------------------------------" << endl;
    
    for (int i = S.top; i >= 0; i--) {
        float nilaiAkhir = (S.data[i].nilaiTugas * 0.2) + 
                          (S.data[i].nilaiUTS * 0.4) + 
                          (S.data[i].nilaiUAS * 0.4);
        
        if (nilaiAkhir >= minNilaiAkhir && nilaiAkhir <= maxNilaiAkhir) {
            ditemukan = true;
            cout << "Nama: " << S.data[i].nama << endl;
            cout << "NIM: " << S.data[i].nim << endl;
            cout << "Nilai Akhir: " << nilaiAkhir << endl;
            cout << "Posisi: " << S.top - i + 1 << endl;
            cout << "---------------------------------" << endl;
        }
    }
    
    if (!ditemukan) {
        cout << "Tidak ada data yang sesuai dengan kriteria pencarian." << endl;
    }
}
