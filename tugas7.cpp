#include <iostream>
using namespace std;

struct InfoType {
    char pekerjaan;
    int waktu;
    int dikerjakan;
};

struct ElmTugas;
typedef ElmTugas* address;

struct ElmTugas {
    InfoType info;
    address next;
};

struct AntrianTugas {
    address Head;
    address Tail;
};

void createQueue(AntrianTugas &Q) {
    Q.Head = NULL;
    Q.Tail = NULL;
}

address createElm(char id, int w) {
    address P = new ElmTugas;
    P->info.pekerjaan = id;
    P->info.waktu = w;
    P->info.dikerjakan = 0;
    P->next = NULL;
    return P;
}

void TambahTugas(AntrianTugas &Q, address P){
    if(Q.Head == NULL){
        Q.Head = P;
        Q.Tail = P;
        P->next = P;
    } else {
        P->next = Q.Head;
        Q.Tail->next = P;
        Q.Tail = P;
    }
}

void HapusTugas(AntrianTugas &Q, address &P){
    if(Q.Head == NULL){
        P = NULL;
        return;
    }
    if(Q.Head == Q.Tail){
        P = Q.Head;
        Q.Head = NULL;
        Q.Tail = NULL;
    } else {
        P = Q.Head;
        Q.Head = Q.Head->next;
        Q.Tail->next = Q.Head;
    }
    P->next = NULL;
}

bool semuaFinished(AntrianTugas Q){
    if(Q.Head == NULL) return true;
    address P = Q.Head;
    do{
        if(P->info.dikerjakan < P->info.waktu) return false;
        P = P->next;
    }while(P != Q.Head);
    return true;
}

void DailyTask(AntrianTugas &Q){
    int total = 0;
    while(!semuaFinished(Q)){
        address P;
        HapusTugas(Q,P);

        P->info.dikerjakan++;
        total++;

        if(P->info.dikerjakan < P->info.waktu){
            TambahTugas(Q,P);
        } else {
            // finished : tidak masuk antrian lagi
        }
    }
    cout << "Total = " << total << " jam" << endl;
}

int main(){
    AntrianTugas Q;
    createQueue(Q);

    TambahTugas(Q, createElm('A',3));
    TambahTugas(Q, createElm('B',2));
    TambahTugas(Q, createElm('C',5));
    TambahTugas(Q, createElm('D',1));
    TambahTugas(Q, createElm('E',4));
    TambahTugas(Q, createElm('F',2));
    TambahTugas(Q, createElm('G',3));
    TambahTugas(Q, createElm('H',2));

    DailyTask(Q);

    return 0;
}
