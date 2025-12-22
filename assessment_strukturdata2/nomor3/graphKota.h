#ifndef GRAPHKOTA_H
#define GRAPHKOTA_H

#include <iostream>
#include <string>
using namespace std;

typedef struct ElmKota *adrKota;
typedef struct ElmEdge *adrEdge;

struct ElmEdge {
    adrKota kotaTujuan;
    int jarak;
    adrEdge next;
};

struct ElmKota {
    string namaKota;
    int visited;
    adrEdge firstEdge;
    adrKota next;
};

struct GraphKota {
    adrKota first;
};

void createGraph(GraphKota &G);
adrKota alokasiNode(string nama);
adrEdge alokasiEdge(adrKota tujuan, int jarak);
void insertNode(GraphKota &G, adrKota P);
adrKota findNode(GraphKota G, string nama);
void connectNode(GraphKota &G, string kota1, string kota2, int jarak);
void disconnectNode(GraphKota &G, string kota1, string kota2);
void deleteNode(GraphKota &G, string nama);
void printGraph(GraphKota G);

void resetVisited(GraphKota &G);
void printBFS(GraphKota G, string start);
void printDFS(GraphKota G, string start);

#endif
