#include "bst.h"
#include <iostream>
using namespace std;

adrNode newNode(int id, string nama, int stok) {
    adrNode n = new Node;
    n->info.idProduk = id;
    n->info.namaProduk = nama;
    n->info.stok = stok;
    n->left = NULL;
    n->right = NULL;
    return n;
}

void insertNode(BinTree &root, int id, string nama, int stok) {
    if (root == NULL) {
        root = newNode(id, nama, stok);
    } else {
        if (id < root->info.idProduk) {
            insertNode(root->left, id, nama, stok);
        } else if (id > root->info.idProduk) {
            insertNode(root->right, id, nama, stok);
        } else {
            cout << "Duplicate ID " << id << " ignored." << endl;
        }
    }
}

void searchById(BinTree root, int id) {
    if (root == NULL) {
        cout << "Produk dengan ID " << id << " TIDAK DITEMUKAN." << endl;
        return;
    }
    
    if (root->info.idProduk == id) {
        cout << "DITEMUKAN: ID: " << root->info.idProduk 
             << ", Nama: " << root->info.namaProduk 
             << ", Stok: " << root->info.stok << endl;
    } else if (id < root->info.idProduk) {
        searchById(root->left, id);
    } else {
        searchById(root->right, id);
    }
}

void searchByProductRec(BinTree root, string nama, bool &found) {
    if (root != NULL) {
        if (root->info.namaProduk == nama) {
            cout << "DITEMUKAN: ID: " << root->info.idProduk 
                 << ", Nama: " << root->info.namaProduk 
                 << ", Stok: " << root->info.stok << endl;
            found = true;
        }
        searchByProductRec(root->left, nama, found);
        searchByProductRec(root->right, nama, found);
    }
}

void searchByProduct(BinTree root, string nama) {
    bool found = false;
    searchByProductRec(root, nama, found);
    if (!found) {
        cout << "Produk dengan nama \"" << nama << "\" TIDAK DITEMUKAN." << endl;
    }
}

adrNode findMinNode(BinTree node) {
    adrNode current = node;
    while (current && current->left != NULL) {
        current = current->left;
    }
    return current;
}

adrNode deleteNodeRec(BinTree root, int id) {
    if (root == NULL) return root;

    if (id < root->info.idProduk) {
        root->left = deleteNodeRec(root->left, id);
    } else if (id > root->info.idProduk) {
        root->right = deleteNodeRec(root->right, id);
    } else {
        if (root->left == NULL) {
            adrNode temp = root->right;
            delete root;
            return temp;
        } else if (root->right == NULL) {
            adrNode temp = root->left;
            delete root;
            return temp;
        }
        adrNode temp = findMinNode(root->right);

        root->info = temp->info;
        root->right = deleteNodeRec(root->right, temp->info.idProduk);
    }
    return root;
}

void deleteNode(BinTree &root, int id) {
    root = deleteNodeRec(root, id);
    cout << "Delete Node ID " << id << " selesai (jika ada)." << endl;
}

void inOrder(BinTree root) {
    if (root != NULL) {
        inOrder(root->left);
        cout << "[" << root->info.idProduk << " - " << root->info.namaProduk << "] ";
        inOrder(root->right);
    }
}

void preOrder(BinTree root) {
    if (root != NULL) {
        cout << "[" << root->info.idProduk << " - " << root->info.namaProduk << "] ";
        preOrder(root->left);
        preOrder(root->right);
    }
}

void postOrder(BinTree root) {
    if (root != NULL) {
        postOrder(root->left);
        postOrder(root->right);
        cout << "[" << root->info.idProduk << " - " << root->info.namaProduk << "] ";
    }
}

void deleteTree(BinTree &root) {
    if (root != NULL) {
        deleteTree(root->left);
        deleteTree(root->right);
        delete root;
        root = NULL;
    }
}

void findMin(BinTree root) {
    if (root == NULL) {
        cout << "Tree kosong." << endl;
        return;
    }
    adrNode current = root;
    while (current->left != NULL) {
        current = current->left;
    }
    cout << "Min ID: " << current->info.idProduk 
         << " (" << current->info.namaProduk << ")" << endl;
}

void findMax(BinTree root) {
    if (root == NULL) {
        cout << "Tree kosong." << endl;
        return;
    }
    adrNode current = root;
    while (current->right != NULL) {
        current = current->right;
    }
    cout << "Max ID: " << current->info.idProduk 
         << " (" << current->info.namaProduk << ")" << endl;
}