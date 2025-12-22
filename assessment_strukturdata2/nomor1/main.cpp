#include "bst.h"

int main() {
    BinTree root = NULL;

    cout << "=== 1. Insert Data ===" << endl;
    insertNode(root, 50, "Monitor LED", 10);
    insertNode(root, 30, "Keyboard RGB", 20);
    insertNode(root, 70, "Mouse Gaming", 15);
    insertNode(root, 20, "Kabel HDMI", 50);
    insertNode(root, 40, "Headset 7.1", 12);
    insertNode(root, 60, "Webcam HD", 8);
    insertNode(root, 80, "Speaket BT", 5);
    cout << "Data berhasil diinput.\n" << endl;

    cout << "=== 2. Traversal ===" << endl;
    cout << "InOrder   : "; inOrder(root); cout << endl;
    cout << "PreOrder  : "; preOrder(root); cout << endl;
    cout << "PostOrder : "; postOrder(root); cout << endl << endl;

    cout << "=== 3. Search By ID (40) ===" << endl;
    searchById(root, 40);
    cout << endl;

    cout << "=== 4. Search By ID (99) ===" << endl;
    searchById(root, 99);
    cout << endl;

    cout << "=== 5. Search By Product (Webcam HD) ===" << endl;
    searchByProduct(root, "Webcam HD");
    cout << endl;

    cout << "=== 6. Search By Product (Printer) ===" << endl;
    searchByProduct(root, "Printer");
    cout << endl;

    cout << "=== 7. Find Min & Max ===" << endl;
    findMin(root);
    findMax(root);
    cout << endl;

    cout << "=== 8. Delete Node 20 ===" << endl;
    deleteNode(root, 20);

    cout << "=== 9. InOrder ===" << endl;
    inOrder(root); cout << endl << endl;

    cout << "=== 10. Delete Node 30 ===" << endl;
    deleteNode(root, 30);

    cout << "=== 11. InOrder ===" << endl;
    inOrder(root); cout << endl << endl;

    cout << "=== 12. Delete Node 50 ===" << endl;
    deleteNode(root, 50);

    cout << "=== 13. InOrder ===" << endl;
    inOrder(root); cout << endl << endl;

    cout << "=== 14. Delete Tree ===" << endl;
    deleteTree(root);
    cout << "Tree deleted." << endl;

    cout << "=== 15. InOrder (Setelah Delete Tree) ===" << endl;
    inOrder(root);
    cout << endl;

    return 0;
}