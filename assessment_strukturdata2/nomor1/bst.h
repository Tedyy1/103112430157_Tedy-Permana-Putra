#ifndef BST_H
#define BST_H

#include <iostream>
#include <string>
using namespace std;

struct infotype {
    int idProduk;
    string namaProduk;
    int stok;
};

typedef struct Node* adrNode;

struct Node {
    infotype info;
    adrNode left;
    adrNode right;
};

typedef adrNode BinTree;

adrNode newNode(int id, string nama, int stok);
void insertNode(BinTree &root, int id, string nama, int stok);
void searchById(BinTree root, int id);
void searchByProduct(BinTree root, string nama);
adrNode findMinNode(BinTree node);
adrNode deleteNodeRec(BinTree root, int id);
void deleteNode(BinTree &root, int id);

void inOrder(BinTree root);
void preOrder(BinTree root);
void postOrder(BinTree root);

void deleteTree(BinTree &root);
void findMin(BinTree root);
void findMax(BinTree root);

#endif