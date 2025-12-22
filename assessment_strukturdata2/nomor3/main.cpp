#include "graphKota.h"
#include <iostream>
using namespace std;

int main() {
    GraphKota G;
    createGraph(G);

    insertNode(G, alokasiNode("Jakarta"));
    insertNode(G, alokasiNode("Bogor"));
    insertNode(G, alokasiNode("Depok"));
    insertNode(G, alokasiNode("Bekasi"));
    insertNode(G, alokasiNode("Tangerang"));

    connectNode(G, "Jakarta", "Bogor", 42);
    connectNode(G, "Jakarta", "Depok", 21);
    connectNode(G, "Jakarta", "Bekasi", 16);
    connectNode(G, "Jakarta", "Tangerang", 24);
    connectNode(G, "Bogor", "Bekasi", 60);
    connectNode(G, "Bogor", "Depok", 22);
    connectNode(G, "Depok", "Tangerang", 30);
    connectNode(G, "Bekasi", "Tangerang", 45);
    connectNode(G, "Bekasi", "Depok", 25);

    printGraph(G);

    cout << endl << "=== HASIL TRAVERSAL BFS & DFS ===" << endl;
    printBFS(G, "Tangerang");
    printDFS(G, "Tangerang");

    cout << endl << "=== DELETE NODE DEPOK ===" << endl;
    deleteNode(G, "Depok");
    printGraph(G);

    return 0;
}
