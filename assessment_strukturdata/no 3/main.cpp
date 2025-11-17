#include "StackMahasiswa.h"

void maxNilaiAkhir(StackMahasiswa S) {
    if (isEmpty(S)) {
        cout << "Stack kosong!" << endl;
        return;
    }
    
    float maxNilai = -1;
    int posisiMax = -1;
    Mahasiswa mhsMax;
    
    for (int i = S.top; i >= 0; i--) {
        float nilaiAkhir = (S.data[i].nilaiTugas * 0.2) + 
                          (S.data[i].nilaiUTS * 0.4) + 
                          (S.data[i].nilaiUAS * 0.4);
        
        if (nilaiAkhir > maxNilai) {
            maxNilai = nilaiAkhir;
            posisiMax = S.top - i + 1;
            mhsMax = S.data[i];
        }
    }
    
    cout << "\n=== Mahasiswa dengan Nilai Akhir Tertinggi ===" << endl;
    cout << "---------------------------------" << endl;
    cout << "Nama: " << mhsMax.nama << endl;
    cout << "NIM: " << mhsMax.nim << endl;
    cout << "Nilai Tugas: " << mhsMax.nilaiTugas << endl;
    cout << "Nilai UTS: " << mhsMax.nilaiUTS << endl;
    cout << "Nilai UAS: " << mhsMax.nilaiUAS << endl;
    cout << "Nilai Akhir: " << maxNilai << endl;
    cout << "Posisi: " << posisiMax << endl;
    cout << "---------------------------------" << endl;
}

int main() {
    StackMahasiswa S;
    createStack(S);
    
    cout << "========== STACK MAHASISWA ==========" << endl;
    cout << "Max Capacity: " << MAX_STACK << endl << endl;
    
    cout << "1. Stack kosong telah dibuat" << endl << endl;
    
    cout << "2. Input data mahasiswa:" << endl;
    
    Mahasiswa mhs1;
    mhs1.nama = "Venti";
    mhs1.nim = "11111";
    mhs1.nilaiTugas = 75.7;
    mhs1.nilaiUTS = 82.1;
    mhs1.nilaiUAS = 65.5;
    push(S, mhs1);
    cout << "   - Data Venti ditambahkan" << endl;
    
    Mahasiswa mhs2;
    mhs2.nama = "Xiao";
    mhs2.nim = "22222";
    mhs2.nilaiTugas = 87.4;
    mhs2.nilaiUTS = 88.9;
    mhs2.nilaiUAS = 81.9;
    push(S, mhs2);
    cout << "   - Data Xiao ditambahkan" << endl;
    
    Mahasiswa mhs3;
    mhs3.nama = "Kazuha";
    mhs3.nim = "33333";
    mhs3.nilaiTugas = 92.3;
    mhs3.nilaiUTS = 88.8;
    mhs3.nilaiUAS = 82.4;
    push(S, mhs3);
    cout << "   - Data Kazuha ditambahkan" << endl;
    
    Mahasiswa mhs4;
    mhs4.nama = "Wanderer";
    mhs4.nim = "44444";
    mhs4.nilaiTugas = 95.5;
    mhs4.nilaiUTS = 85.5;
    mhs4.nilaiUAS = 90.5;
    push(S, mhs4);
    cout << "   - Data Wanderer ditambahkan" << endl;
    
    Mahasiswa mhs5;
    mhs5.nama = "Lynette";
    mhs5.nim = "55555";
    mhs5.nilaiTugas = 77.7;
    mhs5.nilaiUTS = 65.4;
    mhs5.nilaiUAS = 79.9;
    push(S, mhs5);
    cout << "   - Data Lynette ditambahkan" << endl;
    
    Mahasiswa mhs6;
    mhs6.nama = "Chasca";
    mhs6.nim = "66666";
    mhs6.nilaiTugas = 99.9;
    mhs6.nilaiUTS = 93.6;
    mhs6.nilaiUAS = 87.3;
    push(S, mhs6);
    cout << "   - Data Chasca ditambahkan" << endl << endl;
    
    // 3) Tampilkan stack yang sudah diinputkan
    cout << "3. Tampilkan stack yang sudah diinputkan:";
    view(S);
    cout << endl;
    
    // 4) Lakukan pop sebanyak 1x
    cout << "4. Pop data 1x:" << endl;
    Mahasiswa popped = pop(S);
    cout << "   - Data " << popped.nama << " dihapus dari stack" << endl << endl;
    
    // 5) Tampilkan stack yang sudah dilakukan pop 1x
    cout << "5. Tampilkan stack setelah pop 1x:";
    view(S);
    cout << endl;
    
    // 6) Lakukan update data pada posisi ke 3
    cout << "6. Update data pada posisi ke 3:" << endl;
    Mahasiswa updated;
    updated.nama = "Heizou";
    updated.nim = "77777";
    updated.nilaiTugas = 99.9;
    updated.nilaiUTS = 88.8;
    updated.nilaiUAS = 77.7;
    
    // Update manual pada posisi 3 (posisi 1 dari atas = index 4, posisi 2 = index 3, posisi 3 = index 2)
    int posisiUpdate = 3;
    int indexUpdate = S.top - posisiUpdate + 1;
    if (indexUpdate >= 0 && indexUpdate <= S.top) {
        S.data[indexUpdate] = updated;
        cout << "   - Data pada posisi " << posisiUpdate << " diupdate menjadi:" << endl;
        cout << "   - Nama: " << updated.nama << endl;
        cout << "   - NIM: " << updated.nim << endl;
        cout << "   - Nilai Tugas: " << updated.nilaiTugas << endl;
        cout << "   - Nilai UTS: " << updated.nilaiUTS << endl;
        cout << "   - Nilai UAS: " << updated.nilaiUAS << endl << endl;
    }
    
    cout << "7. Tampilkan stack setelah update:";
    view(S);
    cout << endl;
    
    cout << "8. Pencarian data mahasiswa dengan nilai akhir dalam rentang 85.5 - 95.5:" << endl;
    searchnilaiakhir(S, 85.5, 95.5);
    cout << endl;
    
    cout << "=== BAGIAN B ===" << endl;
    maxNilaiAkhir(S);
    
    return 0;
}
